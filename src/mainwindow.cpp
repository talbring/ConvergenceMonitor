#include "../include/mainwindow.h"
#include "qfiledialog.h"
#include "../ui/ui_mainwindow.h"
#include "../include/plotsettings.h"
#include "../include/datatab.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  DataIndex(0)
{
  ui->setupUi(this);
  ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend | QCP::iSelectAxes);

  connect(ui->actionLoad_History,SIGNAL(triggered(bool)), this, SLOT(addDataTab()));
  connect(ui->customplot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(ShowContext(QCPAbstractPlottable*, QMouseEvent*)));
  connect(ui->actionFit_to_Data, SIGNAL(triggered(bool)), this, SLOT(FitToData(bool)));
  connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
  connect(ui->buttonRefresh, SIGNAL(clicked(bool)), this, SLOT(refreshData()));
  connect(ui->checkRefresh, SIGNAL(clicked(bool)), this, SLOT(autoRefresh(bool)));
  connect(&timer, SIGNAL(timeout()), this, SLOT(refreshData()));
  connect(ui->spinRefresh, SIGNAL(valueChanged(int)),  &timer, SLOT(start(int)));
  ui->customplot->legend->setVisible(true);


  connect(ui->customplot->yAxis2, SIGNAL(selectionChanged(QCPAxis::SelectableParts)), this, SLOT(SetRangeAxis(QCPAxis::SelectableParts)));
  connect(ui->customplot->yAxis, SIGNAL(selectionChanged(QCPAxis::SelectableParts)), this, SLOT(SetRangeAxis(QCPAxis::SelectableParts)));
  ui->tabWidget->addTab(new QLabel("No data, load a history file"), QString("Data"));

  ui->customplot->xAxis->setLabel("Iteration");
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::SetRangeAxis(QCPAxis::SelectableParts axis){

  if(axis == ui->customplot->yAxis2->selectedParts()){
      ui->customplot->axisRect()->setRangeDragAxes(ui->customplot->xAxis, ui->customplot->yAxis2);
      ui->customplot->axisRect()->setRangeZoomAxes(ui->customplot->xAxis, ui->customplot->yAxis2);
      ui->customplot->axisRect()->setRangeDrag(Qt::Vertical);
      ui->customplot->axisRect()->setRangeZoom(Qt::Vertical);
    }
  if(axis == ui->customplot->yAxis->selectedParts()){
      ui->customplot->axisRect()->setRangeDragAxes(ui->customplot->xAxis, ui->customplot->yAxis);
      ui->customplot->axisRect()->setRangeZoomAxes(ui->customplot->xAxis, ui->customplot->yAxis);
      ui->customplot->axisRect()->setRangeDrag(Qt::Vertical);
      ui->customplot->axisRect()->setRangeZoom(Qt::Vertical);
    }
  if(axis == ui->customplot->xAxis->selectedParts()){
      ui->customplot->axisRect()->setRangeDragAxes(ui->customplot->xAxis, ui->customplot->xAxis);
      ui->customplot->axisRect()->setRangeZoomAxes(ui->customplot->xAxis, ui->customplot->xAxis);
      ui->customplot->axisRect()->setRangeDrag(Qt::Horizontal);
      ui->customplot->axisRect()->setRangeZoom(Qt::Horizontal);

    }
}

void MainWindow::ShowContext(QCPAbstractPlottable* plot, QMouseEvent* event) // this is a slot
{
    // for most widgets
    QPoint globalPos = event->globalPos();
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction("Set Style...");
    // ...
    if (event->button() == Qt::RightButton){
    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
      if(selectedItem->text() == "Delete"){
          plot->setVisible(false);
        }
    }
    else
    {
        // nothing was chosen
    }
      }
}


void MainWindow::addDataTab(){

  DataHandler *data = new DataHandler();

  QString fileName = QFileDialog::getOpenFileName(this, tr("Open History File"),"", tr("SU2 History File (*.dat *.plt)"));
  QString tabname = fileName.split("/").last();

  if (!readDataFromFile(data,fileName)){
    QMessageBox::information(0, "Error", "There was an error while reading the file.");
  }
  if (fileName != ""){

    if(DataIndex == 0){
      ui->tabWidget->removeTab(0);
    }
    DataIndex++;

    DataTab* tab = new DataTab(data,ui->customplot, fileName,ui->tabWidget);

    datatabs.push_back(tab);

    tab->setProperty("FullPath", fileName);

    ui->tabWidget->addTab(tab, tabname);
  }
}


bool MainWindow::readDataFromFile(DataHandler *datahandler, QString fileName){

  if (fileName != ""){
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    /* --- Skip first line ---*/

    QString firstLine = in.readLine();
    firstLine = firstLine.split("=")[1];


    /* --- Read datafile header ---*/

    QString header = in.readLine();
    QStringList HeaderLine = header.split(",");

    for (int i = 0; i < HeaderLine.size(); i++){
      HeaderLine[i] = HeaderLine[i].remove("\"");
    }


    /* --- Remove the VARIABLES= at beginning of line ---*/

    HeaderLine[0] = HeaderLine[0].split("=")[1];

    /* --- Skip third line ---*/

    in.readLine();

    /* --- Read the data lines until end of file --- */

    QVector<QStringList> DataLines;

    while(!in.atEnd()) {
        QString line = in.readLine();
        line.remove("\"");
        QStringList fields = line.split(",");
        DataLines.push_back(fields);
    }


    for (int iData = 0; iData < HeaderLine.size(); iData++){

        QVector <double> data;
        DataHandler::DataItem item;

        item.label = HeaderLine[iData];

        for (int iLine = 0; iLine < DataLines.size(); iLine++){
            data.push_back(DataLines[iLine][iData].toDouble());
        }

        item.data = data;

        datahandler->addData(item);
    }

    return true;
  }
  return true;
}

void MainWindow::refreshData(){
  if (DataIndex != 0){
    for (uint iTab = 0; iTab < datatabs.size(); iTab++){
      DataHandler *data = new DataHandler();
      readDataFromFile(data, datatabs[iTab]->getFileName());
      datatabs[iTab]->updateData(data);
      delete data;
    }
  }
}

void MainWindow::autoRefresh(bool activate){
  if (activate){
     timer.start(ui->spinRefresh->value());
  }else{
    timer.stop();
  }
}

void MainWindow::FitToData(bool triggered){
  ui->customplot->rescaleAxes(true);
  ui->customplot->replot();
}

void MainWindow::closeTab(int index){
  if (DataIndex != 0){
    DataIndex--;
    ui->tabWidget->currentWidget()->deleteLater();
    ui->tabWidget->removeTab(index);
    qDebug() << "Removing tab " << index;
    if (DataIndex == 0){
      ui->tabWidget->addTab(new QLabel("No data, load a history file"), QString("Data"));
    }
   }
}

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

  connect(ui->actionLoad_History,SIGNAL(triggered(bool)), this, SLOT(ReadHistory()));
  connect(ui->customplot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(ShowContext(QCPAbstractPlottable*, QMouseEvent*)));
  connect(ui->actionFit_to_Data, SIGNAL(triggered(bool)), this, SLOT(FitToData(bool)));
  connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
  ui->customplot->legend->setVisible(true);


  connect(ui->customplot->yAxis2, SIGNAL(selectionChanged(QCPAxis::SelectableParts)), this, SLOT(SetRangeAxis(QCPAxis::SelectableParts)));
  connect(ui->customplot->yAxis, SIGNAL(selectionChanged(QCPAxis::SelectableParts)), this, SLOT(SetRangeAxis(QCPAxis::SelectableParts)));
  ui->tabWidget->addTab(new QLabel("No data, load a history file"), QString("Data"));
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

void MainWindow::ReadHistory(){

  bool csv = false;
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open History File"),"", tr("SU2 History File (*.dat *.plt)"));

  DataHandler* datahandler = new DataHandler;
  QVector<QStringList> DataLines;
  QStringList HeaderLine;

  QString tabname = fileName.split("/").last();

  if (fileName != ""){
    QStringList ext = fileName.split(".");

    if (ext[1] == "csv") csv = true;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    in.readLine();

    QString header = in.readLine();

    HeaderLine = header.split(",");

    for (int i = 0; i < HeaderLine.size(); i++){
      HeaderLine[i] = HeaderLine[i].remove("\"");
      std::cout << HeaderLine[i].toStdString() << std::endl;
    }
    HeaderLine[0] = HeaderLine[0].split("=")[1];

    in.readLine();

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

    for (int i = 1; i < HeaderLine.size(); i++){
      datahandler->getData(i).graph = ui->customplot->addGraph();
    }

    if(DataIndex == 0){
        ui->tabWidget->removeTab(0);
      }
    DataIndex++;

    DataTab* tab = new DataTab(datahandler,ui->customplot,ui->tabWidget);

    tab->setProperty("FullPath", fileName);
    qDebug() << tabname;

    ui->tabWidget->addTab(tab, tabname);
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

#include "../include/datatab.h"
#include "../ui/ui_datatab.h"
#include "../include/datahandler.h"
#include <iostream>
DataTab::DataTab(DataHandler *data_, QCustomPlot *plot_, QString fileName_, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DataTab),
  data(data_),
  plot(plot_),
  fileName(fileName_)
{
  ui->setupUi(this);

  ui->tableWidget->setColumnCount(4);
  ui->tableWidget->setRowCount(data->GetnData());
  ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Variable" << "Show" << "Axis" << "Color");
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(changeLabel(int,int)));

  QStringList colors;
  colors <<"Red"<< "Green"<< "Blue" << "darkRed"
        << "darkGreen" << "darkBlue" << "darkMagenta"
        << "darkCyan" << "darkYellow";

  for (int i = 0; i < data->GetnData(); i++){
    
      ui->xArrayCombo->addItem(data->getData(i).label);
      connect(ui->xArrayCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(changeXArray(int)));
    
      data->getData(i).graph = plot->addGraph();
      data->getData(i).graphIndex = plot->graphCount()-1;

      DataHandler::DataItem& item = data->getData(i);

      ui->tableWidget->setItem(i, 0, new QTableWidgetItem(item.label));

      QCheckBox* checkItem = new QCheckBox(ui->tableWidget);
      checkItem->setProperty("row", i);
      connect(checkItem, SIGNAL(stateChanged(int)), this, SLOT(showGraph(int)));
      checkItem->setCheckState(Qt::Unchecked);
      ui->tableWidget->setCellWidget(i, 1, checkItem);


      QComboBox* comboItem = new QComboBox(ui->tableWidget);
      comboItem->addItem("Left");
      comboItem->addItem("Right");
      comboItem->setProperty("row", i);
      connect(comboItem, SIGNAL(currentTextChanged(QString)), this, SLOT(changeAxes(QString)));
      ui->tableWidget->setCellWidget(i,2, comboItem);
      
      

      item.graph->setName(item.label);
      item.graph->setVisible(false);
      QPen qpen;
      qpen.setColor(colors[(i)%9]);
      item.graph->setPen(qpen);
      item.graph->removeFromLegend();

      
      QPushButton *ColorButton = new QPushButton(ui->tableWidget);
      QSignalMapper *ButtonSignalMapper = new QSignalMapper();
      
      connect(ColorButton, SIGNAL(pressed()), ButtonSignalMapper, SLOT(map()));
      ButtonSignalMapper->setMapping(ColorButton, i);
      connect(ButtonSignalMapper, SIGNAL(mapped(int)), this, SLOT(changeColor(int)));
      ui->tableWidget->setCellWidget(i, 3, ColorButton);
      
      QPalette pal = ColorButton->palette();
      pal.setColor(QPalette::Button, colors[(i)%9]);
      ColorButton->setPalette(pal);
      ColorButton->setFlat(true);
      ColorButton->setAutoFillBackground(true);
      
   }
  updateData(data);
}

void DataTab::changeXArray(int index){

  DataHandler::DataItem& xArrayData = data->getData(index);
  for (int i = 0; i < data->GetnData(); i++){
    DataHandler::DataItem& item = data->getData(i);
    
    item.graph->clearData();
    
    item.graph->addData(xArrayData.data, item.data);
  }
  plot->rescaleAxes(true);
  plot->replot();
  
}

void DataTab::changeColor(int row){
  
  QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user

  QPushButton* ColorButton = (QPushButton*)ui->tableWidget->cellWidget(row, 3);
  
  QPalette pal = ColorButton->palette();
  pal.setColor(QPalette::Button, chosenColor);
  ColorButton->setPalette(pal);
  ColorButton->setAutoFillBackground(true);
  
  QPen qpen;
  qpen.setColor(chosenColor);
  data->getData(row+1).graph->setPen(qpen);
  
  plot->replot();
}

QString DataTab::getFileName(){
  return fileName;
}

void DataTab::updateData(DataHandler *new_data){

  data->updateValues(new_data);

  DataHandler::DataItem& xArrayData = data->getData(ui->xArrayCombo->currentIndex());

  for (int i = 0; i < data->GetnData(); i++){
    DataHandler::DataItem& item = data->getData(i);

    item.graph->clearData();

    item.graph->addData(xArrayData.data, item.data);
  }
  plot->rescaleAxes(true);
  plot->replot();
}

void DataTab::changeLabel(int row, int column){
  QString text = ui->tableWidget->item(row, column)->text();

  data->getData(row).label = text;
  data->getData(row).graph->setName(text);

  plot->replot();
}

void DataTab::showGraph(int state){
  QCheckBox *checkbox = (QCheckBox*)sender();

  if (checkbox != NULL){
    int index = checkbox->property("row").toInt();

    DataHandler::DataItem& item = data->getData(index);

    if (state == Qt::Checked){
        item.graph->setVisible(true);
        item.graph->addToLegend();
    }else{
        item.graph->setVisible(false);
        item.graph->removeFromLegend();
      }

    plot->rescaleAxes(true);
    plot->replot();
   }
}

void DataTab::changeAxes(QString axes){
  QComboBox *combobox = (QComboBox*)sender();

  if (combobox != NULL){
      int index = combobox->property("row").toInt();

      DataHandler::DataItem& item = data->getData(index);

      if (axes == "Left"){
         item.graph->setValueAxis(plot->yAxis);
        }else if (axes == "Right"){
          item.graph->setValueAxis(plot->yAxis2);
          plot->yAxis2->setVisible(true);
        }

      item.graph->setVisible(true);
      QCheckBox* checkbox = (QCheckBox*)ui->tableWidget->cellWidget(index-1, 1);
      checkbox->setChecked(true);

      plot->rescaleAxes(true);
      plot->replot();
    }
}

DataTab::~DataTab()
{

  for (int i = 0; i < data->GetnData(); i++){
    DataHandler::DataItem& item = data->getData(i);
    
    //item.graph->removeFromLegend();
    plot->removeGraph(item.graphIndex);
  }

//  plot->replot();
  delete data;
  delete ui;
}

#include "datahandler.h"

DataHandler::DataHandler()
{
  DataItems.clear();
}


void DataHandler::addData(DataItem item){
  DataItems.push_back(item);
}

DataHandler::DataItem& DataHandler::getData(const int index){
  return DataItems[index];
}

unsigned short DataHandler::GetnData(){
  return DataItems.size();
}


void DataHandler::updateLabel(const unsigned short index, QString label){
  DataItems[index].label = label;
}

void DataHandler::updateValues(const unsigned short index, QVector<double> data){
  DataItems[index].data = data;
}

void DataHandler::updateValues(DataHandler *datahandler){
  if (DataItems.size() != datahandler->DataItems.size()){
     QMessageBox::information(0, "error", "Size of data container do not match");
  }else{
    for (unsigned short index = 0; index < DataItems.size(); index++){
      DataItems[index].data = datahandler->DataItems[index].data;
    }
  }
}

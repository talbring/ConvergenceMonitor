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


void DataHandler::changeLabel(const unsigned short index, QString label){
  DataItems[index].label = label;
}

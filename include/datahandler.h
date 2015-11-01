#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <QVector>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "qcustomplot.h"

class DataHandler : QWidget
{

public:
  DataHandler();

  struct DataItem{
    QVector<double> data;
    QString label;
    QCPGraph* graph;
    uint graphIndex;
    QVector<QTableWidgetItem*> tableItems;
  };

  void addData(DataItem item);

  DataItem &getData(const int index);

  unsigned short GetnData();

  void changeLabel(const unsigned short index, QString label);

private:
  QVector<DataItem> DataItems;


};

#endif // DATAHANDLER_H

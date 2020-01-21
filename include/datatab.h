#ifndef DATATAB_H
#define DATATAB_H

#include <QWidget>
#include "datahandler.h"

namespace Ui {
  class DataTab;
}

class DataTab : public QWidget
{
  Q_OBJECT

public:
  explicit DataTab(DataHandler *data_, QCustomPlot *plot_, QString fileName_, QWidget *parent = 0);
  ~DataTab();
  void updateData(DataHandler* new_data);
  QString getFileName();

protected slots:
  void showGraph(int state);
  void changeAxes(QString axes);
  void changeLabel(int row, int column);
  void changeColor(int row);
  void changeXArray(int index);

private:
  Ui::DataTab *ui;
  DataHandler *data;
  QCustomPlot *plot;
  QString fileName;


};

#endif // DATATAB_H

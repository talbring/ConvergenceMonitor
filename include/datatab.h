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
  explicit DataTab( DataHandler *data_, QCustomPlot *plot_, QWidget *parent = 0);
  ~DataTab();

protected slots:
  void showGraph(int state);
  void changeAxes(QString axes);
  void changeLabel(int row, int column);

private:
  Ui::DataTab *ui;
  DataHandler *data;
  QCustomPlot *plot;

};

#endif // DATATAB_H

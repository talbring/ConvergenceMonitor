#ifndef PLOTSETTINGS_H
#define PLOTSETTINGS_H

#include <QDialog>

namespace Ui {
  class plotsettings;
}

class plotsettings : public QDialog
{
  Q_OBJECT

public:
  explicit plotsettings(QWidget *parent = 0);
  ~plotsettings();

private:
  Ui::plotsettings *ui;
};

#endif // PLOTSETTINGS_H

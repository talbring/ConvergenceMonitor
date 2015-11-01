#include "plotsettings.h"
#include "ui_plotsettings.h"

plotsettings::plotsettings(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::plotsettings)
{
  ui->setupUi(this);
}

plotsettings::~plotsettings()
{
  delete ui;
}

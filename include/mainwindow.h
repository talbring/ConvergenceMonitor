#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

#include "../include/qcustomplot.h"
#include "../include/datahandler.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

  DataHandler *datahandler;


public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected slots:
  void ReadHistory();
  void ShowContext(QCPAbstractPlottable* plot, QMouseEvent* event);
  void FitToData(bool triggered);
  void closeTab(int index);
  void SetRangeAxis(QCPAxis::SelectableParts axis);

private:
  Ui::MainWindow *ui;
  uint DataIndex, NameIndex;
};

#endif // MAINWINDOW_H

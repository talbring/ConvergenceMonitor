#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QtConcurrent/QtConcurrent>

#include "../include/qcustomplot.h"
#include "../include/datahandler.h"
#include "../include/datatab.h"
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
public slots:
  void addDataTab(QString fileName);

protected slots:
  void ShowContext(QCPAbstractPlottable* plot, QMouseEvent* event);
  void FitToData(bool triggered);
  void closeTab(int index);
  void SetRangeAxis(QCPAxis::SelectableParts axis);
  void refreshData();
  void autoRefresh(bool activate);

private:
  bool readDataFromFile(DataHandler* datahandler, QString fileName);
  Ui::MainWindow *ui;
  uint DataIndex, NameIndex;
  QTimer timer;
  QVector<DataTab*> datatabs;

};

#endif // MAINWINDOW_H

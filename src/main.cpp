#include "../include/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  for (int numargs = 1; numargs < argc; numargs++){
    
    QString filename = argv[numargs];
     qDebug() << filename;
    w.addDataTab(filename);
    
  }
  return a.exec();
}

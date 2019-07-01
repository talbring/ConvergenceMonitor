/********************************************************************************
** Form generated from reading UI file 'datatab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATATAB_H
#define UI_DATATAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataTab
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *DataTab)
    {
        if (DataTab->objectName().isEmpty())
            DataTab->setObjectName(QString::fromUtf8("DataTab"));
        DataTab->resize(240, 277);
        gridLayout = new QGridLayout(DataTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(DataTab);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setRowCount(1);
        tableWidget->setColumnCount(2);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        retranslateUi(DataTab);

        QMetaObject::connectSlotsByName(DataTab);
    } // setupUi

    void retranslateUi(QWidget *DataTab)
    {
        DataTab->setWindowTitle(QApplication::translate("DataTab", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataTab: public Ui_DataTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATATAB_H

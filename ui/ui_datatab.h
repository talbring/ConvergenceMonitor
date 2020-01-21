/********************************************************************************
** Form generated from reading UI file 'datatab.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATATAB_H
#define UI_DATATAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataTab
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *xArrayCombo;
    QTableWidget *tableWidget;

    void setupUi(QWidget *DataTab)
    {
        if (DataTab->objectName().isEmpty())
            DataTab->setObjectName(QString::fromUtf8("DataTab"));
        DataTab->resize(240, 277);
        gridLayout = new QGridLayout(DataTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DataTab);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        xArrayCombo = new QComboBox(DataTab);
        xArrayCombo->setObjectName(QString::fromUtf8("xArrayCombo"));

        horizontalLayout->addWidget(xArrayCombo);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(DataTab);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setRowCount(1);
        tableWidget->setColumnCount(2);

        verticalLayout->addWidget(tableWidget);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(DataTab);

        QMetaObject::connectSlotsByName(DataTab);
    } // setupUi

    void retranslateUi(QWidget *DataTab)
    {
        DataTab->setWindowTitle(QCoreApplication::translate("DataTab", "Form", nullptr));
        label->setText(QCoreApplication::translate("DataTab", "X Array", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataTab: public Ui_DataTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATATAB_H

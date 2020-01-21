/********************************************************************************
** Form generated from reading UI file 'plotsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTSETTINGS_H
#define UI_PLOTSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_plotsettings
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *plotsettings)
    {
        if (plotsettings->objectName().isEmpty())
            plotsettings->setObjectName(QString::fromUtf8("plotsettings"));
        plotsettings->resize(439, 320);
        buttonBox = new QDialogButtonBox(plotsettings);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(310, 250, 121, 61));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(plotsettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), plotsettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), plotsettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(plotsettings);
    } // setupUi

    void retranslateUi(QDialog *plotsettings)
    {
        plotsettings->setWindowTitle(QCoreApplication::translate("plotsettings", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class plotsettings: public Ui_plotsettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTSETTINGS_H

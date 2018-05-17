/********************************************************************************
** Form generated from reading ui file 'display_lne.ui'
**
** Created: Tue Feb 3 17:37:51 2015
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DISPLAY_LNE_H
#define UI_DISPLAY_LNE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

class Ui_display_lneClass
{
public:
    QLineEdit *IDC_Lne_Display;
    QPushButton *IDC_Btn_Display;

    void setupUi(QWidget *display_lneClass)
    {
    if (display_lneClass->objectName().isEmpty())
        display_lneClass->setObjectName(QString::fromUtf8("display_lneClass"));
    QSize size(600, 400);
    size = size.expandedTo(display_lneClass->minimumSizeHint());
    display_lneClass->resize(size);
    IDC_Lne_Display = new QLineEdit(display_lneClass);
    IDC_Lne_Display->setObjectName(QString::fromUtf8("IDC_Lne_Display"));
    IDC_Lne_Display->setGeometry(QRect(60, 200, 113, 20));
    IDC_Btn_Display = new QPushButton(display_lneClass);
    IDC_Btn_Display->setObjectName(QString::fromUtf8("IDC_Btn_Display"));
    IDC_Btn_Display->setGeometry(QRect(70, 170, 75, 23));

    retranslateUi(display_lneClass);

    QMetaObject::connectSlotsByName(display_lneClass);
    } // setupUi

    void retranslateUi(QWidget *display_lneClass)
    {
    display_lneClass->setWindowTitle(QApplication::translate("display_lneClass", "display_lne", 0, QApplication::UnicodeUTF8));
    IDC_Btn_Display->setText(QApplication::translate("display_lneClass", "Display", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(display_lneClass);
    } // retranslateUi

};

namespace Ui {
    class display_lneClass: public Ui_display_lneClass {};
} // namespace Ui

#endif // UI_DISPLAY_LNE_H

/********************************************************************************
** Form generated from reading UI file 'dialogdisplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDISPLAYER_H
#define UI_DIALOGDISPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogDisplayerClass
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_city;
    QPushButton *pushButton_rote;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_start;

    void setupUi(QWidget *DialogDisplayerClass)
    {
        if (DialogDisplayerClass->objectName().isEmpty())
            DialogDisplayerClass->setObjectName(QString::fromUtf8("DialogDisplayerClass"));
        DialogDisplayerClass->resize(760, 578);
        gridLayout = new QGridLayout(DialogDisplayerClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(DialogDisplayerClass);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout->addWidget(widget, 0, 0, 6, 1);

        verticalSpacer_2 = new QSpacerItem(20, 216, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 5, 1, 1, 1);

        pushButton_clear = new QPushButton(DialogDisplayerClass);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        gridLayout->addWidget(pushButton_clear, 4, 1, 1, 1);

        pushButton_city = new QPushButton(DialogDisplayerClass);
        pushButton_city->setObjectName(QString::fromUtf8("pushButton_city"));

        gridLayout->addWidget(pushButton_city, 1, 1, 1, 1);

        pushButton_rote = new QPushButton(DialogDisplayerClass);
        pushButton_rote->setObjectName(QString::fromUtf8("pushButton_rote"));

        gridLayout->addWidget(pushButton_rote, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 216, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        pushButton_start = new QPushButton(DialogDisplayerClass);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));

        gridLayout->addWidget(pushButton_start, 3, 1, 1, 1);


        retranslateUi(DialogDisplayerClass);

        QMetaObject::connectSlotsByName(DialogDisplayerClass);
    } // setupUi

    void retranslateUi(QWidget *DialogDisplayerClass)
    {
        DialogDisplayerClass->setWindowTitle(QCoreApplication::translate("DialogDisplayerClass", "DialogDisplayer", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("DialogDisplayerClass", "\346\270\205\351\231\244", nullptr));
        pushButton_city->setText(QCoreApplication::translate("DialogDisplayerClass", "\345\237\216\345\270\202\347\276\244", nullptr));
        pushButton_rote->setText(QCoreApplication::translate("DialogDisplayerClass", "\350\267\257\345\276\204\350\247\204\345\210\222", nullptr));
        pushButton_start->setText(QCoreApplication::translate("DialogDisplayerClass", "\345\274\200\345\247\213\346\274\224\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogDisplayerClass: public Ui_DialogDisplayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDISPLAYER_H

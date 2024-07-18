#include "indialog.h"
#include <QApplication>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
#include <QEventLoop>
#include <QDebug>
#include <QInputDialog>
#include "widget.h"

indialog::indialog(QWidget *parent) : QWidget(parent)
{   QDialog *dialog = new QDialog();
    QLineEdit *lineEdit = new QLineEdit(dialog);
    QLabel *label = new QLabel(dialog);
     QPushButton *pushbutton = new QPushButton(dialog);
     dialog->resize(300,150);
     dialog->setWindowTitle("输入环节");
     lineEdit->resize(200,20);
     lineEdit->move(50,50);
     label->setText("请输入想要测试的城市数：");
     label->resize(200,20);
     label->move(60,20);
     pushbutton->setText("输入完毕");
     pushbutton->resize(120,30);
     pushbutton->move(90,90);
     connect(pushbutton, SIGNAL(clicked()),dialog,SLOT(accept()));
     dialog->setModal(true);
     dialog->exec();
     if(lineEdit->text()!=nullptr){
     a = lineEdit->text().toDouble();
     //qDebug() << a;
     }

}

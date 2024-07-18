#ifndef INDIALOG_H
#define INDIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class indialog; }
QT_END_NAMESPACE

class indialog : public QWidget
{
    Q_OBJECT
public:
    explicit indialog(QWidget *parent = nullptr);
    Ui::indialog *ui;
    int a;
    QLabel label;
    QLineEdit lineEdit;
    QPushButton pushbutton;
    QDialog dialog;
    void accept();
    int getinput();
    void closedialog();
};

#endif // INDIALOG_H

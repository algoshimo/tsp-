#include "dialogdisplayer.h"
#include "widget.h"
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QVBoxLayout>

DialogDisplayer::DialogDisplayer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);



    int w = 100;
    int h = 50;
	ui.pushButton_clear->setFixedSize(w, h);
	ui.pushButton_city->setFixedSize(w, h);
	ui.pushButton_rote->setFixedSize(w, h);
	ui.pushButton_start->setFixedSize(w, h);
    ui.pushButton_clear->move(1350,600);

   // ui.pushButton_clear->setl


	QGridLayout* l = new QGridLayout;
    l->setContentsMargins(0, 0, 0, 0);//设置要在布局周围使用的左边距、上边距、右边距和下边距。
    m_widget = new Widget(this);//声明widget对象
    l->addWidget(m_widget);//将m_widget添加到该布局中
	ui.widget->setLayout(l);

	this->resize(this->maximumSize());
}

DialogDisplayer::~DialogDisplayer()
{}

void DialogDisplayer::on_pushButton_city_clicked()
{
	if (m_widget) m_widget->InitCity();
}

void DialogDisplayer::on_pushButton_rote_clicked()
{
	ui.pushButton_start->setEnabled(false);
	if (m_widget) m_widget->CalRote();
	ui.pushButton_start->setEnabled(true);
}

void DialogDisplayer::on_pushButton_start_clicked()
{
	if (m_widget) m_widget->StartTime(true);
}

void DialogDisplayer::on_pushButton_clear_clicked()
{
	if (m_widget) m_widget->Clear();
}

#pragma once

#include <QWidget>
#include "ui_dialogdisplayer.h"
#include "widget.h"

class DialogDisplayer : public QWidget
{
	Q_OBJECT

public:
	DialogDisplayer(QWidget *parent = nullptr);
	~DialogDisplayer();

private:
	Ui::DialogDisplayerClass ui;

	Widget* m_widget;

	QTimer m_timer;
	int m_pindex;
	bool judge1, judge2, judge3;
	QVector<QPair<QPoint, QPoint>> m_lines;

private slots:
    void on_pushButton_city_clicked();
    void on_pushButton_rote_clicked();
    void on_pushButton_start_clicked();
    void on_pushButton_clear_clicked();
};

#ifndef POINT_H
#define POINT_H

#include <QWidget>
#include <QPainter>


class point : public QWidget
{
    Q_OBJECT
public:
    explicit point(QWidget *parent = nullptr);
    void paintpoint(QPainter &painter,int x,int y);
    void paintnumber(QPainter &painter,int x,int y,int i);


signals:

};

#endif // POINT_H

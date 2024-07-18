#ifndef POINT_H
#define POINT_H

#include <QWidget>
#include <QPainter>

class point : public QWidget
{
    Q_OBJECT
public:
    explicit point(QWidget *parent = nullptr);
    void paintpoint(QPainter &painter,int x,int y); // 根据输入的坐标绘制地图点
    void paintnumber(QPainter &painter,int x,int y,int i); // 显示城市点标号

signals:

};

#endif // POINT_H

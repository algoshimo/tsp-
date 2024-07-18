#include "point.h"
#include "widget.h"
#include <QString>
point::point(QWidget *parent) : QWidget(parent)
{

}
void point::paintpoint(QPainter &painter,int x,int y){
     painter.setRenderHint(QPainter::Antialiasing);//抗锯齿，平滑
     QBrush brush(Qt::red);
     painter.setBrush(brush);
     painter.drawEllipse(QPoint(x,y),10,10);
}
 void point ::paintnumber(QPainter &painter, int x, int y,int i)
 {

     QString a = QString::number(i+1);
     painter.drawText(x+10,y+10,a);
 }

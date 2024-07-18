#ifndef WIDGET_H
#define WIDGET_H
#include"city.h"
#include <QWidget>
#include <iostream>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <QVector>
#include <QTimer>
#include "time.h"     //程序运行时间
#define MAX_GEN 60000   //最大进化代数
#define CROSS 0.5     //交叉算子
#define MUT 0.1      //变异算子
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

    void StartTime(bool isture);
    void InitCity() { judge1 = true; this->update(); }
    void CalRote();
    void Clear();

    
    ~Widget();

private slots:
    void slot_Timeout();

private:
    void CalculatDist(CityPosition CityPos[]);//计算城市距离CityDistance[i][j]
    void copy(int a[],int b[]);//数组复制
    bool check(TSP &city,int pop,int num,int k);//用来检查新生成的节点是否在当前群体中，0号节点是默认出发节点和终止节点
    void InitColony(TSP &city);//种群初始化，即为city.colony[i][j]赋值
    void CalFitness(TSP &city);//计算适应度,同时选出最优的
    double GetFittness(int a[CITY_NUM+1]);//适应度
    void Select(TSP &city);//选择算子：轮盘赌法
    void Cross(TSP &city,double pc);//交叉：头尾不变，中间打乱顺序交叉
    void Mutation(TSP &city,double pm);//对换变异
    void OutPut(TSP &city);
    double CityDistance[CITY_NUM][CITY_NUM];
    double Hash1[CITY_NUM+1];
    //double lont[CITY_NUM]={673,223,553,401,308,760,780,726,689,111,546,598,470,461,634,610,761,746,780,590,448,610,519,163,430,675,755,755,317,735,754,324,642,460,230,724,800,739,348,627,498,191,728,750,100,680,518,302,600,450,610,470,165,330,200,350,800,330,170,351,760,550,765,800,615,900,950};
    //double lati[CITY_NUM]={145,100,142,841,164,445,371,126,188,204,260,287,267,203,268,669,518,359,472,356,336,111,218,280,232,100,481,398,756,450,280,330,317,119,221,377,460,224,282,213,140,156,489,323,267,299,325,194,450,461,500,520,700,650,500,450,350,400,350,550,650,850,800,700,400,650,660};
    double lont[CITY_NUM];
    double lati[CITY_NUM];

    QTimer m_timer;
    int m_pindex;
    bool judge1,judge2,judge3;
    QVector<QPair<QPoint, QPoint>> m_lines;
    Ui::Widget *ui;
};
#endif // WIDGET_H

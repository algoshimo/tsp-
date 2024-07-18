#include "widget.h"
#include "ui_widget.h"
#include "city.h"
#include "point.h"
#include <cmath>
#include<stdio.h>
#include <QPainter>
#include <QPushButton>
#include<QDebug>
using namespace std;

#define INVTERVAL 300

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    std::srand(std::time(nullptr));

    for(int i = 0; i < 67; i ++){
        int randomNumber = std::rand()%880+99;
        lont[i] = randomNumber;
    }

    for(int i = 0; i < 67; i ++){
        int randomNumber = std::rand()%730+99;
        lati[i] = randomNumber;
    }

    //this->resize(this->maximumSize());
    m_pindex = 0;
    judge1 = judge2 = judge3 = false;
    connect(&m_timer, &QTimer::timeout, this, & Widget::slot_Timeout);//该信号在计时器超时时发出。
}

TSP city;
CityPosition CityPos[CITY_NUM];
void Widget::paintEvent(QPaintEvent * e)
{
       for(int i=0;i<CITY_NUM;i++){
           CityPos[i].x=lont[i];
           CityPos[i].y=lati[i];
       }

      point draw;
      QPainter painter(this);
      painter.setRenderHint(QPainter::Antialiasing);//抗锯齿，平滑
      //绘制地图
          int j = 0;
          if(judge1){
          while(j<CITY_NUM){
            draw.paintpoint(painter,CityPos[j].x, CityPos[j].y);
            draw.paintnumber(painter, CityPos[j].x, CityPos[j].y,j);
          j++;
          }
        }

		  int cnt = m_pindex;
		  for (int i = 0; i < cnt; i++)
		  {
			  QPair<QPoint, QPoint> pp = m_lines[i];

			  QPoint p1 = pp.first;
			  QPoint p2 = pp.second;
			  double dis = sqrt((pow((double)p1.x() - p2.x(), 2) + pow((double)p1.y() - p2.y(), 2)));
			  double x = ((double)p1.x() + p2.x()) / 2;
			  double y = ((double)p1.y() + p2.y()) / 2;
			  painter.drawLine(pp.first, pp.second);
			  painter.drawText(x, y, QString::number(dis));

			  //painter.drawLine(pp.first, pp.second);
		  }

       QWidget::paintEvent(e);
}

void Widget::StartTime(bool isture)
{
    if (isture)
    {
        judge2 = true;
        m_timer.start(INVTERVAL);
    }
        
    else
        m_timer.stop();
}

void Widget::CalRote()//调用函数，计算路线
{
    m_lines.clear();
    m_pindex = 0;
	CalculatDist(CityPos);   //计算城市距离
    InitColony(city);       //生成初始种群
	CalFitness(city);       //计算适应度,同时选出最优的

	for (int i = 0; i < MAX_GEN; i++) {
		Select(city);           //选择：轮盘赌法
		Cross(city, CROSS);      //交叉
		Mutation(city, MUT);     //变异
		CalFitness(city);       //计算新的适应值
	}

	for (int i = 0; i < CITY_NUM; i++) {
		int index = city.BestRooting[i];
		int index_next = city.BestRooting[i + 1];

		qDebug() << QString::number(index) << QString::number(index_next);
		QPoint p1(CityPos[index].x, CityPos[index].y);
		QPoint p2(CityPos[index_next].x, CityPos[index_next].y);

        m_lines << QPair<QPoint, QPoint>(p1, p2);
	}
}

void Widget::Clear()//清空画布
{
    judge1 = false;
    judge2 = false;
    judge3 = false;
    m_pindex = 0;
    m_lines.clear();
    this->update();
}

void Widget::CalculatDist(CityPosition CityPos[]){
    if(CITY_NUM<=100)
    for(int i=0;i<CITY_NUM;i++){
        for(int j=0;j<CITY_NUM;j++){       //最后一个城市还应该返回到出发节点

            QApplication::processEvents();
            if(i!=j) CityDistance[i][j]=sqrt(pow(CityPos[j].x-CityPos[i].x,2)+pow(CityPos[j].y-CityPos[i].y,2));
            else CityDistance[i][i]=0;}}
    else
    for(int i=0;i<CITY_NUM;i++){
        for(int j=0;j<CITY_NUM;j++){
            QApplication::processEvents();
            if(i!=j) CityDistance[i][j]=sqrt(pow(CityPos[j].x-CityPos[i].x,2)+pow(CityPos[j].y-CityPos[i].y,2));
            else CityDistance[i][i]=0;
        }
    }
}
void Widget::copy(int *a, int *b){
    for(int i=0;i<CITY_NUM+1;i++)
        {
            a[i]=b[i];
        }
}
bool Widget::check(TSP &city, int pop, int num, int k){
    for(int i=0;i<=num;i++){
            if(k==city.colony[pop][i])
                return true;    //新生成节点存在于已经生成的路径中
        }
        return false;    //新生成节点没有存在于已经生成的路径中
}

// 种群初始化，即为city.colony[i][j]赋值
void Widget::InitColony(TSP &city){
    int r;
        for(int i=0;i<POPSIZE;i++){
            city.colony[i][0]=0;
            city.colony[i][CITY_NUM]=0;
            city.BestValue=MAXVALUE;
            city.BestFitness=0;     //适应值越大越好
            
        }
        for(int i=0;i<POPSIZE;i++)
        {
            for(int j=1;j<CITY_NUM;j++)
            {
                r=qrand()%(CITY_NUM-1)+1;      //产生1～CITY_NUM-1之间的随机数
                while(check(city,i,j,r))      //随机产生城市序号，即为city.colony[i][j]赋值
                {
                    r=qrand()%(CITY_NUM-1)+1;
                }

                city.colony[i][j]=r;
            }
        }

        QApplication::processEvents();//根据指定的标志处理调用线程的所有挂起事件
}

// 计算适应度，同时选出最优的路径
void Widget::CalFitness(TSP &city){
    int start,end;
        int Best=0;
        for(int i=0;i<POPSIZE;i++){        //求每个个体的总路径，适应度
            city.Distance[i]=0;
            for(int j=1;j<=CITY_NUM;j++){
                start=city.colony[i][j-1];
                end=city.colony[i][j];
                city.Distance[i]=city.Distance[i]+CityDistance[start][end];   //city.Distance[i]每个个体的总路径
            }
            city.fitness[i]=N/city.Distance[i];
            if(city.fitness[i]>city.fitness[Best])  //选出最大的适应度，即选出所有个体中的最短路径
                Best=i;
        }
        copy(city.BestRooting,city.colony[Best]);    //将最优个体拷贝给city.BestRooting
        city.BestFitness=city.fitness[Best];
        city.BestValue=city.Distance[Best];
        city.BestNum=Best;

}
double Widget::GetFittness(int a[CITY_NUM+1])
{
    int i,start,end;
        double Distance=0;
        for(i=0;i<CITY_NUM;i++){
            start=a[i];
            end=a[i+1];
            Distance+=CityDistance[start][end];
        }
        return N/Distance;
}

// 选择算子，轮盘赌法
void Widget::Select(TSP &city){
    int TempColony[POPSIZE][CITY_NUM+1];
        int i,t;
        double s;
        double GaiLv[POPSIZE];
        double SelectP[POPSIZE+1];
        double sum=0;
        for(i=0;i<POPSIZE;i++)	sum+=city.fitness[i];
        for(i=0;i<POPSIZE;i++)  GaiLv[i]=city.fitness[i]/sum;
        SelectP[0]=0;
        for(i=0;i<POPSIZE;i++)  SelectP[i+1]=SelectP[i]+GaiLv[i]*RAND_MAX;
        memcpy(TempColony[0],city.colony[city.BestNum],sizeof(TempColony[0]));
        for(t=1;t<POPSIZE;t++){
            double ran = qrand() % RAND_MAX + 1;
            s= (double) ran / 100.0;
            for(i=1;i<POPSIZE;i++)	if(SelectP[i]>=s)	break;
            memcpy(TempColony[t],city.colony[i-1],sizeof(TempColony[t]));
        }
        for(i=0;i<POPSIZE;i++)	memcpy(city.colony[i],TempColony[i],sizeof(TempColony[i]));
}

//交叉：头尾不变，中间打乱顺序交叉
void Widget::Cross(TSP &city,double pc)//交叉概率是pc
{
    int i,j,t,l;
       int a,ca,cb;
       int Temp1[CITY_NUM+1];
       for(i=0;i<POPSIZE;i++){
           double s=((double)(qrand()%RAND_MAX))/RAND_MAX;
           if(s<pc){
               cb=qrand()%POPSIZE;
               ca=cb;
               if(ca==city.BestNum||cb==city.BestNum)   //如果遇到最优则直接进行下次循环
                   continue;

               l=qrand()%(CITY_NUM/2)+1;      //1-一半的位置
               a=qrand()%(CITY_NUM-l)+1;     //全部

               memset(Hash1,0,sizeof(Hash1));   //将s中当前位置后面的n个字节 用ch替换并返回s 。
               Temp1[0]=Temp1[CITY_NUM]=0;
               for(j=1;j<=l;j++)          //打乱顺序即随机，选出来的通过Hash标记为1
               {
                   Temp1[j]=city.colony[cb][a+j-1]; //a+l=2~48 25~38
                   Hash1[Temp1[j]]=1;
               }
               for(t=1;t<CITY_NUM;t++)
               {
                   if(Hash1[city.colony[ca][t]]==0)
                   {
                       Temp1[j++]=city.colony[ca][t];
                       Hash1[city.colony[ca][t]]=1;
                   }
               }
               memcpy(city.colony[ca],Temp1,sizeof(Temp1));
           }
       }
}

//对换变异
void Widget::Mutation(TSP &city,double pm)
{
    int i,m;
        int Temp[CITY_NUM+1];
        for(int k=0;k<POPSIZE;k++){
            double s=((double)(qrand()%RAND_MAX))/RAND_MAX;    //随机产生概率0~1间
            i=qrand()%POPSIZE;                       //随机产生0~POPSIZE之间的数
            if(s<pm&&i!=city.BestNum)               //i!=city.BestNum,即保证最优的个体不变异
            {
                int a,b,t;
                a=(qrand()%(CITY_NUM-1))+1;
                b=(qrand()%(CITY_NUM-1))+1;
                copy(Temp,city.colony[i]);
                if(a>b)    //保证让b>=a
                {
                    t=a;
                    a=b;
                    b=t;
                }
                for(m=a;m<(a+b)/2;m++)
                {
                    t=Temp[m];
                    Temp[m]=Temp[a+b-m];
                    Temp[a+b-m]=t;
                }

                if(GetFittness(Temp)<GetFittness(city.colony[i]))
                {
                    a=(qrand()%(CITY_NUM-1))+1;
                    b=(qrand()%(CITY_NUM-1))+1;
                    memcpy(Temp,city.colony[i],sizeof(Temp));
                    if(a>b)
                    {
                        t=a;
                        a=b;
                        b=t;
                    }
                    for(m=a;m<(a+b)/2;m++)
                    {
                        t=Temp[m];
                        Temp[m]=Temp[a+b-m];
                        Temp[a+b-m]=t;
                    }

                        if(GetFittness(Temp)<GetFittness(city.colony[i]))
                        {
                            a=(qrand()%(CITY_NUM-1))+1;
                            b=(qrand()%(CITY_NUM-1))+1;
                            memcpy(Temp,city.colony[i],sizeof(Temp));
                            if(a>b)
                            {
                                t=a;
                                a=b;
                                b=t;
                            }
                            for(m=a;m<(a+b)/2;m++)
                            {
                                t=Temp[m];
                                Temp[m]=Temp[a+b-m];
                                Temp[a+b-m]=t;
                            }
                        }
                }
                memcpy(city.colony[i],Temp,sizeof(Temp));
            }
        }
}
void Widget::slot_Timeout()
{
   m_pindex++;

   this->update();
   if (m_pindex >= m_lines.count())
   {
       m_timer.stop();
   }
}

Widget::~Widget()
{
    delete ui;
}


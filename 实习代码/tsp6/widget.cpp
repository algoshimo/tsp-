#include "widget.h"
#include "ui_widget.h"
#include "point.h"
#include <QPainter>
#include <QPushButton>
#include<QDebug>
#include "iostream"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <QApplication>
#include <QThread>
#include "indialog.h"
#include <QDialog>
#include <QFont>

// 构造函数
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)

{
    //painter = QPainter(this);
    m_pindex = 0;
    ui->setupUi(this);

    judge1 = judge2 = judge3 = false;
    QFont font("楷体",12);
    QPushButton *btn1 = new QPushButton("输入",this);
    btn1->move(1350,100);//按钮位置
    btn1->resize(100,50);//按钮大小
    btn1->setStyleSheet("QPushButton { border: 1px solid black; border-radius:10px;}"
                   "QPushButton:hover { background-color: darkgray; }"
                   "QPushButton:pressed { background-color: black; color: white; }");
    btn1->setFont(font);
    QPushButton *btn2 = new QPushButton("生成地图",this);
    btn2->move(1350,200);//按钮位置
    btn2->resize(100,50);//按钮大小
    btn2->setStyleSheet("QPushButton {border: 1px solid black; border-radius:10px;}"
                   "QPushButton:hover { background-color: darkgray; }"
                   "QPushButton:pressed { background-color: black; color: white; }");
    btn2->setFont(font);
    QPushButton *btn3 = new QPushButton("动态规划",this);
    btn3->move(1350,300);//按钮位置
    btn3->resize(100,50);//按钮大小
    btn3->setStyleSheet("QPushButton {border: 1px solid black; border-radius:10px;}"
                   "QPushButton:hover { background-color: darkgray; }"
                   "QPushButton:pressed { background-color: black; color: white; }");
    btn3->setFont(font);
    QPushButton *btn4 = new QPushButton("贪心算法",this);
    btn4->move(1350,400);//按钮位置
    btn4->resize(100,50);//按钮大小
    btn4->setStyleSheet("QPushButton {border: 1px solid black; border-radius:10px;}"
                   "QPushButton:hover { background-color: darkgray; }"
                   "QPushButton:pressed { background-color: black; color: white; }");
    btn4->setFont(font);
    QPushButton *btn5 = new QPushButton("绘制路线",this);
    btn5->move(1350,500);//按钮位置
    btn5->resize(100,50);//按钮大小
    btn5->setStyleSheet("QPushButton {border: 1px solid black; border-radius:10px;}"
                   "QPushButton:hover { background-color: darkgray; }"
                   "QPushButton:pressed { background-color: black; color: white; }");
    btn5->setFont(font);
    QPushButton *btn6 = new QPushButton("清除",this);
    btn6->move(1350,600);
    btn6->resize(100,50);
    setFixedSize(1500,900);
    btn6->setStyleSheet("QPushButton {border: 1px solid black; border-radius:10px;}"
                   "QPushButton:hover { background-color: darkgray; }"
                   "QPushButton:pressed { background-color: black; color: white; }");
    btn6->setFont(font);
    connect(btn1,&QPushButton::clicked,this,&Widget::on_pushButton_clicked5);//点击输入
    connect(btn2,&QPushButton::clicked,this,&Widget::slot_pushButton_clicked);//点击生成，生成地图
    connect(btn3,&QPushButton::clicked,this,&Widget::slot_pushButton_clicked4);//点击选择dp
    connect(btn4,&QPushButton::clicked,this,&Widget::slot_pushButton_clicked3);//点击选择贪心算法
    connect(btn5,&QPushButton::clicked,this,&Widget::slot_pushButton_clicked1);//点击生成，绘制路线
    connect(btn6,&QPushButton::clicked,this,&Widget::slot_pushButton_clicked2);//点击清除，重置画板
    connect(&m_timer, &QTimer::timeout, this, &Widget::slot_Timeout);
}

void Widget::paintEvent(QPaintEvent * e) // 创建绘图事件
{
    path1[0] = 0;
    point draw;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿，平滑
    //绘制地图,随机生成坐标点
    if(judge5&&m==1){
      for(int i = 0;i <N;i++){
      posx = (qrand()%30 + 5)*25;
      posy = (qrand()%30 + 5)*20;
      x[i] = posx;
      y[i] = posy;
      }
      m++;
      }
        int i = 0;
        // 生成带权无向图
        if(judge1){
        while(i<N){
        draw.paintpoint(painter,x[i],y[i]);// 画点
        draw.paintnumber(painter,x[i],y[i],i); // 点的数字标号
        i++;
        }
      }

        // 生成无向带权图
      for(int i = 0; i < N; i ++){
        for(int j = i+1 ; j < N; j ++){
            double disdis = sqrt((pow((double)x[i] - x[j], 2) + pow((double)y[i] - y[j], 2)));
            double xx = (double)x[i];
            double yy = (double)y[i];
            double xxx = (double)x[j];
            double yyy = (double)y[j];

            double x = (xx + xxx)/2;
            double y = (yy + yyy)/2;

            QPen pen;
            pen.setColor(QColor(100,200,100));
            painter.setPen(pen);
            painter.drawLine(xx,yy,xxx,yyy);
            painter.drawText(x, y, QString::number(disdis));
        }
      }


        //欧几里德距离
    for (int i = 0; i < N - 1; i++)
        {
            distance[i][i] = 0;				// 对角线为0
            for (int j = i + 1; j < N; j++)
            {
                double dis = sqrt((pow((double)x[i] - x[j], 2) / 10 + pow((double)y[i] - y[j], 2) / 10));
                int disInt = (int)dis;
                distance[i][j] = dis == disInt ? disInt : disInt + 1;
                distance[j][i] = distance[i][j];
            }
        }
        distance[N - 1][N - 1] = 0;

        // 绘制路线时的线
        int cnt = m_pindex;
        for (int i = 0; i < cnt; i++)
        {
            QPair<QPoint, QPoint> pp = m_lines[i];

            QPoint p1 = pp.first;
            QPoint p2 = pp.second;
            double dis = sqrt((pow((double)p1.x() - p2.x(), 2) + pow((double)p1.y() - p2.y(), 2))); // 两点长度
            // 两点中心位置
            double x = ((double)p1.x() + p2.x())/2;
            double y = ((double)p1.y() + p2.y())/2;

            qDebug() << p1<< p2;
            qDebug() << x << y << dis;
            painter.setPen(Qt::black);
            painter.drawLine(pp.first, pp.second);
            painter.drawText(x, y, QString::number(dis));
    }

        QWidget::paintEvent(e);

}

// 判断路径上的点是是否全部访问，0未访问，1已经访问
bool Widget::isVisited(bool visited[]){
    for(int i = 1 ; i<N ;i++){
            if(visited[i] == false){
                return false;
            }
        }
        return true;
}

void Widget::slot_pushButton_clicked()
{
    judge5 = true;
    judge1 = true;
    this->update();
}
void Widget::slot_pushButton_clicked1()
{
    judge2 = true;
    judge5 = false;
    this->update();
    m_timer.start(300);
}
void Widget::slot_pushButton_clicked2()
{
    m_pindex = 0;
    judge1 = false;
    judge2 = false;
    judge3 = false;
    judge4 = false;
    m=1;
    this->update();

}
void Widget::slot_pushButton_clicked3()
{
    judge2 = true;
    judge3 = true;
    Greedy(); // 贪心
}
void Widget::slot_pushButton_clicked4()
{
    judge2 = true;
    judge4 = true;
    DP(); // 动态规划
}
void Widget::on_pushButton_clicked5()
{
    indialog *dialog = new indialog(this);
    dialog->setParent(this);
    dialog->show();
    N = dialog->a;

}
void Widget::slot_Timeout(void)
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

// 贪心算法
void Widget::Greedy(void)
{
    m_pindex = 0; // 城市的索引
    m_lines.clear(); // 路径的容器,用来装入起点和终点，方便绘制路线

    if (judge3) {
        // 默认从0开始遍历
        int current = 0;
        // 标识城市是否被访问,访问过置为 1
        bool visit[100] = { 0 };
        // 从第一个城市开始，所以为1
        visit[0] = 1;
        // 遍历 N - 1 次
        for (int i = 1; i < N; i++)
        {
            // 设置较大的距离初始值用来选取最近邻
            int min_distance = 0x7fffffff;
            // 保存当前最近邻城市的索引
            int temp;
            //循环选取城市
            for (int j = 1; j < N; j++)
            {
                // 找到最小路径长度的城市
                if (!visit[j] && distance[current][j] < min_distance)
                {
                    min_distance = distance[current][j];
                    temp = j;
                }
            }
            visit[temp] = 1;
            current = temp;
            path1[i] = current; // 最近的城市索引顺序，方便画路线时的遍历

        }

        // 如果judge2和judge3都为真，表示需要将路径绘制出来。通过循环遍历path1中的每个节点，依次将起点和终点添加到路径容器m_lines中，用于绘制路径线段。
        if (judge2 && judge3) {
            int k = 0;
            while (k < N - 1) {
                m_lines << QPair<QPoint, QPoint>(QPoint(x[path1[k]], y[path1[k]]), QPoint(x[path1[k + 1]], y[path1[k + 1]]));
                qDebug()<<path1[k]<<" "<<path1[k + 1];
                QApplication::processEvents(); //zz

                k++;
            }
            m_lines << QPair<QPoint, QPoint>(QPoint(x[path1[k]], y[path1[k]]), QPoint(x[0], y[0]));

            QApplication::processEvents(); //zz
        }

    }
}

// 动态规划
void Widget::DP(void)
{
    int M = 1 << (N-1); // 该位运算结果表示N已经被访问过了
    m_pindex = 0; // 城市的索引
    m_lines.clear(); // 用来装入起点和终点的容器，方便后期画线

    // dp用来存储每个状态的最优路径长度
    // dp[i][j]表示从起点到达结点i，经过集合j中的所有结点的最短路径长度
    // 初始化dp数组，将起点到每个结点的距离作为初始路径长度
    if (judge4) {
        for (int i = 0; i < N; i++) {
            dp[i][0] = distance[i][0];
        }

        //求解dp[i][j],先更新列再更新行
        // 外层循环遍历每个j集合
        for (int j = 1; j < M; j++) {
            // 内层循环遍历每个节点
            for (int i = 0; i < N; i++) {
                dp[i][j] = INF;
                //如果集合j(或状态j)中包含结点i,则不符合条件退出
                if (((j >> (i - 1)) & 1) == 1) {
                    continue;
                }
                // 遍历集合j中的每个结点k，如果k不在j中，则跳过
                for (int k = 1; k < N; k++) {
                    if (((j >> (k - 1)) & 1) == 0) {
                        continue;
                    }
                    // 通过比较更新dp为较小者
                    if (dp[i][j] > distance[i][k] + dp[k][j ^ (1 << (k - 1))]) {
                        dp[i][j] = distance[i][k] + dp[k][j ^ (1 << (k - 1))];
                    }
                }
            }
        }

        // 通过贪心来求解最优路径
        // 回溯求解最优路径
        int pioneer = 0; // 记录当前路径的最后一个结点
        int min1 = INF; // 记录最小路径长度
        int S = M - 1; // 记录当前未访问的结点集合状态
        int temp;
        //把起点结点编号加入容器
        path2.push_back(0);

        while (!isVisited(visited)) {
            for (int i = 1; i < N; i++) {
                if (visited[i] == false && (S & (1 << (i - 1))) != 0) {
                    if (min1 > distance[i][pioneer] + dp[i][(S ^ (1 << (i - 1)))]) {
                        min1 = distance[i][pioneer] + dp[i][(S ^ (1 << (i - 1)))];
                        temp = i;
                    }
                }
            }
            pioneer = temp;
            path2.push_back(pioneer);
            visited[pioneer] = true;
            S = S ^ (1 << (pioneer - 1));
            min1 = INF;
        }

        //绘制路线
        if (judge4 && judge2) {
            int i = 0;
            for (i = 0; i < path2.size() - 1; ++i) {

                m_lines << QPair<QPoint, QPoint>(QPoint(x[path2[i]], y[path2[i]]), QPoint(x[path2[i + 1]], y[path2[i + 1]]));
                qDebug()<<path2[i]<<" "<<path2[i + 1];
                QApplication::processEvents(); //zz
            }
            m_lines << QPair<QPoint, QPoint>(QPoint(x[path2[i]], y[path2[i]]), QPoint(x[0], y[0]));
        }
    }
}



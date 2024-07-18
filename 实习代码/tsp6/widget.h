#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QTimer>


#define INF 10000000
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *); // 创建绘图事件
     bool isVisited(bool visited[]); // 判断路径上的点是否全部访问
    ~Widget();

private:
    void Greedy(void); // 贪心算法
    void DP(void); // 动态规划

private slots :
    void slot_pushButton_clicked(); // 绘制地图
    void slot_pushButton_clicked1(); // 绘制路线
    void slot_pushButton_clicked2(); // 清除联系
    void slot_pushButton_clicked3(); // 贪心算法
    void slot_pushButton_clicked4(); // 动态规划
    void on_pushButton_clicked5(); // 点击输入
    void slot_Timeout(void); // 演示完路线绘制后停止

private:
    Ui::Widget *ui;
    int self_start = 0;
    int  posx,posy; // 坐标点
    int N;
    int m = 1;
    QVector<int> path2;
    bool visited[1000] = {false}; // 城市点的数组，下标是城市序号
    int dp[15][10000];
    bool judge1,judge2,judge3,judge4,judge5;
    int distance[100][100]; // 距离矩阵
    int path1[100];
    int x[100]; // x的坐标集合
    int y[100]; // y的坐标集合

    QTimer m_timer;
    int m_pindex;
    QVector<QPair<QPoint, QPoint>> m_lines;
};
#endif // WIDGET_H

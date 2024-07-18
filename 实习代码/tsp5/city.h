#ifndef CITY_H
#define CITY_H
#include <QMetaType>
#include <QWidget>
#define CITY_NUM 67  //城市个数
#define POPSIZE 300    //种群个体数
#define MAXVALUE 0x7ffffffff //路径最大值上限
#define N 100000       //需要根据实际求得的路径值修正
typedef struct {
    double x;
    double y;
}CityPosition;
Q_DECLARE_METATYPE(CityPosition)

typedef struct{
    int colony[POPSIZE][CITY_NUM+1];   //城市种群,默认出发城市编号为0，则城市编号的最后一个城市还应该为0
    double fitness[POPSIZE];           // 每个个体的适应度，即1/Distance[POPSIZE]
    double Distance[POPSIZE];          //每个个体的总路径
    int BestRooting[CITY_NUM+1];       //最优城市路径序列
    double BestFitness;                //最优路径适应值
    double BestValue;                  //最优路径长度
    int BestNum;                       //最优路径城市数目
}TSP;
Q_DECLARE_METATYPE(TSP)
class city : public QWidget
{
    Q_OBJECT
public:
    explicit city(QWidget *parent = nullptr);

signals:

};

#endif // CITY_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointF>
#include <QVector>
#include <QThread>
#include <cmath>
#include <QTime>
#include <QGraphicsTextItem>\
#include "iostream"
#include <QPushButton>
#include <QtWidgets>
#include <functional>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>

struct City {
    double x;
    double y;
};


// 计算两点城市距离
double calculateDistance(const City& city1, const City& city2) {
    return std::sqrt(std::pow(city2.x - city1.x, 2) + std::pow(city2.y - city1.y, 2));
}

double calculatePathLength(const QVector<City>& cities, const QVector<int>& path) {
    double totalDistance = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        totalDistance += calculateDistance(cities[path[i]], cities[path[i + 1]]);
    }
    // 添加最后一个城市和第一个城市之间的距离
    totalDistance += calculateDistance(cities[path.last()], cities[path.first()]);
    return totalDistance;
}

QVector<int> bruteForceTSP(const QVector<City>& cities) {
    QVector<int> bestPath;
    double bestLength = std::numeric_limits<double>::max();

    QVector<int> path(cities.size());
    for (int i = 0; i < path.size(); ++i) {
        path[i] = i;
    }

    do {
        double currentLength = calculatePathLength(cities, path);
        if (currentLength < bestLength) {
            bestLength = currentLength;
            bestPath = path;
        }
    } while (std::next_permutation(path.begin() + 1, path.end()));

    return bestPath;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    //QCoreApplication a(argc,argv);

    // 生成随机城市
    QVector<City> cities;
    const int numCities = 10;
    //int numCities;
    //std::cin >> numCities;
    const int sceneSize = 500;
    // 随机种子
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    for (int i = 0; i < numCities; ++i) {
        City city;
        city.x = qrand()%sceneSize;
        city.y = qrand()%sceneSize;
        cities.append(city);
    }

    // 用暴力算法求解TSP问题
    QVector<int> bestPath = bruteForceTSP(cities);

    // 创建图形场景和视图
    QGraphicsScene scene;
    QGraphicsView view(&scene);

    // 为城市绘制为点
    for (const City& city : cities) {
        //scene.addEllipse(city.x - 2, city.y - 2, 4, 4);
        QGraphicsEllipseItem* ellipseItem = scene.addEllipse(city.x-2, city.y-2, 10, 10);
        QPen pen(Qt::red);
        pen.setWidth(1);
        ellipseItem->setPen(pen);
        QBrush brush(Qt::red);
        ellipseItem->setBrush(brush);
    }

    // 生成带权无向图
    for(int i = 0; i < numCities; i ++){
      for(int j = i+1 ; j < numCities; j ++){
          double disdis = sqrt((pow(cities[i].x-cities[j].x, 2) + pow(cities[i].y-cities[j].y, 2)));
          double xx = cities[i].x;
          double yy = cities[i].y;
          double xxx = cities[j].x;
          double yyy = cities[j].y;
          double x = (xx + xxx)/2;
          double y = (yy + yyy)/2;

          QPen pen;
          pen.setColor(QColor(100,200,100));
          QGraphicsLineItem *lineItem = scene.addLine(xx,yy,xxx,yyy);
          lineItem->setPen(pen);
          QGraphicsTextItem *textItem = new QGraphicsTextItem;
          textItem->setPlainText(QString::number(disdis));
          textItem->setPos(x,y);
          scene.addItem(textItem);
      }
    }

    // 绘制最佳路径
    for (int i = 0; i < bestPath.size() - 1; ++i) {
        const City& city1 = cities[bestPath[i]];
        const City& city2 = cities[bestPath[i + 1]];
        double mid_x = (city1.x+city2.x)/2;
        double mid_y = (city1.y+city2.y)/2;
        double dis = calculateDistance(city1,city2);

        // 创建文本项并设置文本内容和位置
        QGraphicsTextItem *textItem = new QGraphicsTextItem;
        textItem->setPlainText(QString::number(dis));
        textItem->setPos(mid_x,mid_y);
        scene.addItem(textItem);
        scene.addLine(city1.x, city1.y, city2.x, city2.y);
    }
    // 添加最后一个城市和第一个城市之间的行
    const City& lastCity = cities[bestPath.last()];
    const City& firstCity = cities[bestPath.first()];
    double mid_x = (lastCity.x+firstCity.x)/2;
    double mid_y = (lastCity.y+firstCity.y)/2;
    double dis = calculateDistance(lastCity,firstCity);
    QGraphicsTextItem *textItem = new QGraphicsTextItem;
    textItem->setPlainText(QString::number(dis));
    textItem->setPos(mid_x,mid_y);
    scene.addItem(textItem);
    scene.addLine(lastCity.x, lastCity.y, firstCity.x, firstCity.y);

    // 设置视图大小和显示
    view.setFixedSize(sceneSize, sceneSize);
    view.show();

    return app.exec();
}

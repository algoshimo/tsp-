#include "widget.h"
#include"city.h"
#include "dialogdisplayer.h"
#include <QApplication>
#include <QMetaType>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<CityPosition>("CityPosition");
    qRegisterMetaType<TSP>("TSP");
    DialogDisplayer d;
    d.resize(1500,900);

    d.show();

    return a.exec();
}

//#include "widget.h"

//#include "game.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow g;
    g.show();
    return a.exec();
}

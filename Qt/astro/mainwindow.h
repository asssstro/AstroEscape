#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QWidget>
#include<QMainWindow>
#include "button.h"
#include<QPropertyAnimation>
#include "game.h"

namespace Ui{
class mainwindow;
}

class mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow();
    button *gamebutton=NULL;
    button *gamebutton2=NULL;
    button *gamebutton3=NULL;
    game *game_=NULL;
    QPropertyAnimation *start=NULL;

private slots:


private:
    Ui::mainwindow *ui;

signals:

};

#endif // MAINWINDOW_H

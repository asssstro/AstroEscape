#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"button.h"
#include<QPaintEvent>
#include<QPainter>
#include<QPushButton>
#include<QMessageBox>
#include<QMenu>
#include<QMenuBar>

#define button1 "../image/startgame1.png"
#define button2 "../image/startgame2.png"
#define button3 "../image/key1.png"
#define button4 "../image/key2.png"
#define button5 "../image/archive1.png"
#define button6 "../image/archive2.png"
#define title "../image/title.png"

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    this->setFixedSize(1280,720);
    this->setWindowIcon(QPixmap(title)); //设置应用图标
    this->setWindowTitle("AstroEscape");
    game_=new game(this,this->width(),this->height());//游戏类

    gamebutton =new button(button1,button2);
    gamebutton->setParent(this);
    gamebutton->move(120,430);

    gamebutton2 =new button(button3,button4);
    gamebutton2->setParent(this);
    gamebutton2->move(415,455);
    QString str_0 = "游 戏 玩 法 :\n"
                    "   1.点击开始并选择角色以进入游戏。\n"
                    "   2.游戏以控制人物避开障碍物，以获得更高得分为主要目标。\n"
                    "   3.控制人物跑得越远得分越高，吃到金币会有加分，碰到障碍物会有扣分并扣血，进入黑洞将会被传送。\n"
                    "   4.使用W、A、S、D移动人物，使用O冲刺以应对某些机关。\n"
                    "   5.吃到血包会回一定血量，不碰到障碍物人物会自动缓慢回血，血条为空时死亡，游戏结束。\n"
                    "   6.游戏会自动记录你的最高记录，试着打破它！";

    connect(gamebutton2,&QPushButton::clicked,this,
            [=](){
                QMessageBox::about(this,"游戏玩法",str_0);
            }
                );

    gamebutton3 =new button(button5,button6);
    gamebutton3->setParent(this);
    gamebutton3->move(665,455);

    connect(gamebutton3,&QPushButton::clicked,this,
            [=](){
                QString str="你的最高分数为："+QString("%1分").arg(game_->maxscore);
                QMessageBox::about(this,"游戏玩法",str);
            }
                );

    connect(gamebutton,&QPushButton::clicked,this,
            [=](){
                start=new QPropertyAnimation(gamebutton,"geometry");
                start->setDuration(300);
                start->setEasingCurve(QEasingCurve::OutQuad);
                start->setStartValue(QRect(gamebutton->x(),gamebutton->y(),gamebutton->width(),gamebutton->height()));
                start->setEndValue(QRect(gamebutton->x(),780,gamebutton->width(),gamebutton->height()));
                start->start();
                game_->ischoose=true;
                game_->beforegame=false;
                game_->button_=gamebutton;
                game_->button_2=gamebutton2;
                game_->button_3=gamebutton3;
                game_->chooseCharacter();
                gamebutton2->hide();
                gamebutton3->hide();
            });
}

mainwindow::~mainwindow(){
    delete ui;
    delete start;
    delete gamebutton;
    delete game_;
}

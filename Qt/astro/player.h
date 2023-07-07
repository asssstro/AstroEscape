#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include <QWidget>
#include <QTimer>



class Player:public QWidget
{
public:
    game* g;
    int wid, hei;
    int x, y;
    float vx, vy;
    float ax, ay;
    bool up, down, left, right;
    bool is_dashing, can_dash;
    bool can_jump;
    int score=0;
    int max_score=-1;
    int runningTime=0;
    int hp;
    int maxhp;

    int currImg;
    QPixmap run_image[8]; //奔跑图片
    QPixmap jump_img,down_img,fall_img;  //跳跃图片
    QTimer run_Timer;  //定时器

    Player(game* game_);
    int getl(); int geth(); int getx(); int gety();
    int getscore(); void setscore(int x);
    QPixmap getImg();

    void keyPress(QKeyEvent* event);
    void keyRelease(QKeyEvent* event);
    void move();
    void move(bool up, bool down, bool left, bool right);
    void jump();
    void dash();
    int getCurhp();
    void reducehp();
    void increasehp(int d);
    int getCurhpPercent();
    bool isKun;
};

#endif // PLAYER_H

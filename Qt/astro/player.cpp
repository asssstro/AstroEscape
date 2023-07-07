#include "player.h"
#include "game.h"
#include "qevent.h"
#include <QTimer>
#include <QDebug>

#define run_1 "../image/astro0.png"
#define run_2 "../image/astro1.png"
#define run_3 "../image/astro2.png"
#define run_4 "../image/astro3.png"
#define run_5 "../image/astro4.png"
#define jump_ "../image/astro_jump.png"
#define down_ "../image/astro_down.png"
#define fall_ "../image/astro_fall.png"

#define run_11 "../image/ikun0.png"
#define run_22 "../image/ikun1.png"
#define run_33 "../image/ikun2.png"
#define run_44 "../image/ikun3.png"
#define run_55 "../image/ikun4.png"
#define jump_kun "../image/ikun_jump.png"
#define down_kun "../image/ikun_down.png"
#define fall_kun "../image/ikun_fall.png"

Player::Player(game* game_)
{
    g = game_;
    wid = 120;
    hei = 150;
    isKun=g->isKun;
    if(isKun)
        x = 310;
    else
        x= 110;
    y = 285;
    vx = 0;
    vy = 0;
    ax = 0;
    ay = 0.6;
    up = down = left = right = false;
    is_dashing = false;
    can_dash = true;
    can_jump = true;
    hp=1000;
    maxhp=1000;

    if(isKun){
        run_image[0].load(run_11);
        run_image[1].load(run_22);
        run_image[2].load(run_33);
        run_image[3].load(run_22);
        run_image[4].load(run_11);
        run_image[5].load(run_44);
        run_image[6].load(run_55);
        run_image[7].load(run_44);
        jump_img.load(jump_kun);
        down_img.load(down_kun);
        fall_img.load(fall_kun);
    }
    else{
        run_image[0].load(run_1);
        run_image[1].load(run_2);
        run_image[2].load(run_3);
        run_image[3].load(run_2);
        run_image[4].load(run_1);
        run_image[5].load(run_4);
        run_image[6].load(run_5);
        run_image[7].load(run_4);
        jump_img.load(jump_);
        down_img.load(down_);
        fall_img.load(fall_);
    }
    currImg=0;
    run_Timer.setInterval(100);
    connect(&run_Timer,&QTimer::timeout,
            [=]()
            {
                currImg++;
                currImg%=8;
            }
            );
    run_Timer.start();
}

int Player::getl() { return wid; }
int Player::geth() { return hei; }
int Player::getx() { return x; }
int Player::gety() { return y; }
int Player::getscore(){ return this->score; }
void Player::setscore(int x){ this->score += x; }

void Player::keyPress(QKeyEvent* event)
{
    if(event->key()==Qt::Key_W && !down)
    {
        jump();
    }
    else if(event->key()==Qt::Key_S)
    {
        down = true;
    }
    else if(event->key()==Qt::Key_A)
    {
        left = true;
    }
    else if(event->key()==Qt::Key_D)
    {
        right = true;
    }
    else if(event->key()==Qt::Key_O)
    {
        dash();
    }
}

void Player::keyRelease(QKeyEvent* event)
{
    if(event->key()==Qt::Key_S)
    {
        down = false;
    }
    else if(event->key()==Qt::Key_A)
    {
        left = false;
    }
    else if(event->key()==Qt::Key_D)
    {
        right = false;
    }
}

void Player::move()
{
    if(is_dashing)
    {
        x += 50;
    }
    else
    {
        if(down)
        {
            hei = 86;
            wid=135;
            y = g->ground_Y - hei;
        }
        else
        {
            hei = 150;
            wid=120;
        }
        if(left)
        {
            x -= 7;
        }
        if(right)
        {
            x += 7;
        }
        else
        {
            x -= 3;
        }

        vy += ay;
        y += vy;
    }

    if(y > g->ground_Y - hei) y = g->ground_Y - hei;
    if(x < 0)                 x = 0;
    if(x + wid > g->width()*0.8)  x = g->width()*0.8-wid;

    g->update();
    runningTime++;
    if(runningTime % 8 == 0) score++;
    if(runningTime % 20 == 0) this->increasehp(3);
}

void Player::jump()
{
    if(y == g->ground_Y - hei) //在地板上
    {
        can_jump = true;
        vy = -15;
    }
    else if(y < g->ground_Y - hei) //在空中，且有一定高度
    {
        if(can_jump)
        {
            can_jump = false;
            vy = -15;
        }
    }
}

void Player::dash()
{
    if(!can_dash)
        return;

    is_dashing = true;
    can_dash = false;
    hei = 75;

    QTimer::singleShot(100, [=](){
        is_dashing = false;
        vy = 0;
        hei = 150;
    });
    QTimer::singleShot(300, [=](){
        can_dash = true;
    });
}

QPixmap Player::getImg(){
    if(down){
        return down_img;
    }
    if(this->y<g->ground_Y-hei){
        if(vy<0)return jump_img;
        else return fall_img;
    }
    else
    {
        return run_image[currImg];
    }
}

int Player::getCurhp(){
    return this->hp;
}
int Player::getCurhpPercent(){
    return this->hp*100/this->maxhp;
}
void Player::reducehp(){
    this->hp-=100;
    if(this->hp<=0) this->hp=0;
}
void Player::increasehp(int d){
    this->hp+=d;
    if(this->hp>=this->maxhp) this->hp=this->maxhp;
}

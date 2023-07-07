#include "barrier.h"

#include<QDebug>
#include<QTime>

#define block1 "../image/barrierOnGround.png"
#define block2 "../image/barrierOnCeiling.png"
#define rocket "../image/rocket.png"
#define stone "../image/stone.png"
#define coins1 "../image/star_like1.png"
#define coins2 "../image/star_like2.png"
#define hole "../image/hole.png"
#define hole_end "../image/hole_end.png"
#define bonus1 "../image/bonus.png"
#define bonus2 "../image/bonus.png"
#define bonus3 "../image/bonus.png"
#define flyBar "../image/flyBar.png"
const int flyspeed=20;

Barriers::Barriers(int a,int b,int c,int d,int s){
    this->x=a;
    this->y=b;
    this->length=c;
    this->height=d;
    this->speed=s;
}
void Barriers::setx(int a){
    this->x=a;
}
void Barriers::sety(int a){
    this->y=a;
}
void Barriers::setSpeed(int s){
    speed=s;
}
int Barriers::getx(){
    return this->x;
}
int Barriers::gety(){
    return this->y;
}
int Barriers::geth(){
    return this->height;
}
int Barriers::getl(){
    return this->length;
}


BlocksOnGround::BlocksOnGround(int a,int b,int c,int d,int s):Barriers(a,b,c,d,s){
    this->image.load(QString(block1));
}
bool BlocksOnGround::pass(){
    return this->getx()<-this->getl()||this->destroyed;
}
bool BlocksOnGround::hit(int x,int y,int l,int h){
    QRect re1(this->getx(),this->gety(),this->getl(),this->geth());
    QRect re2(x,y,l,h);
    bool tmp=re1.intersects(re2);
    if(tmp)this->broken=true;
    return tmp;
}
void BlocksOnGround::boom(){
    QPixmap img;
    img.load(QString("../image/groundBoom%1.png").arg(this->times/10+1));//载入爆炸特效图片
    this->times++;
    this->setImage(img);
    if(this->times==20)this->destroyed=true;
}
void BlocksOnGround::setImage(QPixmap i){
    this->image=i;
}
QPixmap BlocksOnGround::getImage(){
    return this->image;
}
void BlocksOnGround::move(){
    int newx=this->getx()-this->speed;
    this->setx(newx);
}


BlocksOnCeiling::BlocksOnCeiling(int a,int b,int c,int d,int s):Barriers(a,b,c,d,s){
    this->image.load(QString(block2));
}
bool BlocksOnCeiling::pass(){
    return this->getx()<-this->getl()||this->destroyed;
}
bool BlocksOnCeiling::hit(int x,int y,int l,int h){
    QRect re1(this->getx(),this->gety(),this->getl(),this->geth());
    QRect re2(x,y,l,h);
    return re1.intersects(re2);
}
void BlocksOnCeiling::boom(){
    this->times++;
    this->setx(this->getx()+flyspeed);
    this->sety(this->gety()-flyspeed);
    if(this->getx()>=1280||this->gety()+this->geth()<=0)this->destroyed=true;
}
void BlocksOnCeiling::setImage(QPixmap i){
    this->image=i;
}
QPixmap BlocksOnCeiling::getImage(){
    return this->image;
}
void BlocksOnCeiling::move(){
    this->setx(this->getx()-this->speed);
}


coin::coin(int a,int b,int c,int d,int s):Barriers(a,b,c,d,s){
    int tmp=rand();
    if(tmp%2)this->image.load(QString(coins1));
    else this->image.load(QString(coins2));
}
bool coin::pass(){
    return this->getx()+this->getl()<0||this->hintHeight<=0;
}
bool coin::hit(int x,int y,int l,int h){
    QRect re1(this->getx(),this->gety(),this->getl(),this->geth());
    QRect re2(x,y,l,h);
    return re1.intersects(re2);
}
void coin::setImage(QPixmap i){
    this->image=i;
}
QPixmap coin::getImage(){
    return this->image;
}
void coin::move(){
    this->setx(this->getx()-this->speed);
}


Rocket::Rocket(int a,int b,int c,int d,int s):Barriers(a,b,c,d,s){
    this->image.load(QString(rocket));
}
bool Rocket::pass(){
    return this->getx()<-this->getl()||this->destroyed;
}
bool Rocket::hit(int x,int y,int l,int h){
    QRect re1(this->getx(),this->gety(),this->getl(),this->geth());
    QRect re2(x,y,l,h);
    return re1.intersects(re2);
}
void Rocket::boom(){
    this->times++;
    this->setx(this->getx()+flyspeed);
    this->sety(this->gety()-flyspeed);
    if(this->getx()>=1280||this->gety()+this->geth()<=0)this->destroyed=true;
}
void Rocket::setImage(QPixmap i){
    this->image=i;
}
QPixmap Rocket::getImage(){
    return this->image;
}
void Rocket::move(){
    int newx=this->getx()-this->speed;
    this->setx(newx);
}


Stone::Stone(int a,int b,int c,int d,int s):Barriers(a,b,c,d,s){
    this->image.load(QString(stone));
}
bool Stone::pass(){
    return this->getx()<-this->getl()||this->destroyed;
}
bool Stone::hit(int x,int y,int l,int h){
    QRect re1(this->getx(),this->gety(),this->getl(),this->geth());
    QRect re2(x,y,l,h);
    return re1.intersects(re2);
}
void Stone::boom(){
    QPixmap img;
    img.load(QString("../image/stoneBoom%1.png").arg(this->times/10+1));//载入爆炸特效图片
    this->times++;
    this->setImage(img);
    if(this->times==20)this->destroyed=true;
}
void Stone::setImage(QPixmap i){
    this->image=i;
}
QPixmap Stone::getImage(){
    return this->image;
}
void Stone::move(){
    int newx=this->getx()-this->speed;
    this->setx(newx);
}


Wormhole::Wormhole(int a,int b,int c,int d,int s,int e,int f):Barriers(a,b,c,d,s),endx(e),endy(f){
    this->image.load(QString(hole));
    this->image_end.load(QString(hole_end));
}
bool Wormhole::pass(){
    return std::max(this->get_endx(),this->get_endx())+this->getl()<0;
}
bool Wormhole::hit(int x,int y,int l,int h){
    QRect re1(this->getx(),this->gety(),this->getl(),this->geth());
    QRect re2(x,y,l,h);
    return re1.intersects(re2);
}
void Wormhole::setImage(QPixmap i){
    this->image=i;
}
QPixmap Wormhole::getImage(){
    return this->image;
}
QPixmap Wormhole::getImage_end(){
    return this->image_end;
}
void Wormhole::move(){
    this->setx(this->getx()-this->speed);
    this->endx-=this->speed;
}
int Wormhole::get_endx(){
    return this->endx;
}
int Wormhole::get_endy(){
    return this->endy;
}


FlyBar::FlyBar(int a,int b,int c,int d,int s):Barriers(a,b,c,d,s){
    this->image.load(QString(flyBar));
}
bool FlyBar::pass(){
    return this->getx()<-this->getl()||this->destroyed;
}
bool FlyBar::hit(int x,int y,int l,int h){
    QRect re1(this->getx(),this->gety(),this->getl(),this->geth());
    QRect re2(x,y,l,h);
    return re1.intersects(re2);
}
void FlyBar::boom(){
    this->times++;
    this->setx(this->getx()+flyspeed);
    this->sety(this->gety()-flyspeed);
    if(this->getx()>=1280||this->gety()+this->geth()<=0)this->destroyed=true;
}
void FlyBar::setImage(QPixmap i){
    this->image=i;
}
QPixmap FlyBar::getImage(){
    return this->image;
}
void FlyBar::move(){
    int newx=this->getx()-this->speed;
    this->setx(newx);
}

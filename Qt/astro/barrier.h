#ifndef BARRIER_H
#define BARRIER_H

#endif // BARRIER_H
#include<QPixmap>
#include<QTime>


class Barriers{
private:
    int x,y;
    int length,height;

public:
    Barriers(int a,int b,int c,int d,int s);
    void setx(int a);
    void sety(int a);//获取障碍物矩形左上角坐标
    int speed;//障碍物随背景移动速度
    void setSpeed(int s);
    int getx();
    int gety();//设定障碍物矩形左上角坐标
    int geth();
    int getl();//获取障碍物参数
};

class BlocksOnGround:public Barriers{
private:
    QPixmap image;

public:
    bool broken=false;//是否被碰撞
    bool destroyed=false;//是否被摧毁（爆炸）
    int times=0;//爆炸后绘制次数
    BlocksOnGround(int a,int b,int c,int d,int s);
    bool pass();//障碍物是否超出屏幕或者已经爆炸
    bool hit(int x,int y,int l,int h);//是否发生碰撞
    void boom();//障碍物被碰撞后的爆炸
    void setImage(QPixmap i);//设置障碍物图片
    QPixmap getImage();//获取障碍物图片
    void move();//障碍物随背景移动
};

class BlocksOnCeiling:public Barriers{
private:
    QPixmap image;

public:
    bool broken=false;//是否被碰撞
    bool destroyed=false;//是否被摧毁（爆炸）
    int times=0;//爆炸后绘制次数
    BlocksOnCeiling(int a,int b,int c,int d,int s);
    bool pass();//障碍物是否超出屏幕或者已经爆炸
    bool hit(int x,int y,int l,int h);//是否发生碰撞
    void boom();//障碍物被碰撞后的爆炸
    void setImage(QPixmap i);//设置障碍物图片
    QPixmap getImage();//获取障碍物图片
    void move();//障碍物随背景移动
};

class coin:public Barriers{
private:
    QPixmap image;
    int value;
public:
    coin(int a,int b,int c,int d,int s);
    bool eaten=false;//金币是否被吃
    bool extra=false;
    bool restore=false;
    int hintHeight=100;//绘制加分逐渐消失的特效
    bool pass();//金币是否超出屏幕或者已经被吃
    bool hit(int x,int y,int l,int h);//是否发生碰撞
    void setImage(QPixmap i);//设置金币图片
    QPixmap getImage();//获取金币图片
    void move();//金币随背景移动
};

class Rocket:public Barriers{
private:
    QPixmap image;

public:
    bool broken=false;//是否被碰撞
    bool destroyed=false;//是否被摧毁（爆炸）
    int times=0;//爆炸后绘制次数
    Rocket(int a,int b,int c,int d,int s);
    bool pass();//障碍物是否超出屏幕或者已经爆炸
    bool hit(int x,int y,int l,int h);//是否发生碰撞
    void boom();//障碍物被碰撞后的爆炸
    void setImage(QPixmap i);//设置障碍物图片
    QPixmap getImage();//获取障碍物图片
    void move();//障碍物随背景移动
};

class Stone:public Barriers{
private:
    QPixmap image;

public:
    bool broken=false;//是否被碰撞
    bool destroyed=false;//是否被摧毁（爆炸）
    int times=0;//爆炸后绘制次数
    Stone(int a,int b,int c,int d,int s);
    bool pass();//障碍物是否超出屏幕或者已经爆炸
    bool hit(int x,int y,int l,int h);//是否发生碰撞
    void boom();//障碍物被碰撞后的爆炸
    void setImage(QPixmap i);//设置障碍物图片
    QPixmap getImage();//获取障碍物图片
    void move();//障碍物随背景移动
};

class Wormhole:public Barriers{
private:
    QPixmap image;
    QPixmap image_end;
    int endx,endy;
public:
    int hintHeight=100;
    int times=0;//爆炸后绘制次数
    Wormhole(int a,int b,int c,int d,int s,int e,int f);
    bool pass();//障碍物是否超出屏幕
    bool cross=false;
    bool hit(int x,int y,int l,int h);//是否发生碰撞
    void setImage(QPixmap i);//设置障碍物图片
    QPixmap getImage();//获取障碍物图片
    QPixmap getImage_end();
    void move();//障碍物随背景移动
    int get_endx();
    int get_endy();
};


class FlyBar:public Barriers{
private:
    QPixmap image;

public:
    bool broken=false;//是否被碰撞
    bool destroyed=false;//是否被摧毁（爆炸）
    int times=0;//爆炸后绘制次数
    FlyBar(int a,int b,int c,int d,int s);
    bool pass();//障碍物是否超出屏幕或者已经爆炸
    bool hit(int x,int y,int l,int h);//是否发生碰撞
    void boom();//障碍物被碰撞后的爆炸
    void setImage(QPixmap i);//设置障碍物图片
    QPixmap getImage();//获取障碍物图片
    void move();//障碍物随背景移动
};

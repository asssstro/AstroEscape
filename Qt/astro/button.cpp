#include "button.h"
#include<QPushButton>

button::button(QString str,QString str2){
    img1.load(str);
    img2.load(str2);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setFixedSize(QSize(img1.width(),img1.height())); //按钮尺寸
    this->setIcon(img1);            //按钮图标
    this->setIconSize(QSize(img1.width(),img1.height()));  //图标尺寸
    diffh=(img2.height()-img1.height())/2;
    diffw=(img2.width()-img1.width())/2;

}

button::~button(){

}
void button::mouseReleaseEvent(QMouseEvent* e){//鼠标点击
    //qDebug()<<"鼠标";
    return QPushButton::mouseReleaseEvent(e);
}
void button::enterEvent(QEnterEvent *event)
{
    //qDebug()<<"鼠标进入";
    this->setFixedSize(QSize(img2.width(),img2.height()));  //设置更大图标
    this->setIcon(img2);
    this->setIconSize(QSize(img2.width(),img2.height()));
    this->move(this->x()-diffw,this->y()-diffh);
}
void button::leaveEvent(QEvent *event)
{
    //qDebug()<<"鼠标离开";
    this->setFixedSize(QSize(img1.width(),img1.height())); //按钮尺寸
    this->setIcon(img1);            //按钮图标
    this->setIconSize(QSize(img1.width(),img1.height()));  //图标尺寸
    this->move(this->x()+diffw,this->y()+diffh);
}

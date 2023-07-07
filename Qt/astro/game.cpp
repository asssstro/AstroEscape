#include "game.h"
//#include "ui_mainwindow.h"
#include "player.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QVector>
#include <vector>
#include <time.h>
#include <QTime>
#include <ctime>
#include <QMessageBox>
#include <QFile>
#include <QDesktopServices>


#define back0 "../image/start.png"
#define back1 "../image/background1.png"
#define back2 "../image/background2.png"
#define back3 "../image/background3.png"
#define back4 "../image/background4.png"
#define bigcoin "../image/bigcoin.png"
#define heart "../image/heart.png"
#define hurtimg "../image/hurt.png"
#define defeatImg "../image/defeat.png"
#define chooseImg "../image/choose.png"
#define astro1 "../image/astro0.png"
#define astro2 "../image/astro0_choose.png"
#define ikun1 "../image/ikun0.png"
#define ikun2 "../image/ikun0_choose.png"

const int hintSize=40;
const int punish=250;

game::game(QWidget *parent,int wid,int heig): QWidget(parent)/*,ui(new Ui::game)*/
{
    QFile file("../save.txt");
    file.open(QIODevice::ReadOnly| QIODevice::Text);
    QTextStream txtInput(&file);
    QString lineStr;
    /*if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //qDebug()<<"111";
    }*/
    while (!txtInput.atEnd())
    {
        lineStr = txtInput.readAll();
        maxscore = lineStr.toInt();
    }
    file.close();


   // ui->setupUi(this);
    srand((unsigned)time(NULL));
    this->resize(wid,heig);
    ground_Y=heig;
    //背景
    back_0.load(back0);
    background1.load(back1);
    background2.load(back2);
    background3.load(back3);
    background4.load(back4);
    background1_X=0;
    background2_X=background1_X+this->width()-5;
    background3_X=background2_X+this->width()-5;
    background4_X=background3_X+this->width()-5;
    hurtImg.load(hurtimg);
    defeat.load(defeatImg);
    choose.load(chooseImg);

    up = down = left = right = false;
    //p = new Player(this);
    ground_speed=5;
    timer.setInterval(17);
    this->grabKeyboard();
    connect(&timer,&QTimer::timeout,[=](){

        p->move();

        p->max_score=std::max(p->max_score,p->score);
        this->ground_speed=5+p->max_score/1000;

        for(auto i=barrier1.begin();i!=barrier1.end();++i)(*i)->setSpeed(ground_speed);
        for(auto i=barrier2.begin();i!=barrier2.end();++i)(*i)->setSpeed(ground_speed);
        for(auto i=barrier3.begin();i!=barrier3.end();++i)(*i)->setSpeed(ground_speed);
        for(auto i=barrier4.begin();i!=barrier4.end();++i)(*i)->setSpeed(ground_speed);
        for(auto i=barrier5.begin();i!=barrier5.end();++i)(*i)->setSpeed(2*ground_speed);
        for(auto i=coin1.begin();i!=coin1.end();++i)(*i)->setSpeed(ground_speed);
        for(auto i=hole.begin();i!=hole.end();++i)(*i)->setSpeed(ground_speed);

        for(auto i=coin1.begin();i<coin1.end();++i){
            if((*i)->pass()){
                i=coin1.erase(i);
                --i;
            }
            else{
                if((*i)->hit(p->getx(),p->gety(),p->getl(),p->geth())){
                    (*i)->eaten=true;
                }
                (*i)->move();
            }
        }

        for(auto i=barrier1.begin();i<barrier1.end();++i){
            if((*i)->pass()){
                i=barrier1.erase(i);
                --i;
                }
            else{
                    if((*i)->hit(p->getx(),p->gety(),p->getl(),p->geth())){
                        (*i)->broken=true;
                    }
                    (*i)->move();
            }
        }

        for(auto i=barrier2.begin();i<barrier2.end();++i){
            if((*i)->pass()){
                    i=barrier2.erase(i);
                    --i;
            }
            else{
                    if((*i)->hit(p->getx(),p->gety(),p->getl(),p->geth())){
                        (*i)->broken=true;
                    }
                    (*i)->move();
            }
        }

        for(auto i=barrier3.begin();i<barrier3.end();++i){
            if((*i)->pass()){
                    i=barrier3.erase(i);
                    --i;
            }
            else{
                    if((*i)->hit(p->getx(),p->gety(),p->getl(),p->geth())){
                        (*i)->broken=true;
                    }
                    (*i)->move();
            }
        }

        for(auto i=barrier4.begin();i<barrier4.end();++i){
            if((*i)->pass()){
                i=barrier4.erase(i);
                --i;
            }
            else{
                    if((*i)->hit(p->getx(),p->gety(),p->getl(),p->geth())){
                        (*i)->broken=true;
                    }
                    (*i)->move();
            }
        }

        for(auto i=barrier5.begin();i<barrier5.end();++i){
            if((*i)->pass()){
                    i=barrier5.erase(i);
                    --i;
            }
            else{
                    if((*i)->hit(p->getx(),p->gety(),p->getl(),p->geth())){
                        (*i)->broken=true;
                    }
                    (*i)->move();
            }
        }

        for(auto i=hole.begin();i<hole.end();++i){
            if((*i)->pass()){
                i=hole.erase(i);
                --i;
            }
            else{
                if((*i)->hit(p->getx(),p->gety(),p->getl(),p->geth())){
                    p->x=(*i)->get_endx();
                    p->y=(*i)->get_endy();
                    (*i)->cross=true;
                }
                (*i)->move();
            }
        }

        if(isRunning){
            if(p->getCurhp()==0){
                gameisover();

                //存档
                QFile file("../save.txt");
                QTextStream txtInput(&file);
                QString lineStr;
                /*if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    return;
                }*/
                while (!txtInput.atEnd())
                {
                    lineStr = txtInput.readAll();
                    maxscore = lineStr.toInt();
                }
                file.close();
                if (score > maxscore)
                {
                    if (file.exists())
                    {
                        file.remove();
                    }
                    file.open(QIODevice::WriteOnly);
                    file.close();
                    if (file.open(QFile::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                        QTextStream out(&file);
                        out << score;
                    }
                    file.close();
                }
            }
            addBarriers();
        }
    }
    );
    //timer.start();
}

game::~game()
{

}

void game::background_move(){
    this->background1_X-=this->ground_speed;
    this->background2_X-=this->ground_speed;
    this->background3_X-=this->ground_speed;
    this->background4_X-=this->ground_speed;
    if(this->background1_X+this->width()-5<=0)this->background1_X=this->background4_X+this->width()-5;
    if(this->background2_X+this->width()-5<=0)this->background2_X=this->background1_X+this->width()-5;
    if(this->background3_X+this->width()-5<=0)this->background3_X=this->background2_X+this->width()-5;
    if(this->background4_X+this->width()-5<=0)this->background4_X=this->background3_X+this->width()-5;
}

void game::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    if(beforegame==true){
        painter.drawPixmap(0,0,this->width(),this->height(),back_0);
    }
    else if(ischoose){
        painter.drawPixmap(0,0,this->width(),this->height(),choose);
    }
    else if(gameover){
        painter.drawPixmap(0,0,1280,720,defeat);
    }
    else{
    painter.drawPixmap(background1_X,0,this->width(),this->height(),background1);
    painter.drawPixmap(background2_X,0,this->width(),this->height(),background2);
    painter.drawPixmap(background3_X,0,this->width(),this->height(),background3);
    painter.drawPixmap(background4_X,0,this->width(),this->height(),background4);
    this->background_move();


    //画金币
    for(auto i=coin1.begin();i!=coin1.end();++i){
        if(!(*i)->eaten){
            painter.drawPixmap((*i)->getx(),(*i)->gety(),(*i)->getl(),(*i)->geth(),(*i)->getImage());
        }
        else {
            if((*i)->hintHeight==100){
                if(!(*i)->restore){
                    p->score+=50;
                    if((*i)->extra)p->score+=150;
                }
                else p->increasehp(100);
            }
            QPen tmp(Qt::white);
            painter.setFont(QFont("黑体",hintSize));
            if((*i)->extra){
                painter.setPen(tmp);
                painter.drawText(this->width()-150,(*i)->hintHeight,QString("+200"));
                (*i)->hintHeight-=5;
            }
            else{
                painter.setPen(tmp);
                painter.drawText(this->width()-150,(*i)->hintHeight,QString("+50"));
                (*i)->hintHeight-=5;
            }
        }
    }

    //画虫洞
    for(auto i=hole.begin();i!=hole.end();++i){
        painter.drawPixmap((*i)->getx(),(*i)->gety(),(*i)->getl(),(*i)->geth(),(*i)->getImage());
        painter.drawPixmap((*i)->get_endx(),(*i)->get_endy(),(*i)->getl(),(*i)->geth(),(*i)->getImage_end());
        if((*i)->cross){
            if((*i)->times==0){
                p->score+=50;
                (*i)->times++;
            }
            QPen tmp(Qt::white);
            painter.setFont(QFont("黑体",hintSize));
            painter.setPen(tmp);
            if((*i)->hintHeight>=0){
                painter.drawText(this->width()-150,(*i)->hintHeight,QString("+50"));
                (*i)->hintHeight-=5;
            }
        }
    }

    //画障碍物
    for(auto i=barrier1.begin();i!=barrier1.end();++i){
        if((*i)->broken){
            if((*i)->times==0){
                p->score-=punish;
                p->reducehp();
                hurtImgAlpha = 255;
            }
            QPen tmp(Qt::red);
            painter.setFont(QFont("黑体",hintSize));
            painter.setPen(tmp);
            painter.drawText(this->width()-300,(20-(*i)->times)*5,QString("-200"));
            (*i)->boom();
        }
        painter.drawPixmap((*i)->getx(),(*i)->gety(),(*i)->getl(),(*i)->geth(),(*i)->getImage());
    }

    for(auto i=barrier2.begin();i!=barrier2.end();++i){
        if((*i)->broken){
            if((*i)->times==0){
                p->score-=punish;
                p->reducehp();
                hurtImgAlpha = 255;
            }
            QPen tmp(Qt::red);
            painter.setFont(QFont("黑体",hintSize));
            painter.setPen(tmp);
            painter.drawText(this->width()-300,(20-(*i)->times)*5,QString("-200"));
            (*i)->boom();
        }
        painter.drawPixmap((*i)->getx(),(*i)->gety(),(*i)->getl(),(*i)->geth(),(*i)->getImage());
    }

    for(auto i=barrier3.begin();i!=barrier3.end();++i){
        if((*i)->broken){
            if((*i)->times==0){
                p->score-=punish;
                p->reducehp();
                hurtImgAlpha = 255;
            }
            QPen tmp(Qt::red);
            painter.setFont(QFont("黑体",hintSize));
            painter.setPen(tmp);
            painter.drawText(this->width()-300,(20-(*i)->times)*5,QString("-200"));
            (*i)->boom();
        }
        painter.drawPixmap((*i)->getx(),(*i)->gety(),(*i)->getl(),(*i)->geth(),(*i)->getImage());
    }

    for(auto i=barrier4.begin();i!=barrier4.end();++i){
        if((*i)->broken){
            if((*i)->times==0){
                p->score-=punish;
                p->reducehp();
                hurtImgAlpha = 255;
            }
            QPen tmp(Qt::red);
            painter.setFont(QFont("黑体",hintSize));
            painter.setPen(tmp);
            painter.drawText(this->width()-300,(20-(*i)->times)*5,QString("-200"));
            (*i)->boom();
        }
        painter.drawPixmap((*i)->getx(),(*i)->gety(),(*i)->getl(),(*i)->geth(),(*i)->getImage());
    }

    for(auto i=barrier5.begin();i!=barrier5.end();++i){
        if((*i)->broken){
            if((*i)->times==0){
                p->score-=punish;
                p->reducehp();
                hurtImgAlpha = 255;
            }
            QPen tmp(Qt::red);
            painter.setFont(QFont("黑体",hintSize));
            painter.setPen(tmp);
            painter.drawText(this->width()-300,(20-(*i)->times)*5,QString("-200"));
            (*i)->boom();
        }
        painter.drawPixmap((*i)->getx(),(*i)->gety(),(*i)->getl(),(*i)->geth(),(*i)->getImage());
    }

    painter.drawPixmap(p->getx(),p->gety(),p->getl(),p->geth(),p->getImg());

    //画分数
    QPen pen1(Qt::white);
    painter.setFont(QFont("黑体",20));
    pen1.setColor(Qt::white);
    painter.setPen(pen1);
    painter.drawText(20,50,QString("Score:%1").arg(p->getscore()));

    //画血条
    int tmphp=p->getCurhpPercent()*120/100;
    painter.drawRect(QRect(p->getx()+5,p->gety()-20,120,10));
    if(tmphp>=80)
        painter.fillRect(QRect(p->getx()+5,p->gety()-20,tmphp,10),Qt::green);
    else if(tmphp<40)
        painter.fillRect(QRect(p->getx()+5,p->gety()-20,tmphp,10),Qt::red);
    else
        painter.fillRect(QRect(p->getx()+5,p->gety()-20,tmphp,10),Qt::yellow);

    //画扣血特效
    if(hurtImgAlpha!=0) {
        QPixmap temp(hurtImg.size());
        temp.fill(Qt::transparent);
        QPainter p2(&temp);
        p2.setCompositionMode(QPainter::CompositionMode_Source);
        p2.drawPixmap(0,0,hurtImg);
        p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        p2.fillRect(temp.rect(),QColor(0,0,0,hurtImgAlpha));
        painter.drawPixmap(QRect(0,0,this->width(),this->height()),temp);
        hurtImgAlpha-=3;
    }
    }
}

void game::addBarriers(){
    static int barrierTime=0;
    static int holeTime=0;
    int thres1=std::max(120-2*(p->max_score/1000),80);
    int thres2=std::max(200-2*(p->max_score/1000),160);
    int choice=rand()%999;
    if(barrierTime*ground_speed/6>thres1){
        if(choice%3==0){//生成地面障碍物与金币
            barrier1.push_back(new BlocksOnGround(this->width()+180,this->ground_Y-100,100,100,ground_speed));
            coin1.push_back(new coin(this->width(),this->ground_Y-80,60,60,ground_speed));
            coin1.push_back(new coin(this->width()+90,this->ground_Y-180,60,60,ground_speed));
            coin1.push_back(new coin(this->width()+200,this->ground_Y-250,60,60,ground_speed));
            coin1.push_back(new coin(this->width()+310,this->ground_Y-180,60,60,ground_speed));
            coin1.push_back(new coin(this->width()+400,this->ground_Y-80,60,60,ground_speed));
            int extra=rand();
            if(extra%5==0){
                coin* i=new coin(this->width()+rand()%640,160+rand()%320,70,70,ground_speed);
                QPixmap img;
                if(rand()%3)img.load(QString(bigcoin));
                else{
                    img.load(QString(heart));
                    i->restore=true;
                }
                (*i).setImage(img);
                (*i).extra=true;
                coin1.push_back(i);
            }
        }
        else if(choice%3==1){//生成长障碍物
            barrier2.push_back(new BlocksOnCeiling(this->width(),0,100,this->height()-100,ground_speed));
            coin1.push_back(new coin(this->width()+15,this->ground_Y-80,60,60,ground_speed));
        }
        else{//生成缝隙障碍物
            barrier3.push_back(new Rocket(this->width(),0,100,350,ground_speed+(ground_speed>10?rand()%5:0)));
            barrier4.push_back(new Stone(this->width(),this->height()-220,100,250,ground_speed));
            coin1.push_back(new coin(this->width()+20,400,60,60,ground_speed));
        }
        if(choice%5==0){
            barrier5.push_back(new FlyBar(this->width(),200+rand()%360,400,50,2*ground_speed));
        }
        barrierTime=0;
    }
    if(holeTime*ground_speed/6>thres2){//生成虫洞
        int dx1=360,dx2=400;
        while(dx2-dx1<300||dx1<=720){
            dx1=rand()%1080;
            dx2=rand()%1080;
        }
        hole.push_back(new Wormhole(dx1,250,200,50,ground_speed,dx2,rand()%450));
        holeTime=0;
    }
    barrierTime++;
    holeTime++;
}


void game::keyPressEvent(QKeyEvent *event)
{
    if(gameover&&event->key()==Qt::Key_R){
        //Rscore=p->getscore();
        start_game();
    }
    else if(gameover&&event->key()==Qt::Key_B){
        back();
    }
    else
        p->keyPress(event);
}
void game::keyReleaseEvent(QKeyEvent *event)
{
    p->keyRelease(event);
}

void game::start_game(){
    //beforegame=false;
    ischoose=false;
    p = new Player(this);
    //p->isKun=this->isKun;
    timer.setInterval(17);
    timer.start();
    isRunning=true;
    gameover=false;
    update();
}

/*void game::restart_game(){
    p = new Player(this);
    timer.start();
    isRunning=true;
    gameover=false;
    beforegame=false;
    p->setscore(Rscore-5000);
    update();
}*/

void game::gameisover(){
    score=p->getscore();
    if(score>maxscore){
        maxscore=score;
    }
    QMessageBox Debox;
    Debox.setWindowTitle("游戏结束");
    Debox.setText("你的得分："+QString("%1").arg(p->getscore())+'\n');
    //Debox.setIconPixmap(defeat);
    Debox.exec();

    QFile file("../save.txt");
    QTextStream txtInput(&file);
    QString lineStr;
    /*if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Open failed." << Qt::endl;
        //return ;
    }*/
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readAll();
        maxscore=lineStr.toInt();
    }
    file.close();

    isRunning=false;
    gameover=true;
    timer.stop();
    p->run_Timer.stop();
    barrier1.clear();
    barrier2.clear();
    barrier3.clear();
    barrier4.clear();
    barrier5.clear();
    coin1.clear();
    hole.clear();
    delete p;
    update();
}

void game::back(){
    QFile file("../save.txt");
    QTextStream txtInput(&file);
    QString lineStr;
    /*if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"222";
        //return;
    }*/
    while (!txtInput.atEnd())
    {
        lineStr = txtInput.readAll();
        maxscore = lineStr.toInt();
    }
    file.close();

    beforegame=true;
    button_->move(120,430);
    button_2->show();
    button_3->show();
    update();
}

void game::chooseCharacter(){
    beforegame=false;
    ischoose=true;
    update();
    astrobutton= new button(astro1,astro2);
    astrobutton->setParent(this);
    astrobutton->move(110,285);
    astrobutton->show();

    ikunbutton = new button(ikun1,ikun2);
    ikunbutton->setParent(this);
    ikunbutton->move(310,285);
    ikunbutton->show();

    connect(astrobutton,&QPushButton::clicked,this,
            [=](){
                isKun=false;
        //qDebug()<<"111";
                this->start_game();
                astrobutton->hide();
                ikunbutton->hide();
            });

    connect(ikunbutton,&QPushButton::clicked,this,
            [=](){
                isKun=true;
        //qDebug()<<"111";
                this->start_game();
                astrobutton->hide();
                ikunbutton->hide();
            });
}

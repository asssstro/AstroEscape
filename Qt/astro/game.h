#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QTimer>
#include "barrier.h"
#include "button.h"

/*QT_BEGIN_NAMESPACE
namespace Ui { class game; }
QT_END_NAMESPACE*/

class Player;

class game : public QWidget
{
    Q_OBJECT

private:
    QPixmap background1; //游戏地图
    QPixmap background2;
    QPixmap background3;
    QPixmap background4;
    QPixmap hurtImg;
    QPixmap back_0;
    QPixmap defeat;
    QPixmap choose;


public:
    explicit game(QWidget *parent = nullptr,int wid=1280,int heig=720);
    ~game();

    double background1_X; // X点
    double background2_X;
    double background3_X;
    double background4_X;
    double ground_speed=1; //地面移动参数
    int ground_Y; //Y点
    bool up;
    bool down;
    bool right;
    bool left;
    int hurtImgAlpha=0;
    Player* p;
    QTimer timer;
    std::vector<BlocksOnGround *> barrier1;
    std::vector<BlocksOnCeiling *> barrier2;
    std::vector<Rocket *> barrier3;
    std::vector<Stone *> barrier4;
    std::vector<FlyBar *> barrier5;
    std::vector<coin *> coin1;
    std::vector<Wormhole *> hole;
    void addBarriers();
    void paintEvent(QPaintEvent *event);//绘图
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    void background_move();
    int maxscore;

    button *button_=NULL;
    button *button_2=NULL;
    button *button_3=NULL;
    bool isRunning=false;
    void start_game();
    bool beforegame=true;
    bool gameover=false;
    bool ischoose=false;
    void gameisover();
    int score=0;
    void back();
    //int Rscore=0;
    //void restart_game();
    void chooseCharacter();
    bool isKun=false;
    button *astrobutton=NULL;
    button *ikunbutton=NULL;

/*private:
    Ui::game *ui;*/

signals:

public slots:
};
#endif // GAME_H

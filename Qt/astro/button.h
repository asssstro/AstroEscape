#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include<QPushButton>
#include<QString>

class button : public QPushButton
{
    Q_OBJECT
private:
    QPixmap img1;
    QPixmap img2;
public:
    //explicit button(QWidget *parent = nullptr);
    button(QString str,QString str2);
    ~button();

    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
    void mouseReleaseEvent(QMouseEvent *e);
    //void init();
    int diffh;
    int diffw;

signals:

};

#endif // BUTTON_H

#include "Interface.h"


double Interface::interface_x = 1750,Interface::interface_y = 962.5;

Interface::Interface(QWidget *parent):
     QWidget(parent),
     map(new Map),
     mainmenu(new Mainmenu(this, this->map)),
     intro(new Intro(this, this->map)),
     tremble(new Tremble(this, this->map)),
     pickmenu(new Pickmenu(this,this->map)),
     play(new Play(this,this->map))
{
    mainmenu->resize(interface_x, interface_y);
    mainmenu->hide();

    intro->resize(interface_x, interface_y);
    intro->hide();

    tremble->resize(interface_x, interface_y);
    tremble->hide();

    pickmenu->resize(interface_x, interface_y);
    pickmenu->hide();

    play->resize(interface_x, interface_y);
    play->hide();

    Timer = startTimer(16);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

}

void Interface::paintEvent(QPaintEvent *)
{
    switch(map->interface_state)
    {
    case 0:
        if(map->Snd->che(1))map->Snd->ply(1);
        mainmenu->show();
        intro->hide();
        pickmenu->hide();
        play->hide();
        tremble->hide();
        mainmenu->grabKeyboard();
        break;
    case 1:
         if(map->Snd->che(5))map->Snd->ply(5);
        mainmenu->hide();
        intro->show();
        pickmenu->hide();
        play->hide();
        tremble->hide();
        intro->grabKeyboard();
        break;
    case 2:
        if(map->Snd->che(4))map->Snd->ply(4);
        mainmenu->hide();
        intro->hide();
        pickmenu->show();
        play->hide();
        tremble->hide();
        pickmenu->grabKeyboard();
        break;
    case 3:
        mainmenu->hide();
        intro->hide();
        pickmenu->hide();
        play->show();
        tremble->hide();
        play->grabKeyboard();
        break;
    case 4:
        if(map->Snd->che(2))map->Snd->ply(2);
        mainmenu->hide();
        intro->hide();
        pickmenu->hide();
        play->hide();
        tremble->show();
        tremble->grabKeyboard();
    }

}

Interface::~Interface() { }
void Interface::mousePressEvent(QMouseEvent *)  { update(); }
void Interface::mouseMoveEvent(QMouseEvent *)   { update(); }
void Interface::mouseReleaseEvent(QMouseEvent *){ update(); }
void Interface::keyPressEvent(QKeyEvent *) {update();}
void Interface::keyReleaseEvent(QKeyEvent *) {update();}

void Interface::tremb()
{
    double rate = map->rate;
    QPoint now = pos();
    move(QPoint(now.x()+((qrand()%20)-10)*rate, now.y()+((qrand()%20)-10))*rate);
}

void Interface::timerEvent(QTimerEvent *)
{
    double rate = map->rate;
    if(map->if_tremble==1&&tremble->cnt%3==0&&tremble->cnt<=450)
    {
        move(10*rate,10*rate);
    }
    if(map->if_tremble==1&&tremble->cnt%3!=0&&tremble->cnt<=450)
    {
        tremb();
    }
    update();
}

#include "Tremble.h"

Tremble::Tremble(QWidget *parent, Map *amp):
    QWidget(parent),
    map(amp)
{
    setFocus();
    setParent(parent);
    Timer = startTimer(16);
    image.load("://cnmb/SoccerBall2.png");
    cnt =0;
}


void Tremble::paintEvent(QPaintEvent *)
{
     QPainter painter(this);
     paintbackground(painter);
     paintball(painter, map->ball->pos, map->ball->h);
     painttips(painter);
}


void Tremble::paintbackground(QPainter &painter)
{
     double rate = map->rate;
     QBrush black(QColor(0,0,0,255));
     QRect all(0,0,2500*rate,1375*rate);
     painter.fillRect(all,black);
}


void Tremble::paintball(QPainter &painter, QPointF point, double h)
{
    double rate = map->rate;
    QBrush grey(QColor(130,130,130,100));
    QPen pen(grey, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(grey);
    painter.drawEllipse(QPointF(point.x()*rate,point.y()*rate), std::max((double)5, (40-(0.03*h)))*rate*0.85,std::max((double)5, (40-(0.03*h)))*rate*0.85);
    painter.drawImage(QPointF(point.x()*rate-16, point.y()*rate-16.5-h*0.1*rate), image);
}


void Tremble::painttips(QPainter &painter)
{
    double rate = map->rate;
    QBrush white(QColor(255,255,255,255));
    QBrush white1(QColor(255,255,255,140));
    painter.setBrush(white);
    QPen pen1(white, 10*rate, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen2(white1, 6*rate, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QFont font1("Small fonts", 31, QFont::Black, false);
    QFont font2("Small fonts", 18, QFont::Black, false);
//    painter.drawRect(750*rate, 200*rate, 1400*rate, 150*rate);
//    painter.drawRect(750*rate, 350*rate, 1400*rate, 150*rate);
//    painter.drawRect(750*rate, 700*rate, 1400*rate, 150*rate);
//    painter.drawRect(750*rate, 850*rate, 1400*rate, 150*rate);
//    painter.drawRect(750*rate, 1000*rate, 1400*rate, 150*rate);
    painter.setPen(pen1);
    painter.setFont(font1);

    std::string a1 = "When  Nobody  is  Kicking ,";
    std::string a2 = "A  Ball  has  to  Kick  Himself .";
    std::string a3 = "I'm  only  a  Ball .";
    std::string a4 = "But  I";
    std::string a5 = "Shall  Win  the  Match !";
    std::string a6 = "Press  Space  to  skip ▼";
    if(cnt>=80)
    painter.drawText(QRectF(750*rate, 200*rate, 1400*rate, 150*rate), Qt::AlignCenter, a1.c_str());
    if(cnt>=160)
    painter.drawText(QRectF(750*rate, 350*rate, 1400*rate, 150*rate), Qt::AlignCenter, a2.c_str());
    if(cnt>=240)
    painter.drawText(QRectF(750*rate, 700*rate, 1400*rate, 150*rate), Qt::AlignCenter, a3.c_str());
    if(cnt>=320)
    painter.drawText(QRectF(750*rate, 850*rate, 1400*rate, 150*rate), Qt::AlignCenter, a4.c_str());
    if(cnt>=400)
    painter.drawText(QRectF(750*rate, 1000*rate, 1400*rate, 150*rate), Qt::AlignCenter, a5.c_str());

    painter.setPen(pen2);
    painter.setFont(font2);
    painter.drawText(QRectF(1750*rate, 1200*rate, 600*rate, 100*rate), Qt::AlignCenter, a6.c_str());

}

void Tremble::timerEvent(QTimerEvent *)
{
    if(map->if_tremble){
        cnt++;
    }
    if(cnt==600)
    {
       map->if_tremble = 0;
       cnt =0;
       map->interface_state = 2;
    }
    update();
}

void Tremble::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space){
        map->if_tremble = 0;
        cnt =0;
        map->interface_state = 2;
    }
    update();
}

void Tremble::keyReleaseEvent(QKeyEvent *)
{
    update();
}





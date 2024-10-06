#include "Intro.h"

Intro::Intro(QWidget *parent, Map* amp):
    QWidget(parent),
    map(amp)
{
    setFocus();
    //this->grabKeyboard();
    setParent(parent);
    Timer = startTimer(16);
    image.load("://cnmb/SoccerBall2.png");
    cnt = 0;
}


void Intro::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    paintbackground(painter);
    paintball(painter, map->ball->pos, map->ball->h);
    for(int i=0;i<map->tiger_num;i++)
        painttiger(painter, map->tiger[i]->pos, (map->ball->pos-map->tiger[i]->pos), map->tiger[i]->kick_dis);
    painttips(painter);
}



void Intro::paintbackground(QPainter &painter)
{
    double rate = map->rate;
    QBrush green(QColor(0,201,87,255));
    QBrush grey(QColor(130,130,130,200));
    QBrush grey2(QColor(130,130,130,175));
    QBrush white(QColor(255,255,255,255));
    QBrush black(QColor(0,0,0,255));
    QPen pen1(white, 10*rate, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen2(grey, 10*rate, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen3(black, 10*rate, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QRect all(0,0,1750,962.5);
    painter.fillRect(all,green);

    const double a = 10*rate;
    for(double x = 130; x < 200; x += 2*a)
        for(double y = 580; y<975; y += 2*a)
            painter.fillRect(QRect(x*rate, y*rate, std::min(a,200-x)*rate, std::min(a, 975-y)*rate),grey2);

    for(double x = 2310; x < 2375; x +=2*a)
        for(double y = 580; y < 975; y+=2*a)
            painter.fillRect(QRect(x*rate, y*rate, std::min(a,2375-x)*rate, std::min(a, 975-y)*rate),grey2);

    painter.setPen(pen1);
    painter.drawLine(125*rate, 450*rate, 450*rate, 450*rate);
    painter.drawLine(125*rate, 1100*rate, 450*rate, 1100*rate);
    painter.drawLine(450*rate, 450*rate, 450*rate, 1100*rate);
    painter.drawLine(2375*rate, 1100*rate, 2050*rate, 1100*rate);
    painter.drawLine(2050*rate, 450*rate, 2050*rate, 1100*rate);
    painter.drawLine(2375*rate, 450*rate, 2050*rate, 450*rate);

    painter.drawEllipse(QPointF(1250*rate, 775*rate), 200*rate, 200*rate);
    painter.drawEllipse(QPointF(400*rate, 775*rate), 200*rate, 200*rate);
    painter.drawEllipse(QPointF(2100*rate, 775*rate), 200*rate, 200*rate);
    painter.fillRect(QRect((200-3)*rate, (450+5)*rate, 250*rate, (550-10)*rate),green);
    painter.fillRect(QRect((2375-325+5)*rate, (450+5)*rate, 251*rate, (550-10)*rate),green);

    painter.drawArc(QRectF((125-50)*rate, (250-50)*rate, 100*rate, 100*rate), 270*16, 90*16);
    painter.drawArc(QRectF((2375-50)*rate, (250-50)*rate, 100*rate, 100*rate), 180*16, 90*16);
    painter.drawArc(QRectF((2375-50)*rate, (1300-50)*rate, 100*rate, 100*rate), 90*16, 90*16);
    painter.drawArc(QRectF((125-50)*rate, (1300-50)*rate, 100*rate, 100*rate), 0*16, 90*16);

    painter.setPen(pen2);
    painter.drawLine(125*rate, 575*rate, 200*rate, 575*rate);
    painter.drawLine(125*rate, 975*rate, 200*rate, 975*rate);
    painter.drawLine(200*rate, 575*rate, 200*rate, 975*rate);
    painter.drawLine(2375*rate, 575*rate, 2300*rate, 575*rate);
    painter.drawLine(2375*rate, 975*rate, 2300*rate, 975*rate);
    painter.drawLine(2300*rate, 575*rate, 2300*rate, 975*rate);

    painter.setPen(pen1);
    painter.drawLine(125*rate, 25*rate, 2375*rate, 25*rate);
    painter.drawLine(125*rate, 200*rate, 2375*rate, 200*rate);
    painter.drawLine(125*rate, 250*rate, 2375*rate, 250*rate);
    painter.drawLine(125*rate, 1300*rate, 2375*rate, 1300*rate);
    painter.drawLine(125*rate, 250*rate, 125*rate, 1300*rate);
    painter.drawLine(2375*rate, 250*rate, 2375*rate, 1300*rate);
    painter.drawLine(1250*rate, 250*rate, 1250*rate, 1300*rate);
    painter.drawLine(2375*rate, 25*rate, 2375*rate, 200*rate);
    painter.drawLine(125*rate, 25*rate, 125*rate, 200*rate);

    painter.setBrush(white);
    painter.drawEllipse(QPointF(1250*rate, 775*rate), 10*rate, 10*rate);
    painter.drawEllipse(QPointF((400-100)*rate, 775*rate), 7*rate, 7*rate);
    painter.drawEllipse(QPointF((2100+100)*rate, 775*rate), 7*rate, 7*rate);

    painter.setPen(pen3);
    painter.drawLine(125*rate, 35*rate, 125*rate, 190*rate);
    painter.drawLine(125*rate, 35*rate, 425*rate, 35*rate);
    painter.drawLine(125*rate, 190*rate, 425*rate, 190*rate);
    painter.drawLine(425*rate, 190*rate, 425*rate, 35*rate);

    QFont font("宋体", 19, QFont::Black, false);
    QFont font1("System", 19, QFont::Black, false);

    painter.setFont(font);
    QRect text1(125*rate, 35*rate, 300*rate, 155*rate);
    std::string s1,s2;
    if(map->myscore<10) s1 = "0" + std::to_string(map->myscore);
    else if(map->myscore<100) s1 = std::to_string(map->myscore);
    if(map->enemyscore<10) s2 = "0" + std::to_string(map->enemyscore);
    else if(map->enemyscore<100) s2 = std::to_string(map->enemyscore);
    std::string tmp_s = s1 + ":" + s2;
    if(map->enemyscore>=100) tmp_s = "菜逼";
    if(map->myscore>=100) tmp_s = "真闲";
    painter.drawText(text1, Qt::AlignCenter, tmp_s.c_str());

    QRect text2(450*rate, 35*rate, (2375-470)*rate, 155*rate);
    std::string tmp_s1 = "Press WASD to move, SPACE to jump, TAB back to menu";
    painter.setPen((pen2));
    painter.setFont(font);
    if(map->enemyscore>=100) {tmp_s1 = "怎么会有人玩的这么菜呢？";painter.setPen(pen3);}
    if(map->myscore>=100) {tmp_s1 = "你就没有其他事情要做吗？";painter.setPen(pen3);}
    painter.drawText(text2, Qt::AlignCenter, tmp_s1.c_str());

}



void Intro::paintball(QPainter &painter, QPointF point, double h)
{
    double rate = map->rate;
    QBrush grey(QColor(130,130,130,100));
    QPen pen(grey, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(grey);
    painter.drawEllipse(QPointF(point.x()*rate,point.y()*rate), std::max((double)5, (40-(0.03*h)))*rate*0.85,std::max((double)5, (40-(0.03*h)))*rate*0.85);
    painter.drawImage(QPointF(point.x()*rate-16, point.y()*rate-16.5-h*0.1*rate), image);
}

void Intro::painttiger(QPainter &painter, QPointF point, QPointF spd, double kick_dis)
{
    double rate = map->rate;
    QBrush grey(QColor(130,130,130,100));
    QBrush black(QColor(0,0,0,255));
    QBrush blue(QColor(0,121,241,255));
    QBrush brown(QColor(127,106,79,255));
    QBrush yellow(QColor(253,249,0,255));
    QPen pen(grey, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen1(yellow, 10*rate, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(grey);

    const double pi = acos(-1);
    double angle = atan2(spd.y()*rate, spd.x()*rate);
    double angle1 = atan2(spd.y()*rate, spd.x()*rate)/ pi *180;
    if(angle1<0) angle1 += 360;


    painter.drawEllipse(QPointF(point.x()*rate, point.y()*rate), kick_dis*rate, kick_dis*rate);
    painter.setBrush(black);
    painter.drawEllipse(QPointF(point.x()*rate, point.y()*rate), 6*rate, 6*rate);
    painter.setBrush(blue);
    painter.drawEllipse(QPointF(point.x()*rate + cos(angle - pi/2)*18*rate, point.y()*rate + sin(angle - pi/2)*18*rate),18*rate, 18*rate );
    painter.drawEllipse(QPointF(point.x()*rate - cos(angle - pi/2)*18*rate, point.y()*rate - sin(angle - pi/2)*18*rate),18*rate, 18*rate );
    painter.setBrush(brown);
    painter.drawEllipse(QPointF(point.x()*rate, point.y()*rate), 20*rate, 20*rate);
    painter.setPen(pen1);
    painter.setBrush(yellow);
    painter.drawArc(QRectF(point.x()*rate-15*rate, point.y()*rate-15*rate,30*rate,30*rate), (-1)*(angle1+60)*16 , 120*16);

}

void Intro::painttips(QPainter &painter)
{
    double rate = map->rate;
    QBrush grey(QColor(130,130,130,150));
    QBrush black(QColor(0,0,0,100));
    QPen pen3(black, 10*rate, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen4(grey, 1*rate, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setBrush(grey);
    painter.setPen(pen4);
    std::string k1 = "Press  Q  to  play  animation,  Space  to  skip  animation";
    switch(map->state)
    {
    case 0:
        break;
    case 1:
        break;
    case 2:
        painter.drawRect(125*rate, 1100*rate, 2250*rate, 150*rate);
        painter.setPen(pen3);
        painter.drawText(QRect(125*rate, 1100*rate, 2250*rate, 150*rate),Qt::AlignCenter, k1.c_str());
        break;
    }
}

void Intro::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q&&map->state==2){
        map->state = 0;
        map->show_begin();
    }
    if(event->key() == Qt::Key_Space){
        map->interface_state = 2;
        update();
    }
}

void Intro::timerEvent(QTimerEvent *)
{
    if(map->interface_state!=1) return;
    if(map->state!=2)
    {
    map->ball->player_control(0,0,0,0,0);
    map->ball->bounce();
        if(map->state==0)
        {
            map->tiger_move();
            int goal = map->ball->is_goal();
            map->about_kick();
            if(map->m!=0&&map->state==0) map->if_goal(goal);
        }
    }
    if(map->state==1&&map->ball->spd.x()==0&&map->ball->spd.y()==0)
    {
        if(cnt<=80)cnt++;
    }
    if(cnt==80)
    {
        map->interface_state = 4;
        map->if_tremble = 1;
    }
    update();
}





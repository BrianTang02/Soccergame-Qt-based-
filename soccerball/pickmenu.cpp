#include "Pickmenu.h"

Pickmenu::Pickmenu(QWidget *parent, Map* amp):
    QWidget(parent),
    map(amp)
{
    setFocus();
    //this->grabKeyboard();
    setParent(parent);
    image.load("://cnmb/SoccerBall2.png");
}


void Pickmenu::paintEvent(QPaintEvent *)
{
     QPainter painter(this);

     paintbackground(painter);
     paintball(painter, map->ball->pos, map->ball->h);
     for(int i=0;i<map->tiger_num;i++)
         painttiger(painter, map->tiger[i]->pos, (map->ball->pos-map->tiger[i]->pos), map->tiger[i]->kick_dis);
     painttips(painter);
}

void Pickmenu::paintbackground(QPainter &painter)
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

    QFont font("宋体", 33, QFont::Black, false);
    QFont font1("System", 30, QFont::Black, false);

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

void Pickmenu::paintball(QPainter &painter, QPointF point, double h)
{
    double rate = map->rate;
    QBrush grey(QColor(130,130,130,100));
    QPen pen(grey, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(grey);
    painter.drawEllipse(QPointF(point.x()*rate,point.y()*rate), std::max((double)5, (40-(0.03*h)))*rate*0.85,std::max((double)5, (40-(0.03*h)))*rate*0.85);
    painter.drawImage(QPointF(point.x()*rate-16, point.y()*rate-16.5-h*0.1*rate), image);
}

void Pickmenu::painttiger(QPainter &painter, QPointF point, QPointF spd, double kick_dis)
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

void Pickmenu::painttips(QPainter &painter)
{
    double rate = map->rate;
    QBrush grey(QColor(130, 130, 130, 140));
    QBrush black(QColor(0,0,0,255));
    QBrush red1(QColor(255, 0, 0, 255));
    QBrush red(QColor(191, 42, 42, 255));
    QPen pen(grey, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen1(black, 10*rate, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen2(red1, 10*rate, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen4(black, 8*rate, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QFont font("宋体", 50, QFont::Black, false);
    QFont font1("System", 30, QFont::Black, false);
    QFont font2("System", 25, QFont::Black, false);
    // choose
    painter.setBrush(grey);
    painter.setPen(pen);
    painter.drawRect(125*rate, 200*rate, 2250*rate, 300*rate);
    painter.drawRect(250*rate, 575*rate, 500*rate, 200*rate);
    painter.drawRect(1000*rate, 575*rate, 500*rate, 200*rate);
    painter.drawRect(1750*rate, 575*rate, 500*rate, 200*rate);
    painter.drawRect(250*rate, 875*rate, 500*rate, 200*rate);
    painter.drawRect(1000*rate, 875*rate, 500*rate, 200*rate);
    painter.drawRect(1750*rate, 875*rate, 500*rate, 200*rate);
    // hard
    if(map->hard) painter.setBrush(red);
    else painter.setBrush(grey);
    painter.drawRect(250*rate, 1150*rate, 350*rate, 150*rate);
    // page
    painter.setBrush(grey);
    if(map->now_page!=0) painter.drawRect(1650*rate, 1150*rate, 300*rate, 150*rate);
    if(map->now_page!=map->max_page) painter.drawRect(2050*rate, 1150*rate, 300*rate, 150*rate);
    // interact
    painter.setBrush(grey);
    painter.setPen(pen4);
    painter.drawRect(675*rate, 575*rate, 75*rate, 75*rate);
    painter.drawRect(1425*rate, 575*rate, 75*rate, 75*rate);
    painter.drawRect(2175*rate, 575*rate, 75*rate, 75*rate);
    painter.drawRect(675*rate, 875*rate, 75*rate, 75*rate);
    painter.drawRect(1425*rate, 875*rate, 75*rate, 75*rate);
    painter.drawRect(2175*rate, 875*rate, 75*rate, 75*rate);
    painter.drawRect(525*rate, 1150*rate, 75*rate, 75*rate);
    if(map->now_page!=0)
    painter.drawRect(1875*rate, 1150*rate, 75*rate, 75*rate);
    if(map->now_page!=map->max_page)
    painter.drawRect(2275*rate, 1150*rate, 75*rate, 75*rate);

    std::string a1 = "Level Selection";
    painter.setFont(font);
    painter.setPen(pen1);
    painter.drawText(QRectF(125*rate, 200*rate, 2250*rate, 300*rate), Qt::AlignCenter, a1.c_str());
    std::string a2 = "Level";
    std::string tmp[6];std::string tmp1[10];
    for(int i=1;i<=5;i++){
        char x1 = '0' + (map->now_page*5+i)/10;
        char x2 = '0' + (map->now_page*5+i)%10;

        if(map->now_page*5+i<10) tmp[i] = a2 + " " +"0" +x2;
        else tmp[i] = a2 +" "+ x1 + x2;
    }
    for(int i=1;i<=6;i++){
        char t = '0' +i;
        tmp1[i] = t;
    }
    tmp1[7] = 'Q';tmp1[8] = 'E';tmp1[9] = 'R';
    painter.setFont(font);
    // choose
    if(map->hard) painter.setPen(pen2);
    else painter.setPen(pen1);
    painter.drawText(QRectF(250*rate, 575*rate, 500*rate, 200*rate), Qt::AlignCenter, tmp[1].c_str());
    painter.drawText(QRectF(1000*rate, 575*rate, 500*rate, 200*rate), Qt::AlignCenter, tmp[2].c_str());
    painter.drawText(QRectF(1750*rate, 575*rate, 500*rate, 200*rate), Qt::AlignCenter, tmp[3].c_str());
    painter.drawText(QRectF(250*rate, 875*rate, 500*rate, 200*rate), Qt::AlignCenter, tmp[4].c_str());
    painter.drawText(QRectF(1000*rate, 875*rate, 500*rate, 200*rate), Qt::AlignCenter, tmp[5].c_str());
    std::string a3 = "Freedom";
    painter.setPen(pen1);
    painter.drawText(QRectF(1750*rate, 875*rate, 500*rate, 200*rate), Qt::AlignCenter, a3.c_str());
    // interacrt
    painter.setFont(font2);
    painter.setPen(pen1);
    painter.drawText(QRectF(675*rate, 575*rate, 75*rate, 75*rate), Qt::AlignCenter, tmp1[1].c_str());
    painter.drawText(QRectF(1425*rate, 575*rate, 75*rate, 75*rate), Qt::AlignCenter, tmp1[2].c_str());
    painter.drawText(QRectF(2175*rate, 575*rate, 75*rate, 75*rate), Qt::AlignCenter, tmp1[3].c_str());
    painter.drawText(QRectF(675*rate, 875*rate, 75*rate, 75*rate), Qt::AlignCenter, tmp1[4].c_str());
    painter.drawText(QRectF(1425*rate, 875*rate, 75*rate, 75*rate), Qt::AlignCenter, tmp1[5].c_str());
    painter.drawText(QRectF(2175*rate, 875*rate, 75*rate, 75*rate), Qt::AlignCenter, tmp1[6].c_str());
    painter.drawText(QRectF(525*rate, 1150*rate, 75*rate, 75*rate), Qt::AlignCenter, tmp1[7].c_str());
    if(map->now_page!=0)
    painter.drawText(QRectF(1875*rate, 1150*rate, 75*rate, 75*rate), Qt::AlignCenter, tmp1[8].c_str());
    if(map->now_page!=map->max_page)
    painter.drawText(QRectF(2275*rate, 1150*rate, 75*rate, 75*rate), Qt::AlignCenter, tmp1[9].c_str());
    //hard
    painter.setFont(font1);
    std::string a4 = "Hard";std::string a5 ="Easy";
    if(map->hard){
        painter.setPen(pen1);
        painter.drawText(QRectF(250*rate, 1150*rate, 350*rate, 150*rate), Qt::AlignCenter, a4.c_str());
    }
    else{
        painter.setPen(pen1);
        painter.drawText(QRectF(250*rate, 1150*rate, 350*rate, 150*rate), Qt::AlignCenter, a5.c_str());
    }
    //page
    std::string a6 = "Pre";std::string a7 = "Nex";
    if(map->now_page!=0)
    painter.drawText(QRectF(1650*rate, 1150*rate, 300*rate, 150*rate), Qt::AlignCenter, a6.c_str());
    if(map->now_page!=map->max_page)
    painter.drawText(QRectF(2050*rate, 1150*rate, 300*rate, 150*rate), Qt::AlignCenter, a7.c_str());
}


void Pickmenu::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Q:
        if(event->isAutoRepeat()) return;
        if(map->hard) map->hard = false;
        else map->hard = true;
        break;
    case Qt::Key_E:
        if(event->isAutoRepeat()) return;
        if(map->now_page!=0) map->now_page-=1;
        break;
    case Qt::Key_R:
        if(event->isAutoRepeat()) return;
        if(map->now_page!=map->max_page) map->now_page+=1;
        break;
    case Qt::Key_1:
        map->m = map->now_page*5+1;
        map->init();
        map->myscore = map->enemyscore = 0;
        map->interface_state = 3;
        break;
    case Qt::Key_2:
        map->m = map->now_page*5+2;
        map->init();
        map->myscore = map->enemyscore = 0;
        map->interface_state = 3;
        break;
    case Qt::Key_3:
        map->m = map->now_page*5+3;
        map->init();
        map->myscore = map->enemyscore = 0;
        map->interface_state = 3;
        break;
    case Qt::Key_4:
        map->m = map->now_page*5+4;
        map->init();
        map->myscore = map->enemyscore = 0;
        map->interface_state = 3;
        break;
    case Qt::Key_5:
        map->m = map->now_page*5+5;
        map->init();
        map->myscore = map->enemyscore = 0;
        map->interface_state = 3;
        break;
    case Qt::Key_6:
        map->m = 0;
        map->init();
        map->myscore = map->enemyscore = 0;
        map->interface_state = 3;
        break;
    case Qt::Key_Tab:
        map->interface_state = 3;
        map->state = 2;
    }
}
void Pickmenu::keyReleaseEvent(QKeyEvent *event)
{
    update();
}


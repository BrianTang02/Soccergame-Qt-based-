#include "Mainmenu.h"


Mainmenu::Mainmenu(QWidget *parent, Map* amp):
    QWidget(parent),
    map(amp)
{
    setParent(parent);
    shadow_area = 0;
    setMouseTracking(true);
}


void Mainmenu::paintEvent(QPaintEvent *)
{
     QPainter painter(this);

     QBrush brush(QColor(255,255,255));
     QBrush brush2(QColor(130,130,130,100));
     QRect all(0,0,1750,962.5);
     QRect text1(0,200,1750,120);
     QRect text2(0,340,1750,120);
     QRect text3(750,530,250,100);
     QRect text4(750,670,250,100);
     QFont font1("宋体", 45, QFont::Black, false);
     QFont font2("System", 61, QFont::Black, false);
     font2.setLetterSpacing(QFont::AbsoluteSpacing, 4);
     font2.setPointSizeF(100);
     font2.setPixelSize(60);

     painter.setBrush(brush);
     painter.drawRect(all);
     painter.setPen(Qt::black);
     painter.drawRect(text3);
     painter.drawRect(text4);

     switch(shadow_area){
     case 0:
         break;
     case 1:
         painter.fillRect(text3,brush2);
         break;
     case 2:
         painter.fillRect(text4,brush2);
         break;
     }

     painter.setFont(font1);
     painter.drawText(text1, Qt::AlignCenter, tr("An Ordinary Match"));
     painter.drawText(text2, Qt::AlignCenter, tr("But I'm the Ball"));
     painter.setFont(font2);
     painter.drawText(text3, Qt::AlignCenter, tr("Start"));
     painter.drawText(text4, Qt::AlignCenter, tr("Exit"));
}

bool Mainmenu::check_in_rect(double x1,double y1,double w,double h, QPoint point)
{
    if(point.x()<=x1||point.x()>=x1+w) return false;
    if(point.y()<=y1||point.y()>=y1+h) return false;
    return true;
}

int Mainmenu::check_in_button(QPoint point)
{
    if(check_in_rect(750,530,250,100,point)) return 1;
    if(check_in_rect(750,670,250,100,point)) return 2;
    else return 0;
}

void Mainmenu::mousePressEvent(QMouseEvent *Mouse)
{
    if(Mouse->button() == Qt::LeftButton){
        switch(check_in_button(Mouse->pos())){
        case 1:
            map->show_init();
            map->interface_state = 1;
            break;
        case 2:
            break;
        case 0:
            break;
        }
    }
    update();
}

void Mainmenu::mouseMoveEvent(QMouseEvent *Mouse)
{

    shadow_area = check_in_button(Mouse->pos());
    update();
}

void Mainmenu::mouseReleaseEvent(QMouseEvent *){update();}


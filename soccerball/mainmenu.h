#pragma once
#include <Header.h>

#include "Map.h"

class Mainmenu : public QWidget
{
    friend class Interface;
    Q_OBJECT

public:
    int shadow_area;
    Map* map;
    explicit Mainmenu(QWidget *parent = 0, Map* amp = 0);

protected:

    void paintEvent(QPaintEvent *)Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *Mouse);
    void mouseMoveEvent(QMouseEvent *Mouse);
    void mouseReleaseEvent(QMouseEvent *);

    bool check_in_rect(double x1,double y1,double w,double h,QPoint point);
    int check_in_button(QPoint point);
};




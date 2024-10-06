#pragma once

#include <QWidget>
#include "Map.h"
#include "Mainmenu.h"
#include "Intro.h"
#include "Pickmenu.h"
#include "Play.h"
#include "Tremble.h"

class Interface : public QWidget
{
    Q_OBJECT
public:
    static double interface_x,interface_y;
    Map* map;
    Mainmenu* mainmenu;
    Intro* intro;
    Tremble* tremble;
    Pickmenu* pickmenu;
    Play* play;

    explicit Interface(QWidget *parent = 0);
    ~Interface();

    void paintEvent(QPaintEvent *)Q_DECL_OVERRIDE;
    int Timer;
    void tremb();


protected:
    void mousePressEvent(QMouseEvent *Mouse);
    void mouseMoveEvent(QMouseEvent *Mouse);
    void mouseReleaseEvent(QMouseEvent *Mouse);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *)Q_DECL_OVERRIDE;
};


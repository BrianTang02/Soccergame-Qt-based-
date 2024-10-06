#pragma once

#include <Header.h>

#include "Map.h"

class Pickmenu : public QWidget
{
    friend class Interface;
    Q_OBJECT

public:
    QImage image;
    Map* map;
    explicit Pickmenu(QWidget *parent = 0, Map* amp = 0);

protected:

    void paintEvent(QPaintEvent *)Q_DECL_OVERRIDE;

    void paintbackground(QPainter& painter);
    void paintball(QPainter& painter, QPointF point, double h);
    void painttiger(QPainter& painter, QPointF point, QPointF spd, double kick_dis);
    void painttips(QPainter& painter);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};


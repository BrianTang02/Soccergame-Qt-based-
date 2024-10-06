#pragma once
#include <Header.h>

#include "Map.h"

class Tremble: public QWidget
{
    friend class Interface;
    Q_OBJECT

public:
    QImage image;
    Map* map;
    explicit Tremble(QWidget *parent = 0, Map* amp = 0);

protected:
    void paintEvent(QPaintEvent *)Q_DECL_OVERRIDE;
    void paintbackground(QPainter& painter);
    void paintball(QPainter& painter, QPointF point, double h);
    void painttips(QPainter& painter);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *);

    void timerEvent(QTimerEvent *)Q_DECL_OVERRIDE;

private:
    int Timer;
    int cnt;

};






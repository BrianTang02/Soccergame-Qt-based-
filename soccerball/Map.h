#pragma once

#include "Header.h"
#include<bits/stdc++.h>
#include "Ball.h"
#include "Tiger.h"
#include "Sound.h"


class Map
{    
    friend class Interface;
    friend class Mainmenu;
    friend class Intro;
    friend class Tremble;
    friend class Pickmenu;
    friend class Play;
public:
    int interface_state;// 开始游戏处于的界面
    double rate;// 缩放
    int now_page, max_page;
    int if_tremble;


    int myscore,enemyscore;
    int m;
    int state;
    bool hard;

    static QPointF ball_start_pos;

    int tiger_num;


    Ball* ball;
    Tiger* tiger[30];

    Map();
    ~Map();
    void init();
    void begin_match();
    void show_init();
    void show_begin();

    double dis(QPointF a,QPointF b);
    static bool cmp (Tiger*, Tiger*);

    void tiger_move();
    void about_kick();
    void if_goal(int goal);

    Sound_check *Snd;

};


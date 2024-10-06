#pragma once

#include "Header.h"

class Ball {
    public:
        friend class Map;
        friend class Interface;
        friend class Mainmenu;
        friend class Intro;
        friend class Tremble;
        friend class Pickmenu;
        friend class Play;

        static double fps_rate;

        static double f_ground, f_sky, f_h;//阻力
        static double max_spd_ground; //地面最大速度
        static double delta_acc_ground, delta_acc_sky; //最大玩家施加加速度
        static double max_ground_x, max_ground_y, min_ground_x, min_ground_y; //地图范围

        Ball();
        void init(QPointF start_pos);		//初始化
        void begin_match();		//改变为可移动状态

        void update_spd(); //更新速度
        void update_pos(); //更新位置
        int is_goal(); //判定是否进球
        void bounce(); //反弹

        //键盘交互
        void interact_wasd(int w, int a, int s, int d);
        void interact_jump(int start_h_spd);
        void player_control(int w, int a, int s, int d, int kongge);

        //被踢
        void be_kicked(QPointF new_pos, double new_h_spd, double new_spd);

    private:
        QPointF pos;//位置
        QPointF spd;//速度
        QPointF acc;//加速度
        double h, h_spd;//z轴位置，速度
        bool can_move;//能否移动
};

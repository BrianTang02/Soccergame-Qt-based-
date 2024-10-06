#include "Map.h"

QPointF Map::ball_start_pos = {300, 775};

Map::Map()
{
    interface_state = 0;
    rate = 0.7;
    now_page = 0, max_page = 1;
    if_tremble = 0;

    state = 2;
    myscore = 0, enemyscore = 0;
    ball = new Ball;
    for(int i=0;i<30;i++) tiger[i] = new Tiger;
    m = 1  , hard = false;
    tiger_num = 5;

    Snd = new Sound_check();
}

Map::~Map(){}


void Map::init() {
        state = 2;
        //改变球相关
        ball->init(ball_start_pos);
        switch(m){
        case 0:
                ball->delta_acc_sky = 2;
                ball->max_spd_ground = 12;
                ball->f_sky = 0.1;
        break;
        default:
                ball->delta_acc_sky = 1;
                ball->max_spd_ground = 10;
                ball->f_sky = 0.1;
        break;
        }
        //改变球员人数
        switch(m){
        case 0:
                tiger_num = 0;
        break;
        case 4:
                tiger_num = 1;
        break;
        case 5:
                if(hard) tiger_num = 15;
                else tiger_num = 10;
        break;
        case 7:
                tiger_num = 9;
        break;
        default:
                tiger_num = 5;
        }
        //改变球员位置
        switch(m){
        case 0:
        break;
        case 2:
                tiger[0]->init({1450, 650});
                tiger[1]->init({1450, 900});
                tiger[2]->init({1700, 775});
                tiger[3]->init({1950, 650});
                tiger[4]->init({1950, 900});
        break;
        case 4:
                tiger[0]->init({1650, 775});
        break;
        case 5:
                tiger[0]->init({1650, 550});
                tiger[1]->init({1650, 775});
                tiger[2]->init({1650, 1000});
                tiger[3]->init({1950, 650});
                tiger[4]->init({1950, 900});
                tiger[5]->init({1750, 650});
                tiger[6]->init({1750, 900});
                tiger[7]->init({1850, 550});
                tiger[8]->init({1850, 775});
                tiger[9]->init({1850, 1000});
                if(hard){
                        tiger[10]->init({1550, 650});
                        tiger[11]->init({1550, 900});
                        tiger[12]->init({1450, 550});
                        tiger[13]->init({1450, 775});
                        tiger[14]->init({1450, 1000});
                }
        break;
        case 6:
                tiger[0]->init({1450, 650});
                tiger[1]->init({1450, 900});
                tiger[2]->init({1700, 775});
                tiger[3]->init({1950, 650});
                tiger[4]->init({1950, 900});
        break;
        case 7:
                tiger[0]->init({1650, 655});
                tiger[1]->init({1650, 775});
                tiger[2]->init({1650, 895});
                tiger[3]->init({1650, 1015});
                tiger[4]->init({1650, 535});
                tiger[5]->init({1650, 1135});
                tiger[6]->init({1650, 415});
                tiger[7]->init({1650, 295});
                tiger[8]->init({1650, 1255});
        break;
        default:
                tiger[0]->init({1650, 550});
                tiger[1]->init({1650, 775});
                tiger[2]->init({1650, 1000});
                tiger[3]->init({1950, 650});
                tiger[4]->init({1950, 900});
        }
        // 改变球员球速
        switch(m){
        case 6:
                if(hard)for (int i = 0; i < tiger_num; i++) tiger[i]->kick_out_spd = 150;
                else for (int i = 0; i < tiger_num; i++) tiger[i]->kick_out_spd = 120;
        break;
        case 9:{
                for (int i = 0; i < tiger_num; i++) tiger[i]->kick_out_spd = 10;
        }
        default:
                for (int i = 0; i < tiger_num; i++) tiger[i]->kick_out_spd = 50;
        break;
        }
        // 改变球员攻击范围
        switch(m){
        case 6:
                if(hard) for (int i = 0; i < tiger_num; i++) tiger[i]->kick_dis = 100;
                else for (int i = 0; i < tiger_num; i++) tiger[i]->kick_dis = 80;
        break;
        default:
                for (int i = 0; i < tiger_num; i++) tiger[i]->kick_dis = 60;
        break;
        }
}


double Map::dis(QPointF a, QPointF b) {
        return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}

bool Map::cmp(Tiger* e, Tiger* f) {
        return e->pos.x() * e->pos.x() + e->pos.y() * e->pos.y() <
               f->pos.x() * f->pos.x() + f->pos.y() * f->pos.y();
}


void Map::tiger_move() {
        double x0 = ball->pos.x(), y0 = ball->pos.y();
        for (int i = 0; i < tiger_num; i++) tiger[i]->pos -= ball->pos;
        std::sort(tiger, tiger + tiger_num, cmp);
        for (int i = 0; i < tiger_num; i++) tiger[i]->pos += ball->pos;
        double x1 = tiger[0]->pos.x(), y1 = tiger[0]->pos.y();
        double x2 = tiger[1]->pos.x(), y2 = tiger[1]->pos.y();
        switch (m) {
                case 0:
                break;
                case 1:
                        for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 5;
                        if (hard) for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 10;
                        tiger[0]->update_spd({x0, y0});
                        tiger[1]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
                        tiger[2]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
                        tiger[3]->update_spd({(x0 + 2375) / 2, (y0 + 975) / 2});
                        tiger[4]->update_spd({(x0 + 2375) / 2, (y0 + 575) / 2}); // 3+2阵型
                break;
                case 2:
                        for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 7;
                        if (hard) for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 9;
                        tiger[0]->update_spd({x0, y0});
                        if ((x0 - x2) * (y1 - y2) - (y0 - y2) * (x1 - x2) >= 0) tiger[1]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
                        else tiger[1]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
                        tiger[2]->update_spd({(x0 * 3 + 2375) / 4, (y0 * 3 + 775) / 4});
                        if (tiger[3]->pos.y() <= tiger[4]->pos.y()) {
                                Tiger* tmp = tiger[3];
                                tiger[3] = tiger[4];
                                tiger[4] = tmp;
                        }
                        tiger[3]->update_spd({(x0 + 2375) / 2, (y0 + 1100) / 2});
                        tiger[4]->update_spd({(x0 + 2375) / 2, (y0 + 450) / 2}); //2+2+1阵型
                break;
                case 3:
                        for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 8;
                        if (hard) for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 10;
                        tiger[0]->update_spd({x0, y0});
                        if (dis(tiger[1]->pos, {x0 - y0 + y1, x0 + y0 - x1}) >= dis(tiger[1]->pos, {x0 + y0 - y1, -x0 + y0 + x1})) {
                                Tiger* tmp = tiger[1];
                                tiger[1] = tiger[2];
                                tiger[2] = tmp;
                        }
                        tiger[1]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
                        tiger[2]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
                        tiger[3]->update_spd({(x0 + 2375) / 2, (y0 + 975) / 2});
                        tiger[4]->update_spd({(x0 + 2375) / 2, (y0 + 575) / 2}); // 3+2阵型
                break;
                case 4:
                        tiger[0]->max_spd_ground = 10;
                        if (hard) {
                                tiger[0]->max_spd_ground = 12;
                                tiger[0]->kick_out_spd = 60;
                        }
                        if (tiger[0]->pos.x() >= x0)tiger[0]->update_spd({(x0 + tiger[0]->pos.x()) / 2, y0});
                        else tiger[0]->update_spd({(x0 + 2375) / 2, y0}); //11速能力者
                break;
                case 5:
                        for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 7;
                        for (int i = 0; i < tiger_num; ++i) tiger[i]->kick_out_spd = 50;
                        tiger[0]->update_spd({x0, y0});
                        if (dis(tiger[1]->pos, {x0 - y0 + y1, x0 + y0 - x1}) >= dis(tiger[1]->pos, {x0 + y0 - y1, -x0 + y0 + x1})) {
                                Tiger* tmp = tiger[1];
                                tiger[1] = tiger[2];
                                tiger[2] = tmp;
                        }
                        tiger[1]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
                        tiger[2]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
                        tiger[3]->update_spd({(x0 + 2375) / 2, (y0 + 975) / 2});
                        tiger[4]->update_spd({(x0 + 2375) / 2, (y0 + 575) / 2});
                        for (int i = 5; i < tiger_num; ++i) {
                                tiger[i]->spd = {0, 0};
                        }
                break;
                case 6:
                        for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 6;
                        if (hard) for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 8;
                        tiger[0]->update_spd({x0, y0});
                        if ((x0 - x2) * (y1 - y2) - (y0 - y2) * (x1 - x2) >= 0) tiger[1]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
                        else tiger[1]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
                        tiger[2]->update_spd({(x0 * 3 + 2375) / 4, (y0 * 3 + 775) / 4});
                        if (tiger[3]->pos.y() <= tiger[4]->pos.y()) {
                                Tiger* tmp = tiger[3];
                                tiger[3] = tiger[4];
                                tiger[4] = tmp;
                        }
                        tiger[3]->update_spd({(x0 + 2375) / 2, (y0 + 1100) / 2});
                        tiger[4]->update_spd({(x0 + 2375) / 2, (y0 + 450) / 2}); //2+2+1阵型
                break;
                case 7:
                        for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 8;
                        if (hard) for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 9;
                        tiger[0]->update_spd({x0, y0});
                        if (dis(tiger[1]->pos, {x0 - y0 + 0.5*y1, x0 + y0 - 0.5*x1}) >= dis(tiger[1]->pos, {x0 + y0 - 0.5*y1, -x0 + y0 + 0.5*x1})) {
                                Tiger* tmp = tiger[1];
                                tiger[1] = tiger[2];
                                tiger[2] = tmp;
                        }
                        tiger[1]->update_spd({x0 - y0 + 0.5*y1, x0 + y0 - 0.5*x1});
                        tiger[2]->update_spd({x0 + y0 - 0.5*y1, -x0 + y0 + 0.5*x1});
                        if (dis(tiger[5]->pos, {x0 - y0 + 1.5*y1, x0 + y0 - 1.5*x1}) >= dis(tiger[6]->pos, {x0 + y0 - 1.5*y1, -x0 + y0 + 1.5*x1})) {
                                Tiger* tmp = tiger[5];
                                tiger[5] = tiger[6];
                                tiger[6] = tmp;
                        }
                        tiger[5]->update_spd({x0 - y0 + 1.5*y1, x0 + y0 - 1.5*x1});
                        tiger[6]->update_spd({x0 + y0 - 1.5*y1, -x0 + y0 + 1.5*x1});
                        if (dis(tiger[7]->pos, {x0 - y0 + 2*y1, x0 + y0 - 2*x1}) >= dis(tiger[8]->pos, {x0 + y0 - 2*y1, -x0 + y0 + 2*x1})) {
                                Tiger* tmp = tiger[7];
                                tiger[7] = tiger[8];
                                tiger[8] = tmp;
                        }
                        tiger[7]->update_spd({x0 - y0 + 2*y1, x0 + y0 - 2*x1});
                        tiger[8]->update_spd({x0 + y0 - 2*y1, -x0 + y0 + 2*x1});
                        if (dis(tiger[3]->pos, {x0 - y0 + y1, x0 + y0 - x1}) >= dis(tiger[4]->pos, {x0 + y0 - y1, -x0 + y0 + x1})) {
                                Tiger* tmp = tiger[3];
                                tiger[3] = tiger[4];
                                tiger[4] = tmp;
                        }
                        tiger[3]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
                        tiger[4]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
                break;
                case 8:
                            for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 7;
                        if (hard) for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 9;
                        tiger[0]->update_spd({x0, y0});
                        if ((x0 - x2) * (y1 - y2) - (y0 - y2) * (x1 - x2) >= 0) tiger[1]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
                        else tiger[1]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
                        tiger[2]->update_spd({(x0 * 3 + 2375) / 4, (y0 * 3 + 775) / 4});
                        if (tiger[3]->pos.y() <= tiger[4]->pos.y()) {
                                Tiger* tmp = tiger[3];
                                tiger[3] = tiger[4];
                                tiger[4] = tmp;
                        }
                        tiger[3]->update_spd({(x0 + 2375) / 2, (y0 + 1100) / 2});
                        tiger[4]->update_spd({(x0 + 2375) / 2, (y0 + 450) / 2}); //2+2+1阵型
                break;
                case 9:
                        for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 8;
                        if (hard) for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 10;
                        tiger[0]->update_spd({x0, y0});
                        if (dis(tiger[1]->pos, {x0 - y0 + y1, x0 + y0 - x1}) >= dis(tiger[1]->pos, {x0 + y0 - y1, -x0 + y0 + x1})) {
                                Tiger* tmp = tiger[1];
                                tiger[1] = tiger[2];
                                tiger[2] = tmp;
                        }
                        tiger[1]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
                        tiger[2]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
                        tiger[3]->update_spd({(x0 + 2375) / 2, (y0 + 975) / 2});
                        tiger[4]->update_spd({(x0 + 2375) / 2, (y0 + 575) / 2}); // 3+2阵型
                break;
                default:
                break;
        }

        for (int i = 0; i < tiger_num; i++) tiger[i]->update_pos();
}

void Map::about_kick() {
        double mindis = 2000;
        bool be_kicked = false;
        int kick_man = -1;
        for (int i = 0; i < tiger_num; i++) {
                if (dis(tiger[i]->pos, ball->pos) <= mindis && tiger[i]->can_kick) {
                        mindis = dis(tiger[i]->pos, ball->pos);
                        if (mindis <= tiger[i]->kick_dis) {
                                be_kicked = true;
                                kick_man = i;
                        }
                }
        }
        if (be_kicked)
        switch (m){
        case 8:{
            int t,min_x = 9999;
            double kick_out_rate = (hard) ?0.3:0.5;
            for(int i=0;i<tiger_num;++i) if (tiger[i]->pos.x() < min_x) {min_x = tiger[i]->pos.x(); t = i;}
            if (t != kick_man) ball->be_kicked(tiger[t]->pos, 40, kick_out_rate*tiger[kick_man]->kick_out_spd);
            else ball->be_kicked({125, 775}, 40, tiger[kick_man]->kick_out_spd);
            break;
        }
        default:
            ball->be_kicked({125, 775}, 40, tiger[kick_man]->kick_out_spd);
        }
}


void Map::if_goal(int goal) {
        if (goal == 0) return;
        if (goal == 1){
            myscore++;
            Snd->ply(6);
        }
        if (goal == -1){
            enemyscore++;
            Snd->ply(3);
        }
        for (int i = 0; i < tiger_num; i++) {
                tiger[i]->stop();
        }
        ball->can_move = false;
        state++;
        state %= 3;
}

void Map::begin_match() {
        if(Snd->che(4))Snd->ply(4);
        for (int i = 0; i < tiger_num; i++) {
                tiger[i]->begin_match();
        }
        ball->begin_match();
}

void Map::show_init(){
    ball->init(QPoint(1150,775));
    //tiger[1]->init(QPoint(1350, 775));
}

void Map::show_begin(){
    ball->begin_match();
    for(int i=0;i<tiger_num;i++) tiger[i]->max_spd_ground = 3;
    tiger[1]->kick_out_spd = 140;
    tiger[1]->begin_match();
}



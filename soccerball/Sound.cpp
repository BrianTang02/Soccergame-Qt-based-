#include "Sound.h"

Sound_check::Sound_check(){

    effect1 = new QSoundEffect(this);
    effect1->setVolume(0.25f);
    effect1->setSource(QUrl("qrc:///1/song18.wav"));

    effect2 = new QSoundEffect(this);
    effect2->setVolume(0.25f);
    effect2->setSource(QUrl("qrc:///1/fight.wav"));

    effect3 = new QSoundEffect(this);
    effect3->setVolume(0.25f);
    effect3->setSource(QUrl("qrc:///1/horror_lose_.wav"));

    effect4 = new QSoundEffect(this);
    effect4->setVolume(0.15f);
    effect4->setSource(QUrl("qrc:///1/face_the_facts.wav"));

    effect5 = new QSoundEffect(this);
    effect5->setVolume(0.25f);
    effect5->setSource(QUrl("qrc:///1/coach_whistle.wav"));

    effect6 = new QSoundEffect(this);
    effect6->setVolume(0.25f);
    effect6->setSource(QUrl("qrc:///1/crowd_applause.wav"));

    for(int i=0;i<9;i++)b[i]=true;
    playing = 0;

}

bool Sound_check::che(int x){return b[x];}

void Sound_check::ply(int x){
    for(int i=0;i<9;i++)b[i]=true;
    switch(playing){
    case 1: effect1->stop();break;
    case 2: effect2->stop();break;
    case 3: effect3->stop();break;
    case 4: if(x!=3&&x!=6) effect4->stop();break;
    case 5: effect5->stop();break;
    case 6: effect6->stop();break;
    }

//    if(effect1->isPlaying())effect1->stop();
//    if(effect2->isPlaying())effect2->stop();
//    if(effect3->isPlaying())effect3->stop();
//    if(effect4->isPlaying())effect4->stop();
//    if(effect5->isPlaying())effect5->stop();
//    if(effect6->isPlaying())effect6->stop();
    switch(x){
        case 1: effect1->play(); break;
        case 2: effect2->play(); break;
        case 3: effect3->play(); break;
        case 4: effect4->play(); break;
        case 5: effect5->play(); break;
        case 6: effect6->play(); break;
    }
    b[x]=false;
    if(x!=3&&x!=6) playing = x;
}

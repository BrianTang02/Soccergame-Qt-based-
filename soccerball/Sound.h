#include <QWidget>
#include "Header.h"

class Sound_check : public QWidget{
    Q_OBJECT
public:
    bool b[9];
    QSoundEffect *effect1;
    QSoundEffect *effect2;
    QSoundEffect *effect3;
    QSoundEffect *effect4;
    QSoundEffect *effect5;
    QSoundEffect *effect6;
    QSoundEffect *effect7;

    Sound_check();
    bool che(int x);
    void ply(int x);
    int playing;
};

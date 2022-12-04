#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Battle.h"

using namespace sf;
using namespace std;

class Calibration
{
public:
    Calibration();
    void activate(Display display); 
    void handleInput(); //detect the moment of user calibration
    void update();
    Sprite* getSprite();
    bool getIsActive(); //menu is active
    bool getIsDone(); //choices are ready

private:
    Sprite *m_sprite; //calibration message
    bool m_active;
    bool m_done;

    const int CALIBRATION_WIDTH = 700;
};

#endif
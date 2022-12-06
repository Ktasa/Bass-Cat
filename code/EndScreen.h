#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <SFML/Graphics.hpp>
#include "Character.h"
#include <iostream>

using namespace sf;
using namespace std;

class EndScreen
{
public:
    EndScreen();
    void activate(PlayerID victor); 
    void handleInput(); //detect input to reset game
    void update();
    Sprite* getSprite();
    bool getIsActive(); 
    bool getIsDone(); 
    void setColor(Color color);

private:
    Sprite *m_sprite;
    bool m_active;
    bool m_done;

    const int SCREEN_WIDTH = 1920;
};

#endif
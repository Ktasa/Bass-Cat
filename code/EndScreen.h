#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    Sprite* getSprite();
    Sprite* getVictorySprite();
    void setColor(Color color);

private:
    Sprite *m_sprite;
    Sprite *m_victory; //victory text 
    SoundBuffer m_victorySFXBuffer;
    Sound m_victorySFX;
    bool m_active;
    

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
};

#endif
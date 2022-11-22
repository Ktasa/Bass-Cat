#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
using namespace sf;

class Engine
{
private:

    RenderWindow m_Window;

    View m_mainView; 
    View m_HudView; //HUD
    View m_BgView; //background

    //TextureHolder th;

    //include constants needed throughout the program

    //is the game playing or paused / menu
    bool m_Playing = false;

    //include any basic variables to determine
    //the state of the program

    //what is the current time of a battle
    Time m_BattleTimeTotal;

    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    Engine();

    void run();

};
#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Character.h"
#include "Battle.h"
#include "Menu.h"

using namespace sf;

class Engine
{
private:
    Character* player1;
    //Character* player2;

    Battle* battle;
    Menu* menu;

    RenderWindow m_Window;

    View m_mainView; 
    View m_HudView; //HUD
    View m_BgView; //background

    TextureHolder th;

    //background sprite/texture
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

    //include constants needed throughout the program

    //is the game playing or paused / menu
    bool m_Playing = false;

    //include any basic variables to determine
    //the state of the program

    Time m_GameTimeTotal;

    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    Engine();

    void run();

};
#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Character.h"
#include "Battle.h"
#include "Menu.h"
#include "Rhythm.h"

//#include "Note.h"

using namespace sf;

class Engine
{
private:
    //Character* player1;
    //Character* player2;

    Battle* battle;
    Menu* menu;

    RenderWindow m_Window;

    View m_mainView; 
    //View m_HudView; //HUD
    //View m_BgView; //background

    TextureHolder th;

    //background sprite/texture
	Sprite *m_backgroundSprite;
	//Texture m_BackgroundTexture;

    //include constants needed throughout the program

    //is the game playing or paused / menu
    bool m_Playing = false;

    //include any basic variables to determine
    //the state of the program

    void input();
    void update(float dtAsSeconds);
    void draw();

    //private helpers for draw 
    void displayBackground();
    void displayEffects();
    void displayCharacters();
    void displayStatusBars();
    void displayRhythmBars();
    void displayRhythmTester();
    void displayInterface();
    void displayEndScreen();

public:
    Engine();

    void run();

};
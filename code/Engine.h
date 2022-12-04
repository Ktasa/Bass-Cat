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

    //for testing rhythm input
    Rhythm *rhythm1, *rhythm2;
    //int m_midiTime;
    Time m_battleTime; //keep track of time from start of battle
    bool m_battleTimeActive;
    //80bpm is 0.75 seconds per beat
    //midi clock for this song is 480 ticks per beat
    //that means... 640 ticks per second
    //*ticks per second is not always consistent between midi files with different tempos
    const double TICKS_PER_SECOND = 640.0;
    const double SECONDS_PER_TICK = 1.0 / 640.0;

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

    Time m_GameTimeTotal;

    void input();
    void update(float dtAsSeconds);
    void draw();

    //private helper for draw - displays rhythm tester that flashes back recorded input
    void displayRhythmTester();

public:
    Engine();

    void run();

};
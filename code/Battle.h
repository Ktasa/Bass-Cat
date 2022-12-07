#ifndef BATTLE_H
#define BATTLE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Song.h"
#include "Track.h"
#include "Note.h"
#include "Rhythm.h"
#include "Character.h"
#include "CombatMenu.h"
#include "StatusBar.h"
#include "Effect.h"
#include "Calibration.h"
#include "EndScreen.h"

using namespace sf;
using namespace std;

//forward definitions prevent compile errors in Battle class
class StatusBar;
class CombatMenu;
class Effect;
class RhythmBar;
class Calibration;
class Rhythm;
class EndScreen;

enum BattleState
{
    INACTIVE,
    CALIBRATE, //sequence to sync audio with user input if necessary
    MENU, //awaiting user selection of combat options
    INPUT, //rhythm input
    EFFECT,
    ENDSCREEN
};

enum Display{LIGHT, DARK, GALAXY}; //black or white background/sprites
//enum CombatType{NO_SELECTION, ATTACK, BLOCK, BUILD_METER, MAGIC_ATTACK,}; //moved to CombatMenu.h
//enum EffectType{MAGIC, DAMAGE};

//The game engine will have a battle object, accessing everything through there?

class Battle
{
public:
    Time m_battleTime; //keep track of time from start of battle
    bool m_activeTime;

    Battle();
    void setChoices(vector<int> choices);

    Color getBackground(); //use in draw()    
    Display getDisplay(); //background depends on display setting
    Sprite* getCharacterSprite(PlayerID id); //better to get sprite pointers?
    Sprite* getEffectSprite(PlayerID id);
    Sprite* getCombatMenuSprite();
    Sprite* getCalibrationSprite();
    Sprite* getEndScreenSprite();
    Sprite* getEndScreenText();
    vector<RectangleShape*> getStatusBars(PlayerID id);
    vector<RectangleShape*> getRhythmBar();

    bool getIsCalibrated();
    void handleInput();
    void update(float dtAsSeconds); //update all objects within
    //void drawBattle(RenderWindow &window); //probably not using
    
    BattleState getState();
    void setState(BattleState state); //maybe have an outside function that manages the battle loop

    //move to private
    void setEffectActivity(PlayerID id, EffectType effect, bool active, bool rainbow);
    bool getIsEffectActive(PlayerID id, EffectType effect);
    void setEffects(); //use in Battle::update()

    CombatType getCombatType(PlayerID id);
    void combatAction();

    //functions to handle rhythm input stuff
    bool getIsInputDone(); //[done for both players]
    bool getIsInputActive(); 
    RectangleShape* getRhythmTester(PlayerID id);

    double getScore(PlayerID player); //return score/100.0 of an input session

    int getCurrentTicks();

private:
    //bool m_recordingInput;
    
    //Sprite* background; 
    Character *m_p1, *m_p2;
    Effect *m_magic1, *m_magic2, *m_damage1, *m_damage2;
    //Effect *m_effect1, *m_effect2;
    StatusBar *m_status1, *m_status2;

    Calibration *m_calibration;
    CombatMenu *m_combatMenu; //menu specifically for battle options
    EndScreen *m_endScreen;

    CombatType m_combat1, m_combat2; //player action choices
    double m_scoreP1, m_scoreP2; //store scores for the turn

    Song *m_song;
    Rhythm *m_input1, *m_input2; //store user input as Note data
    RhythmBar *m_bar; //I hope to display a scrolling sequence of notes with simple lines over a box

    Display m_display;
    BattleState m_state;
    //PlayerID m_turn; //whose turn is active

    //helper functions for update() based on BattleState
    void updateTime();
    void updateEndScreen();
    void updateCalibrate();
    void updateMenu();
    void updateInput();
    void updateEffect();

    //functions to calculate input scores
    void calculateScores();
    double calculateScore(Rhythm* input, int track);

    double getMultiplier(CombatType type); //help calc battle damage
};

#include "Song.h"
class RhythmBar
{
public:
    RhythmBar();
    //void loadNotes(vector<Note*> notes);
    void setRange(int units);
    vector<RectangleShape*> getRects();

private:
    vector<RectangleShape*> m_rects;
    int unitsToDisplay = 480 * 8; //range of note units to be displayed

};

#endif
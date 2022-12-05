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

using namespace sf;
using namespace std;

//forward definitions prevent compile errors in Battle class
class StatusBar;
class CombatMenu;
class Effect;
class RhythmBar;
class Calibration;
class Rhythm;

enum BattleState
{
    INACTIVE,
    CALIBRATE, //sequence to sync audio with user input if necessary
    MENU, //awaiting user selection of combat options
    INPUT, //rhythm input
    EFFECT,
    ENDSCREEN
};

enum Display{LIGHT, DARK}; //black or white background/sprites
//enum CombatType{NO_SELECTION, ATTACK, BLOCK, BUILD_METER, MAGIC_ATTACK,}; //moved to CombatMenu.h
//enum EffectType{MAGIC, DAMAGE};

//The game engine will have a battle object, accessing everything through there?

class Battle
{
public:
    Battle();
    void setChoices(vector<int> choices);

    Color getBackground(); //use in draw()    
    Sprite* getCharacterSprite(PlayerID id); //better to get sprite pointers?
    //Sprite getEffectSprite(PlayerID id, EffectType effect);
    Sprite* getEffectSprite(PlayerID id);
    Sprite* getCombatMenuSprite();
    Sprite* getCalibrationSprite();
    vector<RectangleShape*> getStatusBars(PlayerID id);
    vector<RectangleShape*> getRhythmBar();

    int getScore(Track& input, int midiTime); //return int score/100 of an input session
    //^^param midiTime unecessary bevause input will include start val?
    //^^need to store recording time somewhere
    void setScore(PlayerID id, int score);
    //void combatAction(PlayerID id, CombatType type, int score);

    bool getIsCalibrated();
    void handleInput();
    void update(float dtAsSeconds); //update all objects within
    void drawBattle(RenderWindow &window); //probably not using
    
    BattleState getState();
    void setState(BattleState state); //maybe have an outside function that manages the battle loop

    //these are kind of bad, not good for working in engine
    void setEffectActivity(PlayerID id, EffectType effect, bool active);
    bool getIsEffectActive(PlayerID id, EffectType effect);

    //CombatType getCombatType(PlayerID id);

    //functions to handle rhythm input stuff
    //put handleInput inside battle::handleInput
    //activate from inside
    //update from inside
    //void getIsInputDone(); //[done for both players]
    //void getIsInputActive(); 
    //RectangleShape* getRhythmTester();

private:
    bool m_recordingInput;
    
    //Sprite background; //(these can cause hard lag... must be because full screen display?)
    
    //might be best to use pointers for all these class objects with lots of data
    Character *m_p1, *m_p2;

    //all these object pairs for each character, might be best to move to character class
    StatusBar *m_status1, *m_status2;
    CombatMenu *m_combatMenu; //menu specifically for battle options
    Effect *m_magic1, *m_magic2, *m_damage1, *m_damage2;
    //Effect *m_effect1, *m_effect2;

    RhythmBar *m_bar; //I hope to display a scrolling sequence of notes with simple lines over a box
    
    //Text m_text; //use to announce actions

    PlayerID m_turn; //whose turn is active

    Display m_display;

    BattleState m_state;
    
    Song *m_song;

    //Rhythm *m_input1, *m_input2; //store user input as Note data

    Calibration *m_calibration;
    
    int m_actionScoreP1, m_actionScoreP2; //store scores for the turn here to be used in EFFECT phase

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
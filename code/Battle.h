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


using namespace sf;
using namespace std;

//forward definitions prevent compile errors in Battle class
class StatusBar;
class CombatMenu;
class Effect;
class RhythmBar;

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
enum EffectType{MAGIC, DAMAGE};

//The game engine will have a battle object, accessing everything through there?

class Battle
{
public:
    Battle();
    void setChoices(vector<int> choices);

    Color getBackground(); //use in draw()    
    Sprite getCharacterSprite(PlayerID id); //better to get sprite pointers?
    Sprite getEffectSprite(PlayerID id, EffectType effect);
    Sprite getCombatMenuSprite();
    Sprite getHealthBar(PlayerID id);
    vector<RectangleShape*> getRhythmBar();

    int getScore(Track& input, int midiTime); //int score/100 of an input session
    void setScore(PlayerID id, int score);
    //void combatAction(CombatType type, PlayerID id);

    void handleInput();
    void update(float dtAsSeconds); //update all objects within
    void drawBattle(RenderWindow &window);
    
    BattleState getState();
    void setState(BattleState state); //maybe have an outside function that manages the battle loop

private:
    bool m_recordingInput;
    
    //Sprite background; //(these can cause hard lag... must be because full screen display?)
    
    //might be best to use pointers for all these class objects with lots of data
    Character *m_p1, *m_p2;

    //all these object pairs for each character, might be best to move to character class
    StatusBar *m_status1, *m_status2;
    CombatMenu *m_combatMenu; //menu specifically for battle options
    Effect *m_magic1, *m_magic2, *m_damage1, *m_damage2;

    RhythmBar *m_bar; //I hope to display a scrolling sequence of notes with simple lines over a box
    
    Text m_text; //use to announce actions

    PlayerID m_turn; //whose turn is active

    Display m_display;

    BattleState m_state;
    
    Song *m_song;

    Rhythm *m_input; //store user input as Note data
    
    int m_actionScoreP1, m_actionScoreP2; //store scores for the turn here to be used in EFFECT phase

};


//use int or doubles?
const int MAX_HEALTH = 100;
const int MAX_METER = 100;
class StatusBar
{
public:
    StatusBar();
    int getHealth();
    int getMeter();
    vector<RectangleShape*> getBars(); //get the shapes to display
    void addDamage(int damage);
    void addMeter(int meter);
    
private:
    int health;
    int meter;
    //display with SFML rectangles instead of sprite?
    //Sprite m_sprite;
    RectangleShape* m_healthBackground;
    RectangleShape* m_healthBar;
    RectangleShape* m_meterBackground;
    RectangleShape* m_meterBar;

};

//enum EffectType{MAGIC, DAMAGE};
class Effect
{
public:
    Effect(Vector2f position, EffectType type, PlayerID id);
    Sprite getSprite();

    void setPosition(Vector2f coord);
    void setScale(Vector2f xyScale);


private:
    Sprite m_sprite;
    Vector2f m_position;
    Color m_color; //color of effects will be based on health/accuracy stats

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
    int unitsToDisplay = 100; //range of note units to be displayed


};

#endif
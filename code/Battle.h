#ifndef BATTLE_H
#define BATTLE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Song.h"
#include "Character.h"

using namespace sf;
using namespace std;

//forward definitions prevent compile errors in Battle class
class Healthbar;
class CombatMenu;
class Effect;
class RhythmBar;

enum BattleState
{
    CALIBRATE, //sequence to sync audio with user input if necessary
    MENU, //awaiting user selection of combat options
    INPUT,
    EFFECT,
    ENDSCREEN
};

enum Display{LIGHT, DARK}; //black or white background/sprites

//The game engine will have a battle object, accessing everything through there?

class Battle
{
public:
    Battle(Display mode, CharacterType p1, CharacterType p2, string songFileName);
    void update(float dtAsSeconds); //update all objects within

    //void setDisplay(Display display); //light or dark mode

    //void setCharacter(PlayerID playerID, CharacterType type); 
    
    Sprite getCharacterSprite(PlayerID id); //get sprite instead?

    void handleInput();

private:
    Sprite background; //(these can cause hard lag... must be because full screen display?)
    
    //might be best to use pointers for all these class objects with lots of data
    Character *m_p1, *m_p2;

    //all these object pairs for each character, might be best to move to character class
    Healthbar *m_health1, *m_health2;
    CombatMenu *m_menu1, *m_menu2; //menu specifically for battle options
    Effect *m_magic1, *m_magic2, *m_damage1, *m_damage2;

    RhythmBar *m_bar; //I hope to display a scrolling sequence of notes with simple lines over a box
    
    Text m_text; //use to announce actions

    PlayerID m_turn; //whose turn is active

    Display m_display;
    
    Song *m_song;

};


//use int or doubles?
const int MAX_HEALTH = 100;
class Healthbar
{
public:
    Healthbar();
    int getHealth();
    Color getColor(); //color changes depending on health
    RectangleShape getBar();
    void addDamage(int damage);
    
private:
    int health;
    //display with SFML rectangles instead of sprite?
    Sprite m_sprite;
    RectangleShape m_bar;

};

enum EffectType{MAGIC, DAMAGE};
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
    void loadNotes(vector<Note*> *notes);
    void setRange(int units);
    vector<RectangleShape*> getRects();

private:
    vector<RectangleShape*> m_rects;
    int unitsToDisplay = 100; //range of note units to be displayed


};

class CombatMenu
{
public:
    CombatMenu(PlayerID id);
    //getsprite
    //set position, scale
private:
    //has flashing rectangle outline or tiny triangle as selector

};

#endif
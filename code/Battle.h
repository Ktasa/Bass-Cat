#ifndef BATTLE_H
#define BATTLE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Character.h"

using namespace sf;
using namespace std;

enum BattleState
{
    CALIBRATE, //sequence to sync audio with user input if necessary
    MENU, //awaiting user selection of combat options
    INPUT,
    EFFECT,
    VICTORY
};
enum Turn{PLAYER1, PLAYER2};

//The game engine will have a battle object, accessing everything through there?

class Battle
{
public:
    Battle();
    void update(float dtAsSeconds); //update all objects within
    
    Character* getCharacter(PlayerID id); //change "Side" to "PlayerID?"

private:
    Sprite background; //(these can cause hard lag... must be because full screen display?)
    
    //might be best to use pointers for all these class objects with lots of data
    Character *m_p1, *m_p2;

    //all these object pairs for each character, might be best to move to character class
    Healthbar *m_health1, *m_health2;
    Menu *m_menu1, *m_menu2; //menu specifically for battle options
    Effect *m_magic1, *m_magic2, *m_damage1, *m_damage2;

    RhythmBar m_bar; //I hope to display a scrolling sequence of notes with simple lines over a box
    
    Text m_text; //use to announce actions
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
    vector<RectangleShape*> getRects();

private:
    vector<RectangleShape*> m_rects;
    int unitsToDisplay = 100; //range of note units to be displayed


};

class Menu
{
public:
    Menu(PlayerID id);
    //getsprite
    //set position, scale
private:
    //has flashing rectangle outline or tiny triangle as selector

};

#endif
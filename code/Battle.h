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
    //scene background (these can cause hard lag... must be because full screen display?)
    Character *m_p1, *m_p2;

    //move to character
    Healthbar m_health;
    //Menu m_menu;
    Effect m_magic, m_damage;

    //Rhythm bar //I hope to display a scrolling sequence of notes with simple lines over a box
    
    Text m_text; //use to announce actions
};


//move to character class
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

//Move to character class
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

#endif
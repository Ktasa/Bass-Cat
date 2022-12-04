#ifndef COMBATMENU_H
#define COMBATMENU_H

#include "Battle.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

enum CombatType{NO_SELECTION, ATTACK, BLOCK, BUILD_METER, MAGIC_ATTACK,};

class CombatMenu
{
public:
    CombatMenu();
    void activate(); //make the menu appear
    void handleInput(); //get choices
    void update(); 
    Sprite* getSprite();
    void setColor(Color color); //change outline color
    bool getIsActive(); //menu is active
    bool getIsDone(); //choices are ready
    CombatType getChoice(PlayerID id);

private:
    Sprite* m_sprite;
    bool m_isActive;
    Color m_color;
    bool m_isDone; //need another bool to distinguish when to change battle states

    bool m_p1Pressed; //change color during input
    bool m_p2Pressed;
    PlayerID m_current; //which player is inputting

    //need to reset these values when done by setting to NO_SELECTION
    CombatType m_p1Choice; //store user input
    CombatType m_p2Choice;

    const int COMBAT_MENU_WIDTH = 700;
    //const int NUM_OPTIONS = 4;
};

#endif
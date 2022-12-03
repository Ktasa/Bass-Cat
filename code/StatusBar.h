#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Battle.h"
#include "Character.h"

using namespace sf;
using namespace std;

//use int or doubles?
const int MAX_HEALTH = 100;
const int MAX_METER = 100;
class StatusBar
{
public:
    StatusBar();
    void update(); //update the graphics each turn
    int getHealth();
    int getMeter();
    vector<RectangleShape*> getBars(); //get the shapes to display
    void addDamage(int damage);
    void addMeter(int meter);
    //void setColor(Display display);
    void setColor(Color color);
    void setPosition(PlayerID id);
    void setUp(PlayerID id, Color color);
    //RectangleShape* getHealthBG(); //test drawing
    
private:
    int health;
    int meter;
    //display with SFML rectangles instead of sprite?
    //Sprite m_sprite;
    vector<RectangleShape*> m_statusBars;
    RectangleShape *m_healthBG; //when adjusting the scale, do it proportional to height
    RectangleShape *m_healthBar;
    RectangleShape *m_meterBG;
    RectangleShape *m_meterBar;
    //Shape* shape;

};

#endif

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
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
    void addDamage(int damage); //maybe better to use setHealth/Meter
    void addMeter(int meter);
    void setHealth(int health); 
    void setMeter(int meter);
    //void setColor(Display display); //recursive include error because Display is in Battle
    void setColor(PlayerID id, Color color);
    void setPosition(PlayerID id);
    void setUp(PlayerID id, Color color);
    void activateUpdate();
    
private:
    int m_health;
    int m_meter;
    bool m_update;
    vector<RectangleShape*> m_statusBars;
    RectangleShape *m_healthBar;
    RectangleShape *m_meterBar;

};

#endif

#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Character
{
public:
    Character();
    //character(CHARACTER_TYPE);
    Sprite getSprite();
    void updateCharacter(float dtAsSeconds);

private:
    Texture m_spritesheetTexture;
    Sprite m_sprite;
    int currFrame;

};


#endif
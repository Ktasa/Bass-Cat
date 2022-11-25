#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

enum CharacterType{CAT, DOG};
enum Side{LEFT, RIGHT};

const int CHARACTER_SHEET_WIDTH = 1000;

class Character
{
public:
    Character(CharacterType type);
    //Sprite getSprite(); //unnecessary? (pass texture to draw by reference)
    void updateCharacter(float dtAsSeconds);

    //to be used by Battle.h to set scene
    void setPosition(Vector2f coord);
    void setFrameTime(float seconds);

private:
    Texture m_spritesheetTexture;
    VertexArray charVA; //holds coords for sprites in sheet
    //Sprite m_sprite; //unnecessary? (pass texture to draw by reference)
        
    CharacterType m_type; //cat or dog
    Side m_side; //left or right

    Vector2f position; //screen position

    int m_frameNum; //current frame
    float m_timePerFrame; //time per frame
    float m_timeUntilUpdate; 

    bool isPressed; //is player input live
};

#endif
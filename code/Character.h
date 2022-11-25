#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

enum CharacterType{CAT, DOG};
enum Side{LEFT, RIGHT};
enum LineColor{BLACK, WHITE};

const int CHARACTER_SHEET_WIDTH = 1000;

class Character
{
public:
    Character(CharacterType type, LineColor color, Side side);
    //Sprite getSprite(); //unnecessary? (pass texture to draw by reference)
    void updateCharacter(float dtAsSeconds);

    //to be used by Battle.h to set scene
    void setPosition(Vector2f coord);
    void setFrameTime(float seconds);

private:
    Texture m_charTexture;
    VertexArray charVA; //holds coords for sprites in sheet
    //Sprite m_sprite; //unnecessary? (pass texture to draw by reference)
        
    //CharacterType m_type; //cat or dog
    //LineColor m_lineColor;
    Side m_side; //left or right

    Vector2f position; //screen position

    int m_frameID; //current frame
    float m_timePerFrame; //time per frame
    float m_timeUntilUpdate; 

    bool isPressed; //is player input live
};

Character::Character(CharacterType type, LineColor color, Side side)
{
    //load texture file
    //CHANGE TO USE TEXTUREHOLDER
    string fileName = "/graphics/spritesheet ";
    if(type == CAT) {fileName += "cat ";}
    else {fileName += "dog ";}
    if(color == BLACK) {fileName += "B";}
    else {fileName += "W";}
    fileName += ".png";
    m_charTexture.loadFromFile(fileName);

    m_side = side;

}

#endif
#include "Character.h"

Character::Character(CharacterType type, LineColor color, Side side, float frameTime)
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

    m_side = side; //use later to flip sprite

    m_timePerFrame = frameTime;

    m_timeUntilUpdate = frameTime; //countdown time

    m_isPressed = false;

    m_frameID = 0;

    m_position = Vector2f(0,0); //position on screen
}
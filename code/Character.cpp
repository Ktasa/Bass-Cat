#include "Character.h"

Character::Character(){}

Character::Character(CharacterType type, Color color, Side side, int BPM)
{
    //Remove once battle class handles this with setPosition
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    //load texture file
    //CHANGE TO USE TEXTUREHOLDER
    string fileName;
    if(type == CAT) {fileName += "graphics/cat.png";}
    else {fileName += "graphics/dog.png";}
    m_charTexture.loadFromFile(fileName);

    //set sprite texture, position, origin, scale, color
    m_charSprite.setTexture(m_charTexture);
    //position is relative to resolution. 
    Vector2f player1Position = {resolution.x * float(0.1), resolution.y * float(0.8)};
    Vector2f player2Position = {resolution.x * float(0.6), resolution.y * float(0.8)};
    if(side==LEFT) {m_position = player1Position;}
    else {m_position = player2Position;}
    m_charSprite.setPosition(m_position);
    //origin is the center of a sprite to help with alignment
    m_charSprite.setOrigin(CHARACTER_SHEET_WIDTH/2,CHARACTER_SHEET_WIDTH/2);
    //set outline color
    m_charSprite.setColor(color); //set color works with white sprites

    IntRect rect(0, 0, CHARACTER_SHEET_WIDTH, CHARACTER_SHEET_WIDTH);
    m_charSprite.setTextureRect(rect);

    setFrameTime(BPM);

    m_isPressed = false;

    m_frameID = 0;
    m_frameNum = 1;

}

void Character::updateCharacter(float dtAsSeconds)
{
    m_timeUntilUpdate -= dtAsSeconds;
    
    if(m_timeUntilUpdate <= 0.0)
    {
        m_frameID++; //FIX: need to set frame base on more information
        m_frameID %= 4;
        m_timeUntilUpdate += m_timePerFrame;

        //set texture coords of sprite
        int frameOffset = CHARACTER_SHEET_WIDTH * m_frameID;
        IntRect rect(0 + frameOffset, 0, CHARACTER_SHEET_WIDTH, CHARACTER_SHEET_WIDTH);
        m_charSprite.setTextureRect(rect);
    }
}

Sprite Character::getSprite()
{
    return m_charSprite;
}
void Character::setPosition(Vector2f coord)
{
    m_position = coord;
    m_charSprite.setPosition(m_position); 
}
void Character::setScale(Vector2f xyScale)
{
    m_charSprite.setScale(xyScale);
}
void Character::setFrameTime(int BPM)
{
    int framesPerBeat = 4;
    m_timePerFrame = (60.0 / BPM) / framesPerBeat;
    m_timeUntilUpdate = m_timePerFrame; //countdown time
}
//use to resync animation
void Character::resetTime()
{
    m_timeUntilUpdate = 0.0;
}

void Character::setInput(bool isInput)
{
    m_isPressed = isInput;
}
#include "Character.h"

Character::Character(CharacterType type, LineColor color, Side side, int BPM)
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

    setFrameTime(BPM);

    m_charVA.setPrimitiveType(Quads);
    m_charVA.resize(4);

    m_isPressed = false;

    m_frameID = 0;
    m_frameNum = 1;

    m_position = Vector2f(0,0); //position on screen
}

void Character::updateCharacter(float dtAsSeconds)
{
    m_timeUntilUpdate -= dtAsSeconds;
    if(m_timeUntilUpdate <= 0.0)
    {
        //set text coords [location of current sprite]
        m_frameID++; //FIX: need to set frame base on more information
        int frameOffset = CHARACTER_SHEET_WIDTH * m_frameID;
        m_charVA[0].texCoords = Vector2f(0, 0 + frameOffset);
        m_charVA[1].texCoords = Vector2f(CHARACTER_SHEET_WIDTH, 0 + frameOffset);
        m_charVA[2].texCoords = Vector2f(CHARACTER_SHEET_WIDTH, CHARACTER_SHEET_WIDTH + frameOffset);
        m_charVA[3].texCoords = Vector2f(0, CHARACTER_SHEET_WIDTH + frameOffset);

        //reset timer, but keep a slight offset to make up for lost time
        m_timeUntilUpdate += m_timePerFrame;
        m_frameID %= 2;
    }
}

//set screen position
//make relative to View coord system?
void Character::setPosition(Vector2f coord)
{
    m_position = coord; //m_position unnecessary middle man?
    m_charVA[0].position = m_position + Vector2f(0, 0);
    m_charVA[1].position = m_position + Vector2f(CHARACTER_SHEET_WIDTH, 0);
    m_charVA[2].position = m_position + Vector2f(CHARACTER_SHEET_WIDTH, CHARACTER_SHEET_WIDTH);
    m_charVA[3].position = m_position + Vector2f(0, CHARACTER_SHEET_WIDTH);
}
void Character::setFrameTime(int BPM)
{
    int framesPerBeat = 4;
    m_timePerFrame = (BPM / 60.0) / framesPerBeat;
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
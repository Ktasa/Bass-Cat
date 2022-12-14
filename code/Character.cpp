#include "Character.h"
#include <iostream>

Character::Character(PlayerID playerID, CharacterType type, Color color, int BPM)
{
    //Remove once battle class handles this with setPosition
    Vector2f resolution;
    //resolution.x = VideoMode::getDesktopMode().width;
    //resolution.y = VideoMode::getDesktopMode().height;
    resolution.x = 1920;
    resolution.y = 1080;

    //load texture file
    //change to use TextureHolder (not working yet)
    string fileName;
    if(type == CAT) {fileName += "graphics/cat.png";}
    else {fileName += "graphics/panda.png";}
    m_charSprite = new Sprite(TextureHolder::GetTexture(fileName));
    
    //set sprite texture, position, origin, scale, color
    //position is relative to resolution. 
    //Vector2f player1Position = {resolution.x * float(0.1), resolution.y * float(0.8)};
    //Vector2f player2Position = {resolution.x * float(0.6), resolution.y * float(0.8)};

    Vector2f player1Position = {resolution.x * float(0.2), resolution.y * float(0.6)};
    Vector2f player2Position = {resolution.x * float(0.8), resolution.y * float(0.6)};
    
    //size of cat proportional to resolution
    float defaultSize = CHARACTER_SHEET_WIDTH / resolution.y;
    float goalSize = 0.50;
    float adjustScale = goalSize / defaultSize;
    //std::cout << "scale: " << catScaleXY << endl;
    Vector2f p1Scale = {adjustScale,adjustScale};
    Vector2f p2Scale = {-adjustScale,adjustScale}; //flip sprite
    
    //Temporary fix: I accidentally made the panda sprites backwards
    if(type == PANDA)
    {
        p1Scale = {-adjustScale,adjustScale};
        p2Scale = {adjustScale,adjustScale};
    }

    //set position and scale based on PlayerID
    if(playerID==P1) 
    {
        m_position = player1Position;
        m_charSprite->setScale(p1Scale);
    }
    else 
    {
        m_position = player2Position;
        m_charSprite->setScale(p2Scale);
    }
    m_charSprite->setPosition(m_position);
    //origin is the center of a sprite to help with alignment
    m_charSprite->setOrigin(CHARACTER_SHEET_WIDTH/2,CHARACTER_SHEET_WIDTH/2);
    //set outline color
    m_charSprite->setColor(color); //set color works with white sprites

    IntRect rect(0, 0, CHARACTER_SHEET_WIDTH, CHARACTER_SHEET_WIDTH);
    m_charSprite->setTextureRect(rect);

    setFrameTime(BPM);

    m_isPressed = false;

    m_state = IDLE;
    m_frameID = 0;
    m_frameNum = 0;
    m_stateChange = false;

    m_playerID = playerID;
    m_type = type;
}
void Character::handleInput()
{
    //different characters use different input keys
    Keyboard::Key key;
    if(m_playerID == P1)
    {key = Keyboard::Space;}
    else{key = Keyboard::Return;}

    bool checkChange = m_isPressed;

    if (Keyboard::isKeyPressed(key)) 
    {
        m_isPressed = true;
       
    }
    else {m_isPressed = false;}

    if(checkChange != m_isPressed)
    {m_stateChange = true;}
    //else
    //{m_stateChange = false;}
}

void Character::updateCharacter(float dtAsSeconds)
{
    m_timeUntilUpdate -= dtAsSeconds;

    if(m_state != VICTORY)
    {
        if(m_isPressed ==  true){m_state = ACTION;}
        else{m_state = IDLE;}
    }
    
    //if update time OR if switching animations (respond to user input)
    if(m_timeUntilUpdate <= 0.0 || m_stateChange)
    {
        m_frameNum++; //oscillate between a set of two frames, add 0 or 1 to frameID
        m_frameNum %= 2;

        if(m_state == IDLE)
        {
            m_frameID = m_frameNum; //frameID 0&1
        }
        else if(m_state == ACTION)
        {
            m_frameID = m_frameNum + 2; //frameID 2&3
        }
        else if(m_state == VICTORY)
        {
            if(m_type == PANDA){m_frameID = m_frameNum + 4;} //use either 4&5 or 1&2
            else
                m_frameID = m_frameNum + 4; //frameID 4&5
        }

        //set texture coords of sprite
        int frameOffset = CHARACTER_SHEET_WIDTH * m_frameID;
        IntRect rect(0 + frameOffset, 0, CHARACTER_SHEET_WIDTH, CHARACTER_SHEET_WIDTH);
        m_charSprite->setTextureRect(rect);

        //should the animation sync reset at user input?
        //if(!m_stateChange)
        //{m_timeUntilUpdate += m_timePerFrame;}
        m_timeUntilUpdate = m_timePerFrame;
        m_stateChange = false;
    }
}
Sprite* Character::getSprite()
{
    return m_charSprite;
}
void Character::setState(AnimationState state)
{
    m_state = state;
}
void Character::setPosition(Vector2f coord)
{
    m_position = coord;
    m_charSprite->setPosition(m_position); 
}
void Character::setScale(Vector2f xyScale)
{
    m_charSprite->setScale(xyScale);
}
void Character::setFrameTime(int BPM)
{
    int framesPerBeat = 4;
    m_timePerFrame = (60.0 / BPM) / framesPerBeat;
    //set double speed if slower tempo
    if(BPM <= 100)
        m_timePerFrame /= 2;
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
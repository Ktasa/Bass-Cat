#include "Effect.h"
#include "HSV.h"
Effect::Effect()
{
    float m_frameTime = 0.2;
    m_timeUntilUpdate = m_frameTime;
    m_color = Color::White;
    //temp
    m_rainbow = false;
    m_active = false;
}

void Effect::setUp(PlayerID id, EffectType type, int BPM)
{
    Vector2f resolution;
    resolution.x = 1920;
    resolution.y = 1080;

    //load texture file
    //change to use TextureHolder (not working yet)
    string fileName;
    if(type == MAGIC) {fileName += "graphics/magic.png";}
    else {fileName += "graphics/placeholder.png";}
    m_sprite = new Sprite(TextureHolder::GetTexture(fileName));
    
    //set sprite texture, position, origin, scale, color
    //position is relative to resolution. 
    Vector2f player1Position = {resolution.x * float(0.2), resolution.y * float(0.6)};
    Vector2f player2Position = {resolution.x * float(0.8), resolution.y * float(0.6)};
    Color blue = Color(0,100,255);
    Color red = Color(255,0,100);
    if(id == P1)
    {
        m_sprite->setPosition(player1Position);
        m_sprite->setColor(blue);
    }
    else
    {
        m_sprite->setPosition(player2Position);
        m_sprite->setColor(red);
    }

    const int MAGIC_SHEET_WIDTH = 600;
    float magicScale = resolution.y / 700;
    float magicFlip = magicScale * 1.0;
    m_sprite->setScale(Vector2f{magicFlip,magicScale});
    m_sprite->setOrigin(MAGIC_SHEET_WIDTH/2,MAGIC_SHEET_WIDTH*float(0.6));

    setFrameTime(BPM);
    m_playerNum = id;
}

Sprite* Effect::getSprite()
{
    return m_sprite;
}
void Effect::update(float dtAsSeconds)
{
    if(m_active)
    {
        //track update time
        m_timeUntilUpdate -= dtAsSeconds;
        if(m_timeUntilUpdate <= 0.0)
        {
            //flip sprite animation
            Vector2f magicScale = m_sprite->getScale();
            magicScale.x *= -1;
            m_sprite->setScale(magicScale);
            m_timeUntilUpdate = m_frameTime;
            if(m_rainbow)
            {
                Color color = m_sprite->getColor();
                int hueDt = 2.5;
                tuple<float,float,float> HSV = RGBtoHSV(color);
                float hue = get<0>(HSV);
                hue += hueDt;
                if(hue>360.0){hue=0.0;}
                color = HSVtoRGB(hue,1,1);
                m_sprite->setColor(color);
            }
            else
            {
                Color blue = Color(0,100,255);
                Color red = Color(255,0,100);
                if(m_playerNum == P1)
                    m_sprite->setColor(blue);
                if(m_playerNum == P2)
                    m_sprite->setColor(red);
            }
        }
        /*
        if(m_rainbow)
        {
            Color color = m_sprite.getColor();
            int hueDt = 1;
            tuple<float,float,float> HSV = RGBtoHSV(color);
            float hue = get<0>(HSV);
            hue += hueDt;
            if(hue>360.0){hue=0.0;}
            color = HSVtoRGB(hue,1,1);
            m_sprite.setColor(color);
        }
        */

    }
    //add if Magic attack state, use color shifting
    
}

void Effect::setFrameTime(int BPM)
{
    int framesPerBeat = 4;
    m_frameTime = (60.0 / BPM) / framesPerBeat;
    //set double speed if slower tempo
    //if(BPM <= 100)
    //    m_frameTime /= 2;
    m_timeUntilUpdate = m_frameTime; //countdown time
}

void Effect::setActive(bool active)
{
    m_active = active;
}
bool Effect::getIsActive()
{
    return m_active;
}
void Effect::setRainbow(bool active)
{
    m_rainbow = active;
}
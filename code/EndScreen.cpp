#include "EndScreen.h"

EndScreen::EndScreen()
{
    m_active = false;
    string fileName = "graphics/end splash.png";
    m_sprite = new Sprite(TextureHolder::GetTexture(fileName));
    fileName = "graphics/victory.png";
    m_victory = new Sprite(TextureHolder::GetTexture(fileName));

    m_victorySFXBuffer.loadFromFile("sound/bass sfx.ogg");
	m_victorySFX.setBuffer(m_victorySFXBuffer);
    
    Vector2f resolution;
    resolution.x = 1920;
    resolution.y = 1080;

    //Vector2f position = {resolution.x * float(0.15), resolution.y * float(1.2)};
    Vector2f position = {resolution.x * float(0.5), resolution.y * float(0.5)};
    m_sprite->setPosition(position);

    m_sprite->setOrigin(SCREEN_WIDTH/2.0, SCREEN_HEIGHT /2.0);

    //set victory text sprite
    position = {resolution.x * float(0.5), resolution.y * float(0.5)};
    m_victory->setPosition(position);
    m_victory->setOrigin(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

}
void EndScreen::activate(PlayerID victor)
{
    if(!m_active)
    {
        if(victor == P1)
        {
            m_sprite->setColor(Color(100,0,255));
            m_sprite->setScale(1,1);
            //m_sprite->setColor(Color(100,0,255,150));
        }
        else if(victor == P2)
        {
            m_sprite->setScale(-1,1);
            m_sprite->setColor(Color(255,0,100));
        }
        m_victorySFX.play();
    }
    m_active = true;
}

Sprite* EndScreen::getSprite()
{
    return m_sprite;
}

Sprite* EndScreen::getVictorySprite()
{
    return m_victory;
}
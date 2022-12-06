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
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    Vector2f position = {resolution.x * float(0.15), resolution.y * float(1.2)};
    m_sprite->setPosition(position);

    //adjust scale to screen resolution
    float defaultSize = SCREEN_WIDTH / resolution.x;
    float goalSize = 1.5; 
    float adjustScale = goalSize / defaultSize;
    Vector2f scale = {adjustScale,adjustScale};

    m_sprite->setScale(scale);
    m_sprite->setOrigin(SCREEN_WIDTH / 2, SCREEN_WIDTH / 2);

    //set victory text sprite
    position = {resolution.x * float(0.16), resolution.y * float(1.1)};
    m_victory->setPosition(position);

    //adjust scale to screen resolution
    defaultSize = SCREEN_WIDTH / resolution.x;
    goalSize = 1.4; 
    adjustScale = goalSize / defaultSize;
    scale = {adjustScale,adjustScale};

    m_victory->setScale(scale);
    m_victory->setOrigin(SCREEN_WIDTH / 2, SCREEN_WIDTH / 2);

}
void EndScreen::activate(PlayerID victor)
{
    if(!m_active)
    {
        if(victor == P1)
        {
            m_sprite->setColor(Color(100,0,255));
        }
        else if(victor == P2)
        {
            Vector2f resolution;
            resolution.x = VideoMode::getDesktopMode().width;
            resolution.y = VideoMode::getDesktopMode().height;
            
            Vector2f position = {resolution.x * float(0.25), resolution.y * float(1.2)};
            m_sprite->setPosition(position);

            //adjust scale to screen resolution
            float defaultSize = SCREEN_WIDTH / resolution.x;
            float goalSize = 1.4; 
            float adjustScale = goalSize / defaultSize;
            Vector2f scale = {-adjustScale,adjustScale};
            m_sprite->setScale(scale);
            m_sprite->setColor(Color(255,0,100));

            position = {resolution.x * float(0.16), resolution.y * float(1.1)};
            m_victory->setPosition(position);
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
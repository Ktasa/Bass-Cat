#include "EndScreen.h"

EndScreen::EndScreen()
{
    m_active = false;
    string fileName = "graphics/end splash.png";
    m_sprite = new Sprite(TextureHolder::GetTexture(fileName));
    
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
        }
    }
    m_active = true;
}

Sprite* EndScreen::getSprite()
{
    return m_sprite;
}
#include "Calibration.h"

Calibration::Calibration()
{
    m_active = false;
    
    string fileName = "graphics/Calibration.png";
    *m_sprite = Sprite(TextureHolder::GetTexture(fileName));
    
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    Vector2f position = {resolution.x * float(0.35), resolution.y * float(0.8)};
    m_sprite->setPosition(position);

    //adjust scale to screen resolution
    float defaultSize = CALIBRATION_WIDTH / resolution.y;
    float goalSize = 0.80; 
    float adjustScale = goalSize / defaultSize;
    Vector2f menuScale = {adjustScale,adjustScale};
    m_sprite->setScale(menuScale);

    //center of screen
    m_sprite->setOrigin(CALIBRATION_WIDTH / 2, CALIBRATION_WIDTH / 2);
}
void Calibration::activate(Display display)
{
    m_active = true;
    if(display == DARK)
    {
        m_sprite->setColor(Color::White);
    }
    else
    {
        m_sprite->setColor(Color::Black);
    }
}
void Calibration::handleInput()
{
    if(m_active)
    {
        if(Keyboard::isKeyPressed(Keyboard::Space))
        {
            m_done = true;
            m_active = false;
        }
    } 
}
Sprite* Calibration::getSprite()
{
    return m_sprite;
}
bool Calibration::getIsActive()
{
    return m_active;
}
bool Calibration::getIsDone()
{
    return m_done;
}
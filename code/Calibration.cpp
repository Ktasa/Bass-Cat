#include "Calibration.h"

Calibration::Calibration()
{
    m_active = false;
    m_done = false;

    m_sprite = new Sprite();
    
    string fileName = "graphics/Calibration.png";
    *m_sprite = Sprite(TextureHolder::GetTexture(fileName));
    
    Vector2f resolution;
    resolution.x = 1920;
    resolution.y = 1080;

    //Vector2f position = {resolution.x * float(0.35), resolution.y * float(0.8)};
    Vector2f position = {resolution.x * float(0.5), resolution.y * float(0.55)};
    m_sprite->setPosition(position);

    //adjust scale to screen resolution
    float defaultSize = CALIBRATION_WIDTH / resolution.y;
    float goalSize = 0.80; 
    float adjustScale = goalSize / defaultSize;
    Vector2f menuScale = {adjustScale,adjustScale};
    m_sprite->setScale(menuScale);
    m_sprite->setOrigin(CALIBRATION_WIDTH / 2, CALIBRATION_WIDTH / 2);
}
void Calibration::activate()
{
    m_active = true;
    m_done = false;
}
void Calibration::handleInput()
{
    //Add Escape to reset option. Shouldve used a different key because escape closes the window
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
void Calibration::setColor(Color color)
{
    m_sprite->setColor(color);
}
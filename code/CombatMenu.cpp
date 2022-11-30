#include "Battle.h"

CombatMenu::CombatMenu()
{
    m_isActive = false;
    m_p1Choice = NO_SELECTION;
    m_p2Choice = NO_SELECTION;

    string fileName = "graphics/combat menu.png";
    m_color = Color::Blue;
    m_sprite = Sprite(TextureHolder::GetTexture(fileName));
    m_sprite.setColor(m_color);

    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    //Set position
    //Positions of other things - p1: 0.1x, 0.8y; p2: 0.6x, 0.8y
    Vector2f menuPosition = {resolution.x * float(0.3), resolution.y * float(0.8)};
    m_sprite.setPosition(menuPosition);

    //adjust scale to screen resolution
    float defaultSize = COMBAT_MENU_WIDTH / resolution.y;
    float goalSize = 0.50; //half the height of screen
    float adjustScale = goalSize / defaultSize;
    Vector2f menuScale = {adjustScale,adjustScale};
    m_sprite.setScale(menuScale);

    //center of screen
    m_sprite.setOrigin(COMBAT_MENU_WIDTH / 2, COMBAT_MENU_WIDTH / 2);

}

void CombatMenu::activate()
{
    m_isActive = true;
}

void CombatMenu::handleInput()
{
    if(m_isActive)
    {
        if(m_p1Choice != NO_SELECTION)
        {
            if (Keyboard::isKeyPressed(Keyboard::Num1)) 
                m_p1Choice = ATTACK;
            else if (Keyboard::isKeyPressed(Keyboard::Num2)) 
                m_p1Choice = BLOCK;
            else if (Keyboard::isKeyPressed(Keyboard::Num3)) 
                m_p1Choice = BUILD_METER;
            else if (Keyboard::isKeyPressed(Keyboard::Num1)) 
                m_p1Choice = MAGIC_ATTACK;
        }
        if(m_p2Choice != NO_SELECTION)
        {
            if (Keyboard::isKeyPressed(Keyboard::H)) 
                m_p1Choice = ATTACK;
            else if (Keyboard::isKeyPressed(Keyboard::J)) 
                m_p1Choice = BLOCK;
            else if (Keyboard::isKeyPressed(Keyboard::K)) 
                m_p1Choice = BUILD_METER;
            else if (Keyboard::isKeyPressed(Keyboard::L)) 
                m_p1Choice = MAGIC_ATTACK;
        }
        if(m_p1Choice != NO_SELECTION && m_p2Choice != NO_SELECTION)
        {m_isActive = false;}
    }


}
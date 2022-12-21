#include "CombatMenu.h"

CombatMenu::CombatMenu()
{
    m_isActive = false;
    m_isDone = false;
    m_p1Choice = NO_SELECTION;
    m_p2Choice = NO_SELECTION;
    m_current = P1;

    string fileName = "graphics/combat menu.png";
    m_color = Color::Green; //a green menu means the program is failing to change its color
    m_sprite = new Sprite(TextureHolder::GetTexture(fileName));
    m_sprite->setColor(m_color);

    Vector2f resolution;
    resolution.x = 1920;
    resolution.y = 1080;

    //Set position
    //Vector2f menuPosition = {resolution.x * float(0.35), resolution.y * float(0.8)};
    Vector2f menuPosition = {resolution.x * float(0.5), resolution.y * float(0.55)};
    
    m_sprite->setPosition(menuPosition);

    //adjust scale to screen resolution
    float defaultSize = COMBAT_MENU_WIDTH / resolution.y;
    float goalSize = 0.80; //about half the height of screen
    float adjustScale = goalSize / defaultSize;
    Vector2f menuScale = {adjustScale,adjustScale};
    m_sprite->setScale(menuScale);

    //center of screen
    m_sprite->setOrigin(COMBAT_MENU_WIDTH / 2, COMBAT_MENU_WIDTH / 2);
}

void CombatMenu::activate()
{
    if(m_isActive == false)
    {
        m_isActive = true;
        m_isDone = false;
        m_p1Choice = NO_SELECTION;
        m_p2Choice = NO_SELECTION;
        //cout << "activated" << endl;
    }
}
bool CombatMenu::getIsActive()
{
    return m_isActive;
}
bool CombatMenu::getIsDone()
{
    return m_isDone;
}
void CombatMenu::reset()
{
    m_isActive = false;
    m_isDone = false;
    //setColor(Color::White);
}
void CombatMenu::handleInput()
{
    //cout <<"in combatMenu handleInput" << endl;
    if(m_isActive)
    {
        if(m_p1Choice == NO_SELECTION)
        {
            //cout << "Inside p1 choice" << endl;
            if (Keyboard::isKeyPressed(Keyboard::Num1)) 
                m_p1Choice = ATTACK;
            else if (Keyboard::isKeyPressed(Keyboard::Num2)) 
                m_p1Choice = BLOCK;
            else if (Keyboard::isKeyPressed(Keyboard::Num3)) 
                m_p1Choice = BUILD_METER;
            else if (Keyboard::isKeyPressed(Keyboard::Num4)) 
                m_p1Choice = MAGIC_ATTACK;
            
            if(m_p1Choice != NO_SELECTION)
            {
                m_p1Pressed = true;
                m_current = P1;
            }
        }
        if(m_p2Choice == NO_SELECTION)
        {
            //cout << "inside p2 choice" << endl;
            if (Keyboard::isKeyPressed(Keyboard::H)) 
                m_p2Choice = ATTACK;
            else if (Keyboard::isKeyPressed(Keyboard::J)) 
                m_p2Choice = BLOCK;
            else if (Keyboard::isKeyPressed(Keyboard::K)) 
                m_p2Choice = BUILD_METER;
            else if (Keyboard::isKeyPressed(Keyboard::L)) 
                m_p2Choice = MAGIC_ATTACK;

            if(m_p2Choice != NO_SELECTION)
            {
                m_p2Pressed = true;
                m_current = P2;
            }
        }
        if(m_p1Choice != NO_SELECTION && m_p2Choice != NO_SELECTION)
        {
            m_isActive = false;
            m_isDone = true;
            //cout << "deactivated" << endl;
        }
    }
}

void CombatMenu::update()
{
    if(m_isActive)
    {
        //change color of menu depending on who pressed it
        //planning to change it so that the menu color stays constant
        /*
        if(m_p1Pressed && m_current == P1)
        {m_color = Color(100,0,255);}
        if(m_p2Pressed && m_current == P2)
        {m_color = Color(255,0,100);}
        m_sprite->setColor(m_color);
        */
    }
}

Sprite* CombatMenu::getSprite()
{
    return m_sprite;
}
void CombatMenu::setColor(Color color)
{
    m_color = color;
    m_sprite->setColor(color);
}

CombatType CombatMenu::getChoice(PlayerID id)
{
    CombatType choice;
    if(id == P1)
        choice = m_p1Choice;
    if(id == P2)
        choice = m_p2Choice;
    return choice;
    
}



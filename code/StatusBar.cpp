#include "StatusBar.h"

//set position in the same place you set postion the characters
StatusBar::StatusBar()
{
    health = MAX_HEALTH;
    meter = 0;
    m_healthBG = new RectangleShape();
    //m_healthBar = new RectangleShape();
    m_statusBars.push_back(m_healthBG);
    //m_statusBars.push_back(m_healthBar);
}
int StatusBar::getHealth()
{
    return health;
}
int StatusBar::getMeter()
{
    return meter;
}
vector<RectangleShape*> StatusBar::getBars()
{
    return m_statusBars;
}
//RectangleShape* StatusBar::getHealthBG()
//{
//    return m_healthBG;
//}
void StatusBar::setColor(Display display)
{
    if(display == DARK)
    {
        m_healthBG->setFillColor(Color::Black);
        m_healthBG->setOutlineColor(Color::White);
    }
    else
    {
        m_healthBG->setFillColor(Color::White);
        m_healthBG->setOutlineColor(Color::Black);
    }
}
void StatusBar::setPosition(PlayerID id)
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    Vector2f positionP1 = {resolution.x * float(0.1), resolution.y * float(0.8)};
    Vector2f positionP2 = {resolution.x * float(0.6), resolution.y * float(0.8)};
    Vector2f healthPosition;
    if(id == P1){healthPosition = positionP1;}
    else{healthPosition = positionP2;}
    m_healthBG->setPosition(healthPosition);

    //this only controls the proportions of the object while scale overrides its size
    Vector2f healthSize = {resolution.x * float(0.4), resolution.y * float(0.1)};
    m_healthBG->setSize(healthSize);
    FloatRect healthRect = m_healthBG->getGlobalBounds();
    //center origin
    m_healthBG->setOrigin(healthRect.width / 2, healthRect.height / 2);

    //adjust scale to screen resolution
    float defaultSize = healthRect.width / resolution.x;
    float goalSize = 0.15; 
    float adjustScale = goalSize / defaultSize;
    Vector2f scaleP1 = {adjustScale,adjustScale};
    Vector2f scaleP2 = {-adjustScale,adjustScale};
    Vector2f healthScale;
    if(id == P1){healthScale = scaleP1;}
    else{healthScale = scaleP2;}
    m_healthBG->setScale(healthScale);

}
void StatusBar::setUp(PlayerID id, Display display)
{
    setColor(display);
    setPosition(id);
}
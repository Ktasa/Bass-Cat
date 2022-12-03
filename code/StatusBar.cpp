#include "StatusBar.h"

//set position in the same place you set postion the characters
StatusBar::StatusBar()
{
    health = MAX_HEALTH;
    meter = 0;
    m_healthBar = new RectangleShape();
    m_meterBar = new RectangleShape();
    m_statusBars.push_back(m_healthBar);
    m_statusBars.push_back(m_meterBar);
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

void StatusBar::setColor(PlayerID id, Color color)
{
    if(color == Color::Black)
    {
        m_healthBar->setFillColor(Color::Black);
        m_healthBar->setOutlineColor(Color::White);
        m_meterBar->setFillColor(Color::Black);
        m_meterBar->setOutlineColor(Color::White);
    }
    else
    {
        m_healthBar->setFillColor(Color::White);
        m_healthBar->setOutlineColor(Color::Black);
        m_meterBar->setFillColor(Color::White);
        m_meterBar->setOutlineColor(Color::Black);
    }
    m_healthBar->setOutlineThickness(3);
    m_meterBar->setOutlineThickness(3);

    Color blue = Color(0,100,255);
    Color red = Color(255,0,100);
    if(id==P1){m_meterBar->setFillColor(blue);}
    else{m_meterBar->setFillColor(red);}
}

void StatusBar::setPosition(PlayerID id)
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    Vector2f healthPositionP1 = {resolution.x * float(0.1), resolution.y * float(1.05)};
    Vector2f healthPositionP2 = {resolution.x * float(0.595), resolution.y * float(1.05)};
    Vector2f meterPositionP1 = {resolution.x * float(0.1), resolution.y * float(1.08)};
    Vector2f meterPositionP2 = {resolution.x * float(0.595), resolution.y * float(1.08)};
    Vector2f healthPosition;
    Vector2f meterPosition;
    if(id == P1)
    {
        healthPosition = healthPositionP1;
        meterPosition = meterPositionP1;
    }
    else
    {
        healthPosition = healthPositionP2;
        meterPosition = meterPositionP2;
    }
    m_healthBar->setPosition(healthPosition);
    m_meterBar->setPosition(meterPosition);

    Vector2f barSize = {resolution.x * float(0.4), resolution.y * float(0.02)};
    m_healthBar->setSize(barSize);
    m_meterBar->setSize(barSize);
    FloatRect healthRect = m_healthBar->getGlobalBounds();
    //center origin
    m_healthBar->setOrigin(healthRect.width / 2, healthRect.height / 2);
    m_meterBar->setOrigin(healthRect.width / 2, healthRect.height / 2);

    //adjust scale to screen resolution
    float defaultSize = healthRect.width / resolution.x;
    float goalSize = 0.24; 
    float adjustScale = goalSize / defaultSize;
    Vector2f scaleP1 = {adjustScale,adjustScale};
    Vector2f scaleP2 = {-adjustScale,adjustScale};
    Vector2f barScale;
    if(id == P1){barScale = scaleP1;}
    else{barScale = scaleP2;}
    m_healthBar->setScale(barScale);
    m_meterBar->setScale(barScale);

}
void StatusBar::setUp(PlayerID id, Color color)
{
    setColor(id, color);
    setPosition(id);
}

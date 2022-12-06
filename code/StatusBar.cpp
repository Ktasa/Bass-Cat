#include "StatusBar.h"
//
//set position in the same place you set postion the characters
StatusBar::StatusBar()
{
    m_health = MAX_HEALTH;
    m_meter = 50;
    m_healthBar = new RectangleShape();
    m_meterBar = new RectangleShape();
    m_statusBars.push_back(m_healthBar);
    m_statusBars.push_back(m_meterBar);
    m_update = true;
}
void StatusBar::setUp(PlayerID id, Color color)
{
    setColor(id, color);
    setPosition(id);
}
void StatusBar::activateUpdate()
{
    m_update = true;
}
void StatusBar::update()
{
    if(m_update)
    {
        //enforce ceiling to max health / meter values
        if(m_health < 0)
            m_health = 0;
        if(m_health > MAX_HEALTH)
            m_health = MAX_HEALTH;
        if(m_meter < 0)
            m_meter = 0;
        if(m_meter > MAX_METER)
            m_meter = MAX_METER;

        Vector2f resolution;
        resolution.x = VideoMode::getDesktopMode().width;
        resolution.y = VideoMode::getDesktopMode().height;

        float healthPerc = float(m_health) / MAX_HEALTH;
        float meterPerc = float(m_meter) / MAX_METER;
        if(healthPerc < 0)
            healthPerc = 0;
        if(meterPerc < 0)
            meterPerc = 0;
        //cout << "healthPerc: " << healthPerc << endl;
        //cout << "meterPerc: " << meterPerc << endl;
        Vector2f sizeRatio = {0.4,0.02};
        //float healthMagicRatio = 0.5; //maybe make magic meter half the width of health?
        float healthWidth = resolution.x * healthPerc * sizeRatio.x;
        float meterWidth = resolution.x * meterPerc * sizeRatio.x;
        //cout << "healthWidth: " << healthWidth << endl;
        //cout << "meterWidth: " << meterWidth << endl;
        Vector2f healthSize = {healthWidth, resolution.y * sizeRatio.y};
        Vector2f meterSize = {meterWidth, resolution.y * sizeRatio.y};
        m_healthBar->setSize(healthSize);
        m_meterBar->setSize(meterSize);
        m_update = false;
    }
}

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

    Color blue = Color(0,100,255,150);
    Color red = Color(255,0,100,150);
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
    float defaultSize = healthRect.height / resolution.y;
    float goalSize = 0.016; 
    float adjustScale = goalSize / defaultSize;
    Vector2f scaleP1 = {adjustScale,adjustScale};
    Vector2f scaleP2 = {-adjustScale,adjustScale};
    Vector2f barScale;
    if(id == P1){barScale = scaleP1;}
    else{barScale = scaleP2;}
    m_healthBar->setScale(barScale);
    m_meterBar->setScale(barScale);

}

int StatusBar::getHealth()
{
    return m_health;
}
int StatusBar::getMeter()
{
    return m_meter;
}
void StatusBar::addDamage(int damage)
{
    m_health -= damage;
}
void StatusBar::addMeter(int meter)
{
    m_meter += meter;
}
void StatusBar::setHealth(int health)
{
    m_health = health;
}
void StatusBar::setMeter(int meter)
{
    m_meter = meter;
}
vector<RectangleShape*> StatusBar::getBars()
{
    return m_statusBars;
}
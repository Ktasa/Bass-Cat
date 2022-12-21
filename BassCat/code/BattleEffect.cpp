#include "Battle.h"

void Battle::setEffectActivity(PlayerID id, EffectType effect, bool active, bool rainbow)
{
    if(id==P1)
    {
        if(effect==MAGIC)
        {
            m_magic1->setActive(active);
            m_magic1->setRainbow(rainbow);
        }
        else
            m_damage1->setActive(active);
    }
    else
    {
        if(effect==MAGIC)
        {
            m_magic2->setActive(active);
            m_magic2->setRainbow(rainbow);
        }
        else
            m_damage2->setActive(active);
    }
}
bool Battle::getIsEffectActive(PlayerID id, EffectType effect)
{
    if(id==P1)
    {
        if(effect==MAGIC)
            return m_magic1->getIsActive();
        else
            return m_damage1->getIsActive();
    }
    else
    {
        if(effect==MAGIC)
            return m_magic2->getIsActive();
        else
           return m_damage2->getIsActive();
    }
}
void Battle::setEffects()
{
    bool active1, rainbow1;
    bool active2, rainbow2;
    if(m_combat1 == BUILD_METER)
    {
        active1 = true;
        rainbow1 = false;
    }
    else if(m_combat1 == MAGIC_ATTACK)
    {
        active1 = true;
        rainbow1 = true;
    }
    else
    {
        active1 = false;
        rainbow1 = false;
    }
    if(m_combat2 == BUILD_METER)
    {
        active2 = true;
        rainbow2 = false;
    }
    else if(m_combat2 == MAGIC_ATTACK)
    {
        active2 = true;
        rainbow2 = true;
    }
    else
    {
        active2 = false;
        rainbow2 = false;
    }
    //cout << boolalpha << "active1: " << rainbow1 << endl;
    //cout << "active2: " << active2 << endl;
    //cout << boolalpha << "rainbow1: " << rainbow1 << endl;
    //cout << "rainbow2: " << active2 << endl;
    setEffectActivity(P1, MAGIC, active1, rainbow1);
    setEffectActivity(P2, MAGIC, active2, rainbow2);
}
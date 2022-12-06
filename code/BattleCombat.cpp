#include "Battle.h"

void Battle::combatAction()
{
    cout << "Entered CombatAction" << endl;

    cout << "P1 score: " << m_scoreP1 << endl;
    cout << "P2 score: " << m_scoreP2 << endl;
    cout << "P1 health: " << m_status1->getHealth() << endl;
    cout << "P2 health: " << m_status2->getHealth() << endl;
    cout << "P1 meter: " << m_status1->getMeter() << endl;
    cout << "P2 meter: " << m_status2->getMeter() << endl;

    //const double DEFAULT_MULTIPLIER = 0.5;
    //const double MAGIC_ATTACK_MULTIPLIER = DEFAULT_MULTIPLIER * 1.5;
    const double DEFAULT_MULTIPLIER = 1;
    const double MAGIC_ATTACK_MULTIPLIER = DEFAULT_MULTIPLIER * 2;
    int effectP1 = 0;
    int effectP2 = 0;
    if(m_combat1 == ATTACK || m_combat1 == BLOCK || m_combat1 == BUILD_METER)
    {
        effectP1 = m_scoreP1 * DEFAULT_MULTIPLIER;
    }
    else if(m_combat1 == MAGIC_ATTACK)
    {
        effectP1 = m_scoreP1 * MAGIC_ATTACK_MULTIPLIER;
    }
    if(m_combat2 == ATTACK || m_combat2 == BLOCK || m_combat2 == BUILD_METER)
    {
        effectP2 = m_scoreP2 * DEFAULT_MULTIPLIER;
    }
    else if(m_combat1 == MAGIC_ATTACK)
    {
        effectP2 = m_scoreP2 * MAGIC_ATTACK_MULTIPLIER;
    }

    cout << "P1 effect: " << effectP1 << endl;
    cout << "P2 effect: " << effectP2 << endl;

    if(m_combat1 == ATTACK || m_combat1 == MAGIC_ATTACK)
    {
        if(m_combat2 == BLOCK)
        {
            effectP1 -= effectP2;
            if(effectP1 < 0)
                effectP1 = 0;
        }
    }
    else if(m_combat2 == ATTACK || m_combat2 == MAGIC_ATTACK)
    {
        if(m_combat1 == BLOCK)
        {
            effectP2 -= effectP1;
            if(effectP2 < 0)
                effectP2 = 0;
        }
    }

    cout << "P1 effect: " << effectP1 << endl;
    cout << "P2 effect: " << effectP2 << endl;

    if(m_combat1 == BUILD_METER)
    {
        m_status1->addMeter(effectP1);
    }
    else
    {
        m_status2->addDamage(effectP1);
    }
    if(m_combat2 == BUILD_METER)
    {
        m_status2->addMeter(effectP2);
    }
    else
    {
        m_status1->addDamage(effectP2);
    }

    if(m_combat1 == MAGIC_ATTACK)
    {
        int meterDrain = m_status1->getMeter() - effectP1;
        if(meterDrain < 0)
        {
            //reset meter
            m_status1->setMeter(0);
            m_status1->addDamage(meterDrain*-1);
        }
        else
            m_status1->addMeter(-effectP1);
    }
    if(m_combat2 == MAGIC_ATTACK)
    {
        int meterDrain = m_status2->getMeter() - effectP2;
        if(meterDrain < 0)
        {
            //reset meter
            m_status2->setMeter(0);
            m_status2->addDamage(meterDrain*-1);
        }
        else
            m_status2->addMeter(-effectP1);
    }

    if(m_combat1 == NO_SELECTION || m_combat2 == NO_SELECTION)
    {
        cout << "Error: NO_SELECTION combat action" << endl;
    }

    cout << "P1 effect: " << effectP1 << endl;
    cout << "P2 effect: " << effectP2 << endl;

    cout << "P1 health: " << m_status1->getHealth() << endl;
    cout << "P2 health: " << m_status2->getHealth() << endl;
    cout << "P1 meter: " << m_status1->getMeter() << endl;
    cout << "P2 meter: " << m_status2->getMeter() << endl;
}

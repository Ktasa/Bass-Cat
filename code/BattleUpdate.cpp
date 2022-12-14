#include "Battle.h"

void Battle::update(float dt)
{
    m_p1->updateCharacter(dt);
    m_p2->updateCharacter(dt);
    m_combatMenu->update();

    //move to the appropriate phase later
    m_status1->update();
    m_status2->update();

    m_magic1->update(dt);
    m_magic2->update(dt);

    updateTime();

    //check end battle
    if(m_status1->getHealth() <= 0 || m_status2->getHealth() <= 0)
        m_state = ENDSCREEN;

    if(m_state == ENDSCREEN)
        updateEndScreen();
    else if(m_state == CALIBRATE)
        updateCalibrate();
    else if(m_state == MENU)
        updateMenu();
    else if(m_state == INPUT) 
        updateInput();
    else if(m_state == EFFECT) 
        updateEffect();
}

void Battle::updateTime()
{
    int battleTicks = getCurrentTicks();
    //update time in sync once calibrated
    if(getIsCalibrated())
    {
        //calculate current time in ticks, update rhythm
        m_activeTime = true;
        m_input1->update(battleTicks);
        m_input2->update(battleTicks);
        //cout << "battle ticks " << battleTicks << endl;
    }
    //recalibrate upon song loop
    if(battleTicks > m_song->SONG_DURATION_TICKS)
    {
        //if song loops, need to recalibrate
        m_battleTime = Time::Zero;
        m_activeTime = false;
        m_calibration->activate();
        m_state = CALIBRATE;
    }
}
void Battle::updateEndScreen()
{
    //display win results / animation
    if(m_status1->getHealth() <= 0)
    {
        m_p2->setState(VICTORY);
        m_endScreen->activate(P2);
        m_song->stop();
    }
    if(m_status2->getHealth() <= 0)
    {
        m_p1->setState(VICTORY);
        m_endScreen->activate(P1);
        m_song->stop();
    }
    //have some kind of input handler that lets you hit space to restart back to menu
}
void Battle::updateCalibrate()
{
    if(m_calibration->getIsDone() == true) 
    {
        m_state = MENU;
        cout << "calibration done" << endl;
        m_magic1->setActive(true);
        m_magic2->setActive(true);
    }
    else if(m_calibration->getIsActive() == false)
    {
        m_calibration->activate();
        cout << "calibration activated" << endl;
    }
}
void Battle::updateMenu()
{
    if(m_combatMenu->getIsDone() == true)
    {
        m_combat1 =  m_combatMenu->getChoice(P1);
        m_combat2 =  m_combatMenu->getChoice(P2);
        //cout << "Choice 1: " << m_combat1 << endl;
        //cout << "Choice 2: " << m_combat2 << endl;
        setEffects();
        m_state = INPUT; //if menu is done, next phase
        m_combatMenu->reset();
        cout << "CombatMenu done" << endl;
    }
    else if (m_combatMenu->getIsActive() == false)
    {
        m_combatMenu->activate(); //if menu hasnt started, start it
        cout << "combat menu activated" << endl;
    }
}
void Battle::updateInput()
{
    if(getIsInputDone() == true) //both players input done
    {
        //calculate scores, change state
        cout << "Rhythm input done" << endl;
        calculateScores();
        m_scoreP1 = getScore(P1);
        m_scoreP2 = getScore(P2);
        m_state = EFFECT;
        m_input1->reset(); //rhythm tester wont work if reset immediately, change for testing
        m_input2->reset();
        m_bar1->deactivate();
        m_bar2->deactivate();
        //cout << "input is done" << endl;
        //probably also set the rhythm bar to deactivate or change color here
    }
    else if(getIsInputActive() == false) //this block executes once for activation
    {
        //maybe only activate rhythm input at a certain time like at the start of a measure
        //set effect on or to rainbow if combat option is magic related
        int currTime = getCurrentTicks();
        int recordTime = m_song->TICKS_PER_MEASURE * 2; //2 measures
        //int recordTime = m_song->TICKS_PER_MEASURE;
        cout << "recordTime: " << recordTime << endl;
        m_input1->activate(currTime, recordTime);
        m_input2->activate(currTime, recordTime);
        cout << "rhythm input activated" << endl;

        //load notes to rhythm bar
        //need to load notes of the correct track via combatChoice
        Track* track1 = getTrackFromCombat(m_combat1);
        Track* track2 = getTrackFromCombat(m_combat2);
        
        m_bar1->setRange(recordTime);
        m_bar2->setRange(recordTime);
        m_bar1->setDisplayRange(recordTime / 2);
        m_bar2->setDisplayRange(recordTime / 2);
        //check how long these take?
        Clock searchTime;
        Time searchDT = searchTime.restart();
        m_bar1->activate(track1, currTime);
        m_bar2->activate(track2, currTime);
        searchDT = searchTime.restart();
        cout << "Time to load notes: " << searchDT.asSeconds() << endl;
    }
    m_bar1->update(getCurrentTicks());
    m_bar2->update(getCurrentTicks());
}

void Battle::updateEffect()
{
    //cout << "entered effect state" << endl;
    combatAction();
    m_status1->activateUpdate();
    m_status2->activateUpdate();
    //itd be nice to have some kind of pause / damage animation here
    //when battleticks goes by like 2 beats, set character animation states to action?
    m_state = MENU;
    //calculate effects from rhythm objects, apply damage
    //set back to menu unless the song has ended, then set to calibration somehow
}

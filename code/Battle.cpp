#include "Battle.h"
/////////////////////
using namespace sf;
using namespace std;

Battle::Battle()
{
    m_state = INACTIVE;
    m_calibration = new Calibration();
    m_combatMenu = new CombatMenu();
    m_input1 = new Rhythm(P1);
    m_input2 = new Rhythm(P2);
    //m_recordingInput = false; //unnecessary from Rhythm testing
    m_status1 = new StatusBar();
    m_status2 = new StatusBar();
    m_magic1 = new Effect();
    m_magic2 = new Effect();

    m_turn = P1;
    m_display = DARK;
    m_combat1 = NO_SELECTION;
    m_combat2 = NO_SELECTION;
    
    m_actionScoreP1 = 0;
    m_actionScoreP2 = 0;
 //set up stuff that doesnt require user input
}

//void Battle::setChoices(Display display, CharacterType p1_type, CharacterType p2_type, string songFileName)
void Battle::setChoices(vector<int> choices)
{
    m_state = CALIBRATE; //1st step of actual battle 
    //I dont like these magic numbers but Im testing the menu
    CharacterType p1_type, p2_type;
    Display display;
    if(choices.size() == 3)
    {
        if(choices[0] == 1){p1_type = CAT;}
        else{p1_type = PANDA;}
        if(choices[1] == 1){p2_type = CAT;}
        else{p2_type = PANDA;}
        if(choices[2] == 1){display = LIGHT;}
        else{display = DARK;}
    }
    else
    {
        cout << "invalid choices vector size" << endl;
        for(size_t i = 0; i<choices.size();i++)
        {
            cout << "choice " << i << ": " << choices[i] << endl;
        }
    }

    //this may be a selectable option in the future
    string songFileName = "sound/Untitled 05.ogg";
    //songFileName = "sound/Calibration.wav";
    //songFileName = "sound/Untitled Calibrtion B.ogg";

    //set up song
    m_song = new Song(songFileName);
    int BPM = m_song->getBPM(); //important to set frame time for all animation

    //set up colors
    Color outline;
    if(display == DARK)
    {
        outline = Color::White;
        m_display = DARK;
        m_combatMenu->setColor(Color::White);
        m_status1->setUp(P1, Color::White);
        m_status2->setUp(P2, Color::White);
        m_calibration->setColor(Color::White);
    }
    else
    {
        outline = Color::Black;
        m_display = LIGHT;
        m_combatMenu->setColor(Color::Black);
        m_status1->setUp(P1, Color::Black);
        m_status2->setUp(P2, Color::Black);
        m_calibration->setColor(Color::Black);
    }

    m_p1 = new Character(P1, p1_type, outline, BPM);
    m_p2 = new Character(P2, p2_type, outline, BPM);

    m_magic1->setUp(P1, MAGIC, BPM);
    m_magic2->setUp(P2, MAGIC, BPM);
    m_magic1->setActive(true);
    m_magic2->setActive(true);
    
    //set up health bars
    //set up effects
    //set up rhythm bar
    //set up CombatMenu

    m_song->play();
    m_calibration->activate();
}

void Battle::handleInput()
{
    m_p1->handleInput();
    m_p2->handleInput();
    m_combatMenu->handleInput();
    m_calibration->handleInput();
    m_input1->handleInput();
    m_input2->handleInput();
}

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

    int battleTicks = getCurrentTicks();
    if(getIsCalibrated())
    {
        //calculate current time in ticks, update rhythm
        m_activeTime = true;
        m_input1->update(battleTicks);
        m_input2->update(battleTicks);
        //cout << "battle ticks " << battleTicks << endl;
    }
    if(battleTicks > m_song->SONG_DURATION_TICKS)
    {
        //if song loops, need to recalibrate
        m_battleTime = Time::Zero;
        m_activeTime = false;
        m_calibration->activate();
    }

    if(m_status1->getHealth() <= 0 || m_status2->getHealth() <= 0)
    {
        m_state = ENDSCREEN;
        //display win results / animation
        if(m_status1->getHealth() <= 0)
        {
            m_p1->setState(VICTORY);
        }
        if(m_status2->getHealth() <= 0)
        {
            m_p2->setState(VICTORY);
        }
        //have some kind of input handler that lets you hit space to restart back to menu
    }
    else if(m_state == CALIBRATE)
    {
        if(m_calibration->getIsDone() == true) 
        {
            m_state = MENU;
        }
        else if(m_calibration->getIsActive() == false)
        {
            m_calibration->activate();
        }
    }
    else if(m_state == MENU)
    {
        if(m_combatMenu->getIsDone() == true)
        {
            m_combat1 =  m_combatMenu->getChoice(P1);
            m_combat2 =  m_combatMenu->getChoice(P2);
            setEffects();
            m_state = INPUT; //if menu is done, next phase
        }
        else if (m_combatMenu->getIsActive() == false)
            m_combatMenu->activate(); //if menu hasnt started, start it
    }
    else if(m_state == INPUT) 
    {   
        if(getIsInputDone() == true) //both players input done
        {
            //calculate scores, change state
            m_actionScoreP1 = getScore(P1);
            m_actionScoreP2 = getScore(P2);
            m_state = EFFECT;
            //probably also set the rhythm bar to deactivate or change color here
        }
        else if(getIsInputActive() == false)
        {
            //maybe only activate rhythm input at a certain time like at the start of a measure
            //set effect on or to rainbow if combat option is magic related
            int recordTime = m_song->TICKS_PER_MEASURE * 2;
            m_input1->activate(getCurrentTicks(), recordTime);
            m_input2->activate(getCurrentTicks(), recordTime);

            //convert DT to midi time? Is it better to calculate input in the engine?
            //calculate midi time in update.cpp and send it here?
            // m_input1->activate(int midiTime, int range);
        }
    }
    else if(m_state == EFFECT) 
    {
        void combatAction();
        //itd be nice to have some kind of pause / damage animation here
        //when battleticks goes by like 2 beats, set character animation states to action?
        m_state = MENU;
        //calculate effects from rhythm objects, apply damage
        //set back to menu unless the song has ended, then set to calibration somehow
    }
}

int Battle::getCurrentTicks()
{
    int battleTicks = int(m_battleTime.asSeconds() * m_song->TICKS_PER_SECOND);
    return battleTicks;
}

Sprite* Battle::getCharacterSprite(PlayerID id)
{
    if(id == P1){return m_p1->getSprite();}
    else{return m_p2->getSprite();}
}

Sprite* Battle::getCombatMenuSprite()
{
    return m_combatMenu->getSprite();
}
Sprite* Battle::getCalibrationSprite()
{
    return m_calibration->getSprite();
}

vector<RectangleShape*> Battle::getStatusBars(PlayerID id)
{
    if(id == P1)
        return m_status1->getBars();
    else
        return m_status2->getBars();
}

//RectangleShape* Battle::getStatusBar()
//{
//    return m_status1->getHealthBG();
//}

BattleState Battle::getState()
{
    return m_state;
}

void Battle::setState(BattleState state)
{
    m_state = state;
}

Color Battle::getBackground()
{
    Color color = Color::Black;
    if(m_display == LIGHT)
    {color = Color::White;}
    else if(m_display == DARK)
    {color = Color::Black;}
    return color;
}


Sprite* Battle::getEffectSprite(PlayerID id)
{
    //currently magic is the only effect
    if(id == P1)
    {
        return m_magic1->getSprite();
    }
    else
    {
        return m_magic2->getSprite();
    }
}
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
        active2 = true;
        rainbow2 = false;
    }
    setEffectActivity(P1, MAGIC, active1, rainbow1);
    setEffectActivity(P2, MAGIC, active2, rainbow2);
}
bool Battle::getIsCalibrated()
{
    return m_calibration->getIsDone();
}

CombatType Battle::getCombatType(PlayerID id)
{
    return m_combatMenu->getChoice(id);
}

RectangleShape* Battle::getRhythmTester(PlayerID id)
{
    if(id==P1)
        return m_input1->getTester();
    else
        return m_input2->getTester();
}

bool Battle::getIsInputDone() //[done for both players]
{
    bool done = (m_input1->getIsDone() || m_input2->getIsDone());
    return done; //only move on when both are done
}
bool Battle::getIsInputActive()
{
    return m_input1->getIsActive(); //both will be active at the same time
}

void Battle::combatAction()
{
    //really should make this system based on doubles
    const double DEFAULT_MULTIPLIER = 0.25;
    const double MAGIC_ATTACK_MULTIPLIER = DEFAULT_MULTIPLIER * 1.5;
    int effectP1 = 0;
    int effectP2 = 0;
    if(m_combat1 == ATTACK || m_combat1 == BLOCK || m_combat1 == BUILD_METER)
    {
        effectP1 = m_actionScoreP1 * DEFAULT_MULTIPLIER;
    }
    else if(m_combat1 == MAGIC_ATTACK)
    {
        effectP1 = m_actionScoreP1 * MAGIC_ATTACK_MULTIPLIER;
    }
    if(m_combat2 == ATTACK || m_combat2 == BLOCK || m_combat2 == BUILD_METER)
    {
        effectP2 = m_actionScoreP2 * DEFAULT_MULTIPLIER;
    }
    else if(m_combat1 == MAGIC_ATTACK)
    {
        effectP2 = m_actionScoreP2 * MAGIC_ATTACK_MULTIPLIER;
    }

    if(m_combat1 == ATTACK || m_combat1 == MAGIC_ATTACK) //make magic attack even more effective on block?
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
        if(m_combat2 == BLOCK)
        {
            effectP1 -= effectP2;
            if(effectP1 < 0)
                effectP1 = 0;
        }
    }

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
            m_status1->addMeter(-m_status1->getMeter());
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
            m_status2->addMeter(-m_status1->getMeter());
            m_status2->addDamage(meterDrain*-1);
        }
        else
            m_status2->addMeter(-effectP1);
    }

    if(m_combat1 == NO_SELECTION || m_combat2 == NO_SELECTION)
    {
        cout << "Error: NO_SELECTION combat action" << endl;
    }

}

int Battle::getScore(PlayerID id) //return int score/100 of an input session
{
    //change to store scores as Battle data members
    //use helper function to process the rhythm analysis
    if(id == P1)
    {
        return 50;
    }
    else    
        return 50;
}

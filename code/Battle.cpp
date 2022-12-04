#include "Battle.h"
///////////////////
using namespace sf;
using namespace std;

Battle::Battle()
{
    m_state = INACTIVE;
    m_calibration = new Calibration();
    m_combatMenu = new CombatMenu();
    //m_input = new Rhythm();
    //m_recordingInput = false; //unnecessary from Rhythm testing
    m_status1 = new StatusBar();
    m_status2 = new StatusBar();
    m_magic1 = new Effect();
    m_magic2 = new Effect();

    m_turn = P1;
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
//
    m_song->play();
    m_calibration->activate();
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

    if(m_state == CALIBRATE)
    {
        if(m_calibration->getIsDone() == true) //use is done or is active?
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
            m_state = INPUT; //if menu is done, next phase
        else if (m_combatMenu->getIsActive() == false)
            m_combatMenu->activate(); //if menu hasnt started, start it
    }
    else if(m_state == INPUT && m_turn == P1) 
    {
        /*
        if(m_input->getIsDone() == true)
        {
            m_turn = P2; //if recording done, wait. We need two 
            //do the calculations and send score to the necessary place
        }
        else if(m_input->getIsActive() == false)
        {
            //convert DT to midi time? Is it better to calculate input in the engine?
            //calculate midi time in update.cpp and send it here?
            //m_input->activate(P1, int midiTime, int range);
        }
        */
    }
    else if(m_state == INPUT && m_turn == P2) 
    {
        /*
        if(m_input->getIsDone() == true)
        {
            m_state = EFFECT; //if recording done, wait. We need two 
            //do the calculations and send score to the necessary place
        }
        else if(m_input->getIsActive() == false)
        {
            //m_input->activate(P2, int midiTime, int range);
        }
        */
    }
}

void Battle::handleInput()
{
    m_p1->handleInput();
    m_p2->handleInput();
    m_combatMenu->handleInput();
    m_calibration->handleInput();
}

Sprite Battle::getCharacterSprite(PlayerID id)
{
    if(id == P1){return m_p1->getSprite();}
    else{return m_p2->getSprite();}
}

Sprite Battle::getCombatMenuSprite()
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


Sprite Battle::getEffectSprite(PlayerID id)
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
void Battle::setEffectActivity(Effect *effect, bool active)
{
    effect->setActive(active);
}
bool getIsEffectActive(Effect *effect)
{
    return effect->getIsActive();
}
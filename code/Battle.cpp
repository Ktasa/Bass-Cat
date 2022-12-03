#include "Battle.h"
///////////////////
using namespace sf;
using namespace std;

Battle::Battle()
{
    m_state = INACTIVE;
    m_combatMenu = new CombatMenu();
    m_input = new Rhythm();
    //m_recordingInput = false; //unnecessary from Rhythm testing
    m_status1 = new StatusBar();

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

    //set up song
    m_song = new Song(songFileName);
    int BPM = m_song->getBPM(); //important to set frame time for all animation

    //set up characters
    Color outline;
    if(display == DARK)
    {
        //cout << "Entering battle; if display == DARK" << endl;
        outline = Color::White;
        m_display = DARK;
        m_combatMenu->setColor(Color::White);
    }
    else
    {
        outline = Color::Black;
        m_display = LIGHT;
        m_combatMenu->setColor(Color::Black);
    }

    m_p1 = new Character(P1, p1_type, outline, BPM);
    m_p2 = new Character(P2, p2_type, outline, BPM);
    //set up all positions here too?


    
    //set up health bars
    //set up effects
    //set up rhythm bar
    //set up CombatMenu

    m_song->play();
}

void Battle::update(float dt)
{

    m_p1->updateCharacter(dt);
    m_p2->updateCharacter(dt);
    m_combatMenu->update();

    if(m_state == MENU)
    {
        if(m_combatMenu->getIsDone() == true)
            m_state = INPUT; //if menu is done, next phase
        else if (m_combatMenu->getIsActive() == false)
            m_combatMenu->activate(); //if menu hasnt started, start it
    }
    else if(m_state == INPUT && m_turn == P1) 
    {
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
    }
    else if(m_state == INPUT && m_turn == P2) 
    {
        if(m_input->getIsDone() == true)
        {
            m_state = EFFECT; //if recording done, wait. We need two 
            //do the calculations and send score to the necessary place
        }
        else if(m_input->getIsActive() == false)
        {
            //m_input->activate(P2, int midiTime, int range);
        }
    }
}

void Battle::handleInput()
{
    m_p1->handleInput();
    m_p2->handleInput();
    m_combatMenu->handleInput();
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
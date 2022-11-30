#include "Battle.h"
//
using namespace sf;
using namespace std;

Battle::Battle()
{
    m_state = INACTIVE;
    m_combatMenu = new CombatMenu();
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
        else{p1_type = DOG;}
        if(choices[1] == 1){p2_type = CAT;}
        else{p2_type = DOG;}
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
    string songFileName = "placeholder";

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
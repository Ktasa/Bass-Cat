#include "Battle.h"
/////////////////////
using namespace sf;
using namespace std;

Battle::Battle()
{
    m_state = INACTIVE;
    m_calibration = new Calibration();
    m_combatMenu = new CombatMenu();
    m_endScreen = new EndScreen();
    m_input1 = new Rhythm(P1);
    m_input2 = new Rhythm(P2);
    m_bar1 = new RhythmBar();
    m_bar2 = new RhythmBar();
    //m_recordingInput = false; //unnecessary from Rhythm testing
    m_status1 = new StatusBar();
    m_status2 = new StatusBar();
    m_magic1 = new Effect();
    m_magic2 = new Effect();

    //m_turn = P1;
    m_display = DARK;
    m_combat1 = NO_SELECTION;
    m_combat2 = NO_SELECTION;
    
    m_scoreP1 = 0.0;
    m_scoreP2 = 0.0;
    
    m_battleTime = Time::Zero;
}

//void Battle::setChoices(Display display, CharacterType p1_type, CharacterType p2_type, string songFileName)
void Battle::setChoices(vector<int> choices)
{
    m_state = CALIBRATE; //1st step of actual battle 
    
    //TESTING ENDSCREEN
    //m_state = ENDSCREEN;
    //m_endScreen->activate(P1);

    CharacterType p1_type, p2_type;
    Display display;
    if(choices.size() == 3)
    {
        if(choices[0] == 1){p1_type = CAT;}
        else{p1_type = PANDA;}
        if(choices[1] == 1){p2_type = CAT;}
        else{p2_type = PANDA;}
        if(choices[2] == 1){display = LIGHT;}
        else if(choices[2] == 2){display = DARK;}
        else {display = GALAXY;}
    }

    //this may be a selectable option in the future
    string songFileName = "sound/Untitled 05.ogg";

    //set up song
    m_song = new Song(songFileName);
    int BPM = m_song->getBPM(); //important to set frame time for all animation

    //set up colors
    Color outline;
    Color rhythmBarColor;
    if(display == DARK)
    {
        outline = Color::White;
        rhythmBarColor = Color::Black;
        m_display = DARK;
        m_combatMenu->setColor(Color::White);
        m_status1->setUp(P1, Color::White);
        m_status2->setUp(P2, Color::White);
        m_calibration->setColor(Color::White);
    }
    else if(display == GALAXY)
    {
        outline = Color::White;
        rhythmBarColor = Color::Black;
        m_display = GALAXY;
        m_combatMenu->setColor(Color::White);
        m_status1->setUp(P1, Color::White);
        m_status2->setUp(P2, Color::White);
        m_calibration->setColor(Color::White);
    }
    else
    {
        outline = Color::Black;
        rhythmBarColor = Color::White;
        m_display = LIGHT;
        m_combatMenu->setColor(Color::Black);
        m_status1->setUp(P1, Color::Black);
        m_status2->setUp(P2, Color::Black);
        m_calibration->setColor(Color::Black);
    }

    m_p1 = new Character(P1, p1_type, outline, BPM);
    m_p2 = new Character(P2, p2_type, outline, BPM);

    //set up rhythm bars, range is 8 beats
    m_bar1->setUp(P1, rhythmBarColor, 480 * 8);
    m_bar2->setUp(P2, rhythmBarColor, 480 * 8);

    m_magic1->setUp(P1, MAGIC, BPM);
    m_magic2->setUp(P2, MAGIC, BPM);

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

int Battle::getCurrentTicks()
{
    int battleTicks = int(m_battleTime.asSeconds() * m_song->TICKS_PER_SECOND);
    return battleTicks;
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
Display Battle::getDisplay()
{
    return m_display;
}
Sprite* Battle::getCalibrationSprite()
{
    return m_calibration->getSprite();
}
Sprite* Battle::getCombatMenuSprite()
{
    return m_combatMenu->getSprite();
}
Sprite* Battle::getEndScreenSprite()
{
    return m_endScreen->getSprite();
}
Sprite* Battle::getEndScreenText()
{
    return m_endScreen->getVictorySprite();
}

Sprite* Battle::getCharacterSprite(PlayerID id)
{
    if(id == P1){return m_p1->getSprite();}
    else{return m_p2->getSprite();}
}
vector<RectangleShape*> Battle::getStatusBars(PlayerID id)
{
    if(id == P1)
        return m_status1->getBars();
    else
        return m_status2->getBars();
}
vector<RectangleShape*> Battle::getRhythmBar(PlayerID id)
{
    if (id == P1)
        return m_bar1->getRects();
    else
        return m_bar2->getRects();
}
Sprite* Battle::getEffectSprite(PlayerID id)
{
    //currently magic is the only effect
    if(id == P1)
        return m_magic1->getSprite();
    else
        return m_magic2->getSprite();
}
RectangleShape* Battle::getRhythmTester(PlayerID id)
{
    if(id==P1)
        return m_input1->getTester();
    else
        return m_input2->getTester();
}

// ************************* Functions mostly for internal use
bool Battle::getIsCalibrated()
{
    return m_calibration->getIsDone();
}
//check state of rhythm input
bool Battle::getIsInputDone() //[done for both players]
{
    bool done = (m_input1->getIsDone() || m_input2->getIsDone());
    return done; //only move on when both are done
}
bool Battle::getIsInputActive()
{
    return m_input1->getIsActive(); //both will be active at the same time
}
CombatType Battle::getCombatType(PlayerID id)
{
    return m_combatMenu->getChoice(id);
}
Track* Battle::getTrackFromCombat(CombatType combat)
{
    Track* track;
    int trackNum = 0;
    if (combat == ATTACK)
        trackNum = 3; //drums
    if (combat == BLOCK)
        trackNum = 1; //piano
    if (combat == BUILD_METER)
        trackNum = 2; //bass
    if (combat == MAGIC_ATTACK)
        trackNum = 0; //sax

    cout << "Track selected: " << trackNum << endl;
    track = m_song->getTrack(trackNum);
    return track;
}
double Battle::getScore(PlayerID id) //return int score/100 of an input session
{
    //change to store scores as Battle data members
    //use helper function to process the rhythm analysis
    double score = 0.0;
    if(id == P1)
    {
        score = m_scoreP1;
    }
    else    
        score = m_scoreP2;

    return score;
}
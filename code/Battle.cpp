#include "Battle.h"

using namespace sf;
using namespace std;

Battle::Battle(Display display, CharacterType p1_type, CharacterType p2_type, string songFileName)
{

    //set up song
    m_song = new Song(songFileName);
    int BPM = m_song->getBPM();

    //set up characters
    Color outline, background;
    if(display == DARK)
    {
        outline = Color::White;
        background = Color::Black;
    }
    else
    {
        outline = Color::Black;
        background = Color::White;
    }

    m_p1 = new Character(P1, p1_type, outline, BPM);
    m_p2 = new Character(P2, p2_type, outline, BPM);
    //set up all positions here too?


    
    //set up health bars
    //set up effects
    //set up rhythm bar
    //set up CombatMenu
}

Sprite Battle::getCharacterSprite(PlayerID id)
{
    if(id == P1){return m_p1->getSprite();}
    else{return m_p2->getSprite();}
}
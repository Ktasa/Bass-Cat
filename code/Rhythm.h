#ifndef RHYTHM_H
#define TRHYTHM_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
//#include "Song.h"
#include "Track.h"
#include "Note.h"
#include "Character.h" //PlayerID

using namespace sf;
using namespace std;

//CLASS HAS NOT BEEN CHECKED FOR ERRORS

class Rhythm
{
public:
    //add destructor to free input notes that are no longer relevant?
    Rhythm();
    void activate(PlayerID id, int midiTime, int range); //time of start and range in midi clock units
    Track getTrack();
    void handleInput(); 
    void update(int midiTime);
    bool getIsDone();
    bool getIsActive();

private:
    Track m_track;
    Note* m_note; 
    PlayerID m_player;

    int m_startTime; 
    int m_recordingTime; // how long to record input

    bool m_active;
    bool m_isPressed; 
    bool m_isDone;
    bool m_stateChange; //check whether an input is starting or ending

    //Consider that start and end notes will have lower scores if theyre cut off by the recording
    //adjust calculations of percentage of notes hit
};

#endif

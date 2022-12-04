#ifndef RHYTHM_H
#define RHYTHM_H

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
    Rhythm(PlayerID id);
    void activate(int midiTime, int range); //time of start and range in midi clock units
    Track getTrack();
    void handleInput(); 
    void update(int midiTime);
    bool getIsDone();
    bool getIsActive();
    void updateTester(int midiTime);
    RectangleShape* getTester();

private:
    Track m_track; //make track*
    Note* m_note; 
    PlayerID m_player;

    RectangleShape *m_tester; //plays back your input rhythms as a series of blinks
    int readTime; //what time of the rhythm is the tester reading
    int readNote;
    int playbackStartTime; //what tick did playback start
    vector<Note*> m_notes;
    //int noteTimeElapsed; //measure how much the display is working

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

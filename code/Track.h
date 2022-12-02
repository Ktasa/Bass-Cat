#ifndef TRACK_H
#define TRACK_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Song.h"
#include "Note.h"

using namespace sf;
using namespace std;

class Track
{
public:
    //tracks should be set up by Song::loadTracks() by adding notes according to file read
    Track();
    void addNote(Note* note);
    Note* getNote(int unit);
    vector<Note*> getNotesInRange(int unit, int range); //helper function for Song::getNotesInRange
    //vector<Note*>

private:
    //how to access the right notes if given units
    //Loop through values until you get one that says its unit is in range?
    //use map<int unit, note*> for each one?
    //vector<bool> unitPlaying; //store whether a note is playing at each unit?
    vector<Note*> m_notes;
    int m_totalUnits; //total number of note subunits
    int m_unit; //identify the current subunit of the song
};
Track::Track()
{
    //maybe add BPM or something to the constructor
}



#endif
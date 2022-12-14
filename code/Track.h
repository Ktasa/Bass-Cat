#ifndef TRACK_H
#define TRACK_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
//#include "Song.h"
#include "Note.h"

using namespace sf;
using namespace std;

class Track
{
public:
    //tracks should be set up by Song::loadTracks() by adding notes according to file read
    //add destructor to free input notes that are no longer relevant?
    Track();
    //~Track();
    void clear();
    void addNote(Note* note);
    void setSongDuration(int midiTime);
    vector<Note*> getNotes(); //returns all notes. Helper function for Rhythm class
    vector<Note*> getNotesInRange(int unit, int range); //helper function for Song::getNotesInRange
   
    Note* getNote(int index); //for testing CSV reading
    Note* getNoteFromTick(int midiTime);
private:
    //how to access the right notes if given units
    //Loop through values until you get one that says its unit is in range?
    //use map<int unit, note*> for each one?
    //vector<bool> unitPlaying; //store whether a note is playing at each unit?
    vector<Note*> m_notes;
    int m_totalUnits; //total number of note subunits
    int m_unit; //identify the current subunit of the song
    int m_currNote; //current note of the song
    int m_songDuration; //end midiTime of the actual song, not just the track
};


#endif
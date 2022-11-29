#ifndef SONG_H
#define SONG_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>
#include <vector>
#include "Track.h"
#include "Note.h"

using namespace sf;
using namespace std;

class Song
{
public:
    Song();
    Song(string fileName);
    void loadSong(string fileName);
    void loadTracks(string fileName);
    double getDuration();
    int getBPM();

    //get unit info? (read unit length info from track file when loading)

    //Track getTrack(int trackID);
    //vector<Note*> getNotesInRange(int trackID, int unit); //param: instrument and time unit

    //setters

private:
    Music m_music;

    //vector<Track*> m_tracks;
    double duration; //duration in seconds
    int totalUnits; //total number of note subunits
    int BPM;
    int range; //how many notes to display at once in HUD
    int unit; //identify the current subunit of the song
    double unitLen; //seconds per unit
    double currTime; //identify current time playing of song

    //Track: get note values param range

};



#endif
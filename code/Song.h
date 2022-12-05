#ifndef SONG_H
#define SONG_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Track.h"
//#include "Note.h"

using namespace sf;
using namespace std;

class Song
{
public:
    const int SONG_DURATION_TICKS = 90240; //Not the same between all songs, add to read from file
    const int TICKS_PER_BEAT = 480; //same as m_quarterTime
    const int TICKS_PER_MEASURE = 3840;
    const double TICKS_PER_SECOND = 640.0; 
    const double SECONDS_PER_TICK = 1.0 / 640.0;

    Song();
    Song(string fileName);
    void loadSong(string fileName);
    void loadTracks(string fileName);
    double getDuration();
    int getBPM();
    void play();
    void pause();
    void stop();
    void setOffset(float seconds);
    bool isPlaying();

    //get unit info? (read unit length info from track file when loading)

    Track getTrack(int trackID);
    //vector<Note*> getNotesInRange(int trackID, int unit); //param: instrument and time unit

    //setters

private:
    Music m_music;

    vector<Track*> m_tracks;
    double m_duration; //duration in seconds
    int m_totalUnits; //total number of note subunits
    int m_BPM;
    int m_quarterTime;
    int m_range; //how many notes to display at once in HUD
    int m_unit; //identify the current subunit of the song
    
    double m_unitLen; //seconds per unit
    double m_currTime; //identify current time playing of song

    //Track: get note values param range

};



#endif
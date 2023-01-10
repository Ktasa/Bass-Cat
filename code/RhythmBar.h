#pragma once

#include "Song.h"
#include "Track.h"
#include "Note.h"
#include "Character.h" //playerID
//make separate header file just for enumerated types
//so that I dont have to keep doing these workarounds?
//enum Display;

//if I always know all of the note data in advance,
//can I create the rectangles just one time and offset position?

//program flow will exit the input phase based on the input class deactivating,
//so its not necessary to track when it ends
class RhythmBar
{
public:
    RhythmBar();
    void setUp(PlayerID id, Color color, int range);
    void setPlayer(PlayerID id);
    void setColor(Color color);
    void setRange(int units);
    void setDisplayRange(int units);

    vector<RectangleShape*> getRects();
    void setActive(bool active);
    void activate(Track* track, int midiTime); //not sure whether to use activate or set active
    void deactivate();
    void loadNotes(vector<Note*> notes);
    void update(int midiTime);

    bool getActive();

private:
    vector<RectangleShape*> m_rects;
    bool m_active;
    int m_range; //total range to display 
    int m_displayRange; //what range is displayed at a time
    int m_activateTime; //midiTime at activation
    int m_lastUpdated; //help for updating rectangle positions
    Color m_color; 
    PlayerID m_player;

};


//use two of these to display each prompt
//need player position and color to determine stuff
//p1 is slightly left of center, p2 right of center
//Dark: bg is black with white outline, notes are solid white within
//Light: reverse of dark
//Galaxy: same as dark
//not sure whether to actually use a background bar
//possibly use red/blue themed notes to make it clearer whose notes are which

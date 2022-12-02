#ifndef NOTE_H
#define NOTE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
//#include "Battle.h" 

using namespace sf;
using namespace std;

class Note
{
public:
    Note();
    Note(int midiTime);
    void setStart(int midiTime);
    void setDuration(int midiTime);
    virtual int checkNoteAccuracy() = 0;
    
protected:
    int m_start; //start time in midi clock units
    int m_duration; //note duration in midi clock units

};


class Tapper : public Note
{
public:
    Tapper(int midiTime);
    int checkNoteAccuracy() override;
};

class Holder : public Note
{
public:
    Holder(int midiTime);
    int checkNoteAccuracy() override;
//private:
    //int m_duration; //how many units does this note last
};



#endif
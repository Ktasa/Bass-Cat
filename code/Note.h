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
    //virtual ~Note() = default;
    Note(int midiTime);
    void setStart(int midiTime);
    void setDuration(int midiTime);
    int getStart();
    int getDuration();
    //check the accuracy of an input compared to the note
    virtual double checkNoteAccuracy(Note* input) = 0;
    virtual bool isTapper() = 0;
    
protected:
    int m_start; //start time in midi clock units
    int m_duration; //note duration in midi clock units

};


class Tapper : public Note
{
public:
    Tapper(int midiTime);
    double checkNoteAccuracy(Note* input) override;
    bool isTapper() override;
};

class Holder : public Note
{
public:
    Holder(int midiTime);
    double checkNoteAccuracy(Note* input) override;
    bool isTapper() override;
//private:
    //int m_duration; //how many units does this note last
};



#endif
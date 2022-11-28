#ifndef NOTE_H
#define NOTE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class Note
{
public:
    Note(int unit);
    virtual int checkNoteAccuracy() = 0;
    
protected:
    int unit; //identify what subunit of the song this note is
    double timeStamp; //whats the real time value of this note? Might not be useful
};

class Tapper : public Note
{
public:
    Tapper(); //call note constructor with unit in definition
    int checkNoteAccuracy() override;
};

class Holder : public Note
{
public:
    Holder(int duration);
    int checkNoteAccuracy() override;

private:
    int duration; //how many units does this note last
};

//use to mark empty space in track?
//probably not using this
/*
class Silence : public Note
{};
*/

#endif
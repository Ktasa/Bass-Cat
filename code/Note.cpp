#include "Note.h"
#include <cmath>

Note::Note()
{
    m_start = 0;
    m_duration = 0;
}
Note::Note(int midiTime)
{
    m_start = midiTime;
}

void Note::setStart(int midiTime)
{
    m_start = midiTime;
}
void Note::setDuration(int midiTime)
{
    m_duration = midiTime;
}
int Note::getStart()
{
    return m_start;
}
int Note::getDuration()
{
    return m_duration;
}

Tapper::Tapper(int midiTime)
{
    m_start = midiTime;
}

double Tapper::checkNoteAccuracy(Note* input)
{
    //Tappers ignore duration of input

    double score; 

    int inputStart = input->getStart();

    //calculate margin of error for early/late inputs
    //shorter notes have lower error margins

    int quarter = 480; //480 ticks per beat in current song (change to be more reusable later)
    int eighth = quarter / 2;

    int margin = eighth; //default max margin is 8th
    if(m_duration <= eighth) 
    {
        margin = m_duration / 2; //for short notes, margin changes to duration / 2
    }
    int inputError = abs(inputStart - m_start); //difference in start time
    if(inputError >= margin)
    {
        score = 0; //out of allowed range
    }
    else
    {
        score = 1 - (double(inputError) / margin); //ratio within range
    }

    return score;
}

Holder::Holder(int midiTime)
{
    m_start = midiTime;
}
double Holder::checkNoteAccuracy(Note* input)
{
    //Holders account for the start and end of a note

    // - score is reduced if input starts early or ends late
    // - score is maxScore - (start error + end error)?

    double score; 

    int inputStart = input->getStart();
    int inputDuration = input->getDuration();
    int inputEnd = inputStart + inputDuration;

    //calculate startError and endError
    int startError = abs(inputStart - m_start); //difference in start time
    int endError = abs(inputEnd - (m_start + m_duration));
    int totalError = startError + endError;
    //error relative to total duration of note
    double proportionalError = double(totalError) / m_duration;

    score = 1 - proportionalError; 

    return score;
}

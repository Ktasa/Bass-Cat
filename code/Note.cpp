#include "Note.h"

Note::Note()
{}
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

Tapper::Tapper(int midiTime)
{
    m_start = midiTime;
}
int Tapper::checkNoteAccuracy()
{
    //dont factor duration the same way as Holder
    return 0; //temp
}

Holder::Holder(int midiTime)
{
    m_start = midiTime;
}
int Holder::checkNoteAccuracy()
{
    return 1; //temp
}
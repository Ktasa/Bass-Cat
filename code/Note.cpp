#include "Note.h"
/// //
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

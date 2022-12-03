#include "Rhythm.h"

Rhythm::Rhythm()
{
    m_active = false;
    m_isPressed = false; 
    m_isDone = false;
    m_stateChange = false; 
}
void Rhythm::activate(PlayerID id, int midiTime, int range)
{
    m_startTime = midiTime;
    m_recordingTime = range;
    m_player = id;
    m_active = true;
    m_track.clear(); //empty vector for new inputs
}

void Rhythm::handleInput()
{
    if(m_active)
    {
        Keyboard::Key key;
        if(m_player == P1)
            key = Keyboard::Space;
        else
            key = Keyboard::Return;
        
        bool checkChange = m_isPressed;
        if(Keyboard::isKeyPressed(key))
        {
            m_isPressed = true; 
        }
        else
            m_isPressed = false;
        if(checkChange != m_isPressed)
            m_stateChange = true;
    }
}

void Rhythm::update(int midiTime)
{
    //check if within active time period
    bool checkChange = m_active;
    m_active = (m_recordingTime >= m_startTime + midiTime); 
    if(checkChange != m_active) 
    {
        //active period just ended, cleanup
        m_isDone = true;
        
        //if holding note when expired, set duration and add it to track
        if(m_isPressed)
        {
            int duration = midiTime - m_note->getStart();
            m_note->setDuration(duration);
            m_track.addNote(m_note);
        }
        
    }

    //input changed to true, start of new input
    if(m_stateChange && m_isPressed)
    {
        //create note with start time
        m_note = new Holder(midiTime);
    }
    //input changed to false, end of input
    else if(m_stateChange && !m_isPressed)
    {
        //set duration of our note for this input, add it to the track
        int duration = midiTime - m_note->getStart();
        m_note->setDuration(duration);
        m_track.addNote(m_note);
    }
}
bool Rhythm::getIsActive()
{
    return m_active;
}
bool Rhythm::getIsDone()
{
    return m_isDone;
}
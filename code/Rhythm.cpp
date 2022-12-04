#include "Rhythm.h"
//
Rhythm::Rhythm()
{
    m_active = false;
    //m_isPressed = false; 
    //m_isDone = false;
    //m_stateChange = false; 

    //set up rectangle display for testing
    //Vector2f resolution;
	//resolution.x = VideoMode::getDesktopMode().width;
	//resolution.y = VideoMode::getDesktopMode().height;

    //m_tester->setSize(Vector2f(resolution.x / 5, resolution.y / 5));
    //m_tester->setFillColor(Color::Black);
    //m_tester->setPosition(resolution.x / 2, resolution.y / 2);
    //currentTime = 0;
    //currentNote = 0;
    //80BPM at 480 clocks per second

}
/*
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
    else
    {
        m_isPressed = false;
    }
}

void Rhythm::update(int midiTime)
{
    //check if within active time period
    bool checkChange = m_active;
    m_active = (m_recordingTime >= m_startTime + midiTime); 
    if(checkChange != m_active && !m_active) 
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

    //updateTester(midiTime); //tester will play back input when done
}
bool Rhythm::getIsActive()
{
    return m_active;
}
bool Rhythm::getIsDone()
{
    return m_isDone;
}

void Rhythm::updateTester(int midiTime)
{
    if (m_isDone)
    {
        if(m_notes.size() == 0)
            m_notes = m_track.getNotes();
        currentTime += midiTime;
        if(currentNote < m_notes.size())
        {
            int start = m_notes[currentNote]->getStart();
            int end = start + m_notes[currentNote]->getDuration();
            if(start <= currentTime && currentTime <= end)
            {
                m_tester->setFillColor(Color::White); //flash white to represent user input
            }
            else
            {
                m_tester->setFillColor(Color::Black);
                if(currentTime > end)
                {
                    currentNote++;
                }
            }
        }
        else
        {
            m_isDone = false;
        }
    }
}
RectangleShape* Rhythm::getTester()
{
    return m_tester;
}
*/
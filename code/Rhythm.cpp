#include "Rhythm.h"

#include <iostream>
using namespace std;
Rhythm::Rhythm(PlayerID id)
{
    m_track = new Track(); //moved to activate()
    m_player = id;
    m_active = false;
    m_isPressed = false; 
    m_isDone = false;
    m_stateChange = false; 
    //cout << "isDone set false by constructor" << endl;

    //set up rectangle display for testing
    Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

    m_tester = new RectangleShape();
    m_tester->setSize(Vector2f(resolution.x / 10, resolution.y / 40));
    m_tester->setFillColor(Color::Black);
    if(id==P1)
        m_tester->setPosition(resolution.x *float(0.28), resolution.y *float(0.3));
    else
        m_tester->setPosition(resolution.x *float(0.33), resolution.y *float(0.3));
    readTime = 0;
    readNote = 0;
    playbackStartTime = 0;
    //80BPM at 480 clocks per second
}

void Rhythm::activate(int startMidiTime, int range)
{
    //cout << "Rhythm activated" << endl;
    m_startTime = startMidiTime;
    m_recordingTime = range;
    m_active = true;
    m_isDone = false;
    m_track->clear(); //empty vector for new inputs, use track destructor though
    m_tester->setFillColor(Color::Red); //red represents recording
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
            //cout << "rhythm input true" << endl;
        }
        else
            m_isPressed = false;
        //track when input turns on or off
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
    if(m_active)
    {
        //check if within active time period
        bool checkChange = m_active;
        m_active = (midiTime < m_startTime + m_recordingTime);
        //find the moment of deactivation; active changes from true to false
        if(checkChange != m_active) 
        {
            //active period just ended, cleanup
            m_isDone = true;
            cout << "isDone set true in Rhythm::update" << endl;
            
            //if holding note when expired, set duration and add it to track
            if(m_isPressed)
            {
                //cout << "last note added" << endl;
                int duration = midiTime - m_note->getStart();
                m_note->setDuration(duration);
                m_track->addNote(m_note);
            }
            
        }

        //input changed to true, start of new input
        if(m_stateChange && m_isPressed)
        {
            //create note with start time
            m_note = new Holder(midiTime);
            m_stateChange = false;
            //cout << "new note added" << endl;
        }
        //input changed to false, end of input
        else if(m_stateChange && !m_isPressed)
        {
            //set duration of our note for this input, add it to the track
            int duration = midiTime - m_note->getStart();
            m_note->setDuration(duration);
            m_track->addNote(m_note);
            m_stateChange = false;
            //cout << "note duration set" << endl;
        }
    }
    //updateTester(midiTime); //tester will play back input when done
}
bool Rhythm::getIsActive()
{
    return m_active;
}
bool Rhythm::getIsDone()
{
    //cout << "returning " << boolalpha << m_isDone << "to update (getIsDone)" << endl;
    return m_isDone;
}
void Rhythm::reset()
{
    cout << "reset rhythm input" << endl;
    m_active = false;
    m_isDone = false;
    //resetting isDone from outside is necessary to determine when scores have already been input
    //other stuff gets reset at activation
}
void Rhythm::updateTester(int midiTime) //(no longer relevant)
{

    //cout << "Entering rhythm updateTester" << endl;
    if (m_isDone)
    {
        //cout << "Entering updateTester (isDone)" << endl;
        if(m_notes.size() == 0)
        {
            //cout << "initializing playback" << endl;
            //load finished vector for first time
            m_notes = m_track->getNotes();
            //set internal time
            playbackStartTime = midiTime;
            if(m_notes.size() != 0)
            {
                readTime = m_notes[0]->getStart();
                //cout << "read time start: " << readTime << endl;
                //get start time of notes to be read
            }
            else
            {
                //cout << "Empty vector: isDone set to false" << endl;
                m_isDone = false; //if empty, finish by reseting isDone
            }
        }
        int playbackElapsed = midiTime - playbackStartTime;
        readTime = playbackElapsed; //increment by elapsed time
        size_t readNoteSizeT = readNote; //what is the appropriate response to size_t int comparison
        if(readNoteSizeT < m_notes.size()) //avoid out of range
        {
            //cout << "readNote is in range" << endl;
            int start = m_notes[readNote]->getStart();
            int end = start + m_notes[readNote]->getDuration();
            //cout << "start time: " << start << endl;
            //cout << "read time: " << readTime << endl;
           // cout << "end time: " << end << endl << endl;
            if(start <= readTime && readTime <= end)
            {
                //cout << "note is active; flash green" << endl;
                m_tester->setFillColor(Color::Green); //flash white to represent user input
            }
            else
            {
                //cout << "note is inactive; flash black" << endl;
                m_tester->setFillColor(Color(0,0,0,0)); //consider making this clear
                if(readTime > end) //if current note ended
                {
                    readNote++; //move on to the next note
                    //cout << "increment note" << endl;
                }
            }
        }
        else
        {
            //cout << "Read note > notes.size(): done set to false" << endl;
            m_isDone = false;
            /*
            cout << "Table of notes displayed via rectangle" << endl;
            cout << "Index, Start, Duration, End" << endl;
            for(size_t i = 0; i< m_notes.size(); i++)
            {
                int start = m_notes[i]->getStart();
                int duration = m_notes[i]->getDuration();
                int end = start + duration;
                cout << "index: " << i << endl;
                cout << "start: " << start << endl;
                cout << "duration " << duration << endl;
                cout << "end: " << end << endl;
            }
            */

            //clear note vector
            m_notes.clear(); //******memory leak********?
        }
    }
}
RectangleShape* Rhythm::getTester() //no longer relevant
{
    return m_tester;
}
Track* Rhythm::getTrack()
{
    return m_track;
}
int Rhythm::getStartTime()
{
    return m_startTime;
}
int Rhythm::getRecordingTime()
{
    return m_recordingTime;
}
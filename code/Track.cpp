#include "Track.h"
//
Track::Track()
{
    m_unit = 0;
    m_currNote = 0;
    //Note* n = new Tapper(m_unit);
    //m_notes.push_back(n);

}
void Track::clear()
{
    for(size_t i=0; i < m_notes.size(); i++)
    {
        //delete m_notes[i]; //bad to delete abstract class pointer
    }
    m_notes.clear();
}

void Track::addNote(Note* note)
{
    m_notes.push_back(note);
}
void Track::setSongDuration(int midiTime)
{
    m_songDuration = midiTime;
}
Note* Track::getNote(int index)
{
    return m_notes[index];
}
Note* Track::getNoteFromTick(int midiTime)
{
    //returns next note after midiTime if nothing found
    //help to calculate margin of error for slightly early inputs
    size_t size = m_notes.size();
    int startSearch;
    int half = m_notes[size/2]->getStart();
    int quarter = m_notes[size/4]->getStart();
    //cout << "Half: " << half << " quarter: " << quarter << endl;
    if(midiTime < half)
    {
        //target is in the 1st half of the vector
        //target in 1st quater
        startSearch = size/4;
        if(midiTime < quarter)
            startSearch = 0;
            //target in 2nd quarter
    }
    else
    {
        //target is in 2nd half
        startSearch = half;
        if(midiTime > quarter * 3)
            startSearch = quarter * 3;
            //target is in last quarter
    }

    //note in range
    cout << "entering find note" << endl;
    bool found = false;
    bool outOfRange = false;
    size_t i = startSearch;
    int index; //store index of the 1st note in range
    while(!found && !outOfRange)
    {
        int startTime = m_notes[i]->getStart();
        int duration = m_notes[i]->getDuration();
        int endOfNote = startTime + duration;
        //first note searched that contains the target time
        if(startTime <= midiTime && midiTime <= endOfNote)
        {
            index = i;
            found = true;
            cout << "index found: " << index << endl;
        }
        //if out of range, nothing found
        if(startTime > midiTime)
        {
            outOfRange = true;
            cout << "search out of range" << endl;
        }
        i++;
    }//endwhile find index
    Note* note;
    if(found)
        note = m_notes[index];
    else
    {
        if(i < size)
            note = m_notes[i]; //return upcoming note
        else
            note = nullptr; //if no more notes in song, return nullptr
    }
    return note;
}
vector<Note*> Track::getNotes()
{
    return m_notes;
}

//make a version based on current note index for checking accuracy?
//UNFINISHED - its hard to check notes in a range when theres looping values

vector<Note*> Track::getNotesInRange(int midiTime, int range)
{
    cout << "midiTime: " << midiTime << " range: " << range << endl;

    //FIX: include a way to exclude duplicate notes (important for drums)
    
    //cout << "entered getNotesInRange" << endl;
    //FIX: Need to check if the desired range contains notes, or returns an empty vector

    //(give the time to rhythm bar and have it adjust the notes)
    //it might be good to edit note values here to make display easier
    //ie set the start of the 1st note to the start time, cutting off the extra bits at the end
    //set the end of the last note to be the end of range

    //start search from most recent?
    //int i = m_currNote;

    vector<Note*> inRange; //maybe return track instead?
    
    size_t size = m_notes.size();
    //bool loop = false;
    int startTimeTarget = midiTime; 

    /*
    if(size > 0)
    {
        //a target time greater than duration suggests we are looping
        if(startTimeTarget > m_songDuration)
        {
            loop = true;
            startTimeTarget %= m_songDuration; //set it back to equivalent time listed in file
        }
    }
    */
    //cout << "entering calculate start search index" << endl;
    int startSearch;
    int half = m_notes[size/2]->getStart();
    int quarter = m_notes[size/4]->getStart();
    cout << "Half: " << half << " quarter: " << quarter << endl;
    if(startTimeTarget < half)
    {
        //target is in the 1st half of the vector
        //target in 1st quater
        startSearch = size/4;
        if(startTimeTarget < quarter)
            startSearch = 0;
            //target in 2nd quarter
    }
    else
    {
        //target is in 2nd half
        startSearch = half;
        if(startTimeTarget > quarter * 3)
            startSearch = quarter * 3;
            //target is in last quarter
    }

    //find 1st note in range
    cout << "entering find startIndex" << endl;
    //FIX: Accessing index out of range error is happening somewhere around here

    //if start time is near the end of the range, need to loop back to check the full range
    //Ex: start time is 50, and the first note is at 0
    bool startFound = false;
    bool outOfRange = false;
    size_t i = startSearch;
    int startIndex; //store index of the 1st note in range
    while(!startFound && !outOfRange)
    {
        //cout << "entering get start time, etc" << endl;
        //cout << "Start search value: " << startSearch << endl;
        //cout << "Notes vector size: " << m_notes.size() << endl;
        //cout << "Index value: " << i << endl;
        int startTime = m_notes[i]->getStart();
        int duration = m_notes[i]->getDuration();
        int endOfNote = startTime + duration;
        //cout << "Note start: " << startTime << endl;
        //first note searched that starts after the target time
        //or note that is currently playing but hasn't finished
        if(startTime >= startTimeTarget || endOfNote > startTimeTarget)
        {
            startIndex = i;
            startFound = true;
            cout << "Start index found: " << startIndex << endl;
        }
        //if out of range, nothing found
        if(startTime > startTimeTarget + range)
        {
            outOfRange = true;
            cout << "startSearch out of range" << endl;
        }
        i++;
    }//endwhile find startIndex

    //Last note requirements:
    // - have a duration that exceeds the end range
    // - or the next note doesnt start in range
    // - loop back to the start of the song (not possible with current calibration mechanics)
    cout << "entering find end search index" << endl;
    int endIndex;
    size_t j = startIndex;
    //int endTimeTarget = midiTime % m_songDuration + range; //use if looping
    int endTimeTarget = startTimeTarget + range;
    cout << "endTimeTarget: " << endTimeTarget << endl;
    //bool loopingBack = false; 
    /*
    //is the range looping back to the beginning
    if(endTimeTarget > m_songDuration)
    {
        loopingBack = true;
        j = 0; 
        endTimeTarget %= m_songDuration; //adjust target to be in the beginning of song
    }
    */

    //infinite loop...
    bool endFound = false;
    bool endOutOfRange = false;
    if(!outOfRange)
    {
        while(!endFound)
        {      
            int startTime = m_notes[j]->getStart();
            int duration = m_notes[j]->getDuration();
            int endOfNote = startTime + duration;
            cout << "start: " << startTime << endl;
            cout << "endOfNote: " << endOfNote << endl;

            //range ends in middle of note, must be the last note
            if(startTime <= endTimeTarget && endTimeTarget <= endOfNote)
            {
                endIndex = j;
                endFound = true;
            }
            //if note out of range, the previous note is the last
            else if(startTime > endTimeTarget)
            {
                endIndex = j-1; 
                endFound = true;
            }
            if(endFound)
            {
                cout << "End index found: " << endIndex << endl;
            }
            if(j >= size)
            {
                endOutOfRange = true;
                cout << "out of range" << endl;
            }
            j++;

        }//endwhile find endIndex
    }//endif (!outOfRange)

    //Move to helper function
    cout << "GetNotesInRange() TEST RESULTS:" << endl;
    //load vector to return
    if(!outOfRange && !endOutOfRange)
    {
        if(startIndex == endIndex)
        {
            inRange.push_back(m_notes[startIndex]); //only one note
        }
        else
        {
            for(int i=startIndex; i < endIndex; i++)
            {
                Note* current = m_notes[i];
                Note* next = m_notes[i+1];
                //if two notes happen at the same time,
                //pick the shortest one
                if(current->getStart() == next->getStart()) 
                {
                    if(current->getDuration() <= next->getDuration()) 
                        inRange.push_back(current);
                    else
                    {
                        inRange.push_back(next);
                        i++;
                    }
                }
                else
                    inRange.push_back(current);
            }
            if(inRange[inRange.size()-1]->getStart() != m_notes[endIndex]->getStart())
            {
                inRange.push_back(m_notes[endIndex]);
            }
            
        }
    }
    else
    {
        cout << "No notes in range" << endl;
    }

    return inRange;

}


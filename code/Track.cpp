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
vector<Note*> Track::getNotes()
{
    return m_notes;
}

//make a version based on current note index for checking accuracy?
//UNFINISHED - its hard to check notes in a range when theres looping values
/*
vector<Note*> Track::getNotesInRange(int midiTime, int range)
{
    //FIX: Need to check if the desired range contains notes, or returns an empty vector

    //(give the time to rhythm bar and have it adjust the notes)
    //it might be good to edit note values here to make display easier
    //ie set the start of the 1st note to the start time, cutting off the extra bits at the end
    //set the end of the last note to be the end of range

    //Ex: midi clock is 480 per quarter note, 1 measure of music is 1920 units
    //left half of rhythm bar represents the past measure
    //right half represents the current measure
    //center is the current time


    //start search from most recent?
    //int i = m_currNote;

    vector<Note*> inRange;
    
    size_t size = m_notes.size();
    bool loop = false;
    int startTimeTarget = midiTime; 

    if(size > 0)
    {
        //a target time greater than duration suggests we are looping
        if(startTimeTarget > m_songDuration)
        {
            loop = true;
            startTimeTarget %= m_songDuration; //set it back to equivalent time listed in file
        }
    }

    int startSearch;
    int half = m_notes[size/2]->getStart();
    int quarter = m_notes[size/4]->getStart();
    if(half > startTimeTarget)
    {
        //target is in the 1st half of the vector
        startSearch = 0;
        if(quarter > midiTime)
            startSearch = quarter;
    }
    else
    {
        //target is in 2nd half
        startSearch = half;
        if(quarter * 3 < midiTime)
            startSearch = quarter * 3;
    }


    //find 1st note in range

    //if start time is near the end of the range, need to loop back to check the full range
    //Ex: start time is 50, and the first note is at 0
    bool startFound = false;
    bool outOfRange = false;
    int i = startSearch;
    int startIndex; //store index of the 1st note in range
    while(!startFound && !outOfRange)
    {
        int startTime = m_notes[i]->getStart();
        int duration = m_notes[i]->getDuration();
        int endOfNote = startTime + duration;

        //first note searched that starts after the target time
        if(startTime >= startTimeTarget)
        {
            startIndex = i;
            startFound = true;
        }
        //if out of range, nothing found
        if(startTime > startTimeTarget + range)
        {
            outOfRange = true;
        }
        i++;
    }//endwhile find startIndex

    //finding the last note will also need to consider looping
    //Last note requirements:
    // - have a duration that exceeds the end range
    // - have a duration that stops before the end but the next note doesnt start in range
    // - loop back to the start of the song

//Ending note might be in near the end of duration or at the beginning
    int endIndex;
    int j = startIndex;
    int endTimeTarget = midiTime % m_songDuration + range;
    bool loopingBack = false; 
    //is the range looping back to the beginning
    if(endTimeTarget > m_songDuration)
    {
        loopingBack = true;
        j = 0; 
        endTimeTarget %= m_songDuration; //adjust target to be in the beginning of song
    }

    bool endFound = false;
    while(!endFound)
    {      
        int startTime = m_notes[j]->getStart();
        int duration = m_notes[j]->getDuration();
        int endOfNote = startTime + duration;

        //range ends in middle of note
        if(startTime <= endTimeTarget && endTimeTarget <= endOfNote)
        {
            endIndex = j;
            endFound = true;
        }
        //note ends before range, check if theres a next note in range
        else if (endOfNote < endTimeTarget)
        {
            //if next index isnt 
            if(j >= size-1)
            {
                //Im pretty sure this is impossible given the loopingBack reset
                cout << "Error: end search index out of range" << endl;
            }
            else
            {
                //its the last note in range if no following notes
                int startTime = m_notes[j+1]->getStart();
                if(startTime > endTimeTarget)
                {
                    endIndex = j;
                    endFound = true;
                }
            }
            
        }

    }//endwhile find endIndex


}
*/

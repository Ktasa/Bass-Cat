#include "Battle.h"

//functions to calculate scores
void Battle::calculateScores()
{
    Rhythm* input = m_input1;
    int track;

    //get the correct track index to compare against
    if(m_combat1 == ATTACK)
        track = 3; //drums
    if(m_combat1 == BLOCK)
        track = 1; //piano
    if(m_combat1 == BUILD_METER)
        track = 2; //bass
    if(m_combat1 == MAGIC_ATTACK)
        track = 0; //sax

    m_scoreP1 = calculateScore(input, track);

    input = m_input2;
    if(m_combat2 == ATTACK)
        track = 3; //drums
    if(m_combat2 == BLOCK)
        track = 1; //piano
    if(m_combat2 == BUILD_METER)
        track = 2; //bass
    if(m_combat2 == MAGIC_ATTACK)
        track = 0; //sax
    
    m_scoreP2 = calculateScore(input, track);
}
int Battle::calculateScore(Rhythm* inputRhythm, int track)
{
    int score = 100; //max score value

    //get times to get the right range of notes
    int startTime = inputRhythm->getStartTime();
    int recordTime = inputRhythm->getRecordingTime();

    //get tracks and note vectors
    //"notes" will refer to the official song notes
    Track* inputTrack = inputRhythm->getTrack();
    Track* noteTrack = m_song->getTrack(track);
    vector<Note*> input = inputTrack->getNotes();
    vector<Note*> notes = noteTrack->getNotesInRange(startTime, recordTime);
    vector<Note*> allNotesInTrack = noteTrack->getNotes();
    
    int trackSize = allNotesInTrack.size(); 
    int notesSize = notes.size(); 
    int inputSize = input.size();
    //figure out how to make score potential proportional to notes in section
    double density = notesSize / trackSize; 

    if(notesSize == 0 || inputSize == 0)
    {
        score = 0; //no notes to play or no notes played --> score 0
    }
    else
    {
        //score of each note stored as percentage of note time played
        double noteScores[notesSize]; 
        int currentNote = 0;
        int currentInput = 0;

        //find the closest input to the current note.
        //only apply an input to the note its closest to

        
        //get the allowed margin of early/late from Note objects
        //polymorph check note accuracy against closest unused input
        //closest should be determined by which note start is closest to input start

    }
    //convert average of note scores into percent to multiply by max score

    return 0; //return score out of 100

}
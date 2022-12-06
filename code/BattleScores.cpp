#include "Battle.h"

//functions to calculate scores
void Battle::calculateScores()
{
    cout << "entering calculateScores()" << endl;
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
double Battle::calculateScore(Rhythm* inputRhythm, int track)
{
    cout << "entering calculateScore()" << endl;
    double score = 100.0; //max score value

    //get times to get the right range of notes
    int startTime = inputRhythm->getStartTime();
    int recordTime = inputRhythm->getRecordingTime();
    
    //get tracks and note vectors
    //"notes" will refer to the official song notes
    Track* inputTrack = inputRhythm->getTrack();
    Track* noteTrack = m_song->getTrack(track);
    vector<Note*> input = inputTrack->getNotes();
    vector<Note*> notes = noteTrack->getNotesInRange(startTime, recordTime);
    
    int notesSize = notes.size(); 
    int inputSize = input.size();
    //figure out how to make score potential proportional to notes in section
    //double density = notesSize / trackSize; 
    
    if(notesSize == 0 || inputSize == 0)
    {
        score = 0; //no notes to play or no notes played --> score 0
    }
    else
    {
        //score of each note stored as percentage of note time played
        double noteScores[notesSize];

        for(int i=0; i<inputSize; i++)
        {
            
            //find index of the closest note for comparison
            //if two inputs are close to the same note, keep the closest
            int inputStart = input.at(i)->getStart();
            int closestIndex = 0;
            int minDistance = abs(inputStart - notes.at(closestIndex)->getStart());
            for(int j=0; j<notesSize; j++)
            {
                int currentDistance = abs(inputStart - notes.at(j)->getStart());
                if(currentDistance < minDistance)
                {
                    minDistance = currentDistance;
                    closestIndex = j;
                }
            }
            //value between 0-1 of note accuracy
// **************************POLYMORPHISM REQUIREMENT*******************************
//checkNoteAccuracy depends on the note type, Tapper or Holder
            double notePerc = notes.at(closestIndex)->checkNoteAccuracy(input.at(i));
            noteScores[closestIndex] = notePerc;
            
        }

        //compute avg of note scores
        double avgScore;
        double total = 0.0;
        for(int k=0; k<notesSize; k++)
        {
            total += noteScores[k];
        }
        avgScore = total / notesSize;

        //score is proportional to avg note score
        score = avgScore * 100;

        //penalty for extra notes / spam prevention
        int silencePenalty = inputSize - notesSize;
        if(inputSize > notesSize)
        {
            for(int i=0; i<silencePenalty; i++)
            {
                score *= 0.95;
            }
        }
        
    //Possible error: 
    //recording doesnt start exactly on a note, so may automatically give a bad score
    //for 1st and last note

    }
    cout << "exiting calculateScore()" << endl;

    if(score < 1.0)
        score = 0.0;

    return score; //return score out of 100.0

}


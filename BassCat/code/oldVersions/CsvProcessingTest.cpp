/*
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Note
{
public:
  //Note(int start, int duration);
  Note(int start);
  void setDuration(int duration);
  int getStart();
  int getDuration();

private:
  int m_start;
  int m_duration;
};
//Note::Note(int start, int duration)
//{
//  m_start = start;
//  m_duration = duration;
//}
Note::Note(int start)
{
  m_start = start;
}
void Note::setDuration(int duration)
{
  m_duration = duration;
}
int Note::getStart()
{
  return m_start;
}
int Note::getDuration()
{
  return m_duration;
}


int main() {
  ifstream in("game data/Calibration.csv");
  
  string field;
  string previous;
  int startTime;
  int duration;
  bool note = false;
  bool end = false;

  vector<Note*> notes;
  
  int currentNote = 0;
  while(!in.eof() && !end)
  {
    string line;
    getline(in, line);
    stringstream s(line);

    //does the line have note data
    std::size_t found = line.find("Note_on_c");
    if (found!=std::string::npos)
    {
      note = true;
    }
    else
    {
      //does the line have tempo data
      found = line.find("Tempo");
      if (found!=std::string::npos)
      {
        string field;
        s >> field;
        s >> field;
        s >> field;
        int uSecondsBeat;
        s >> uSecondsBeat;
        int BPM = (60 * 1000 * 1000) / uSecondsBeat;
        cout << "Bpm: " << BPM << endl;
      }
    }
    //does the line terminate the note data
    found = line.find("End");
    if (found!=std::string::npos)
    {
      note = false;
    }
    
    string track;
    s >> track;
    if(track == "1," && note) //only pay attention to track 1
    {
      //take care of the remaining 5 fields
      //(track), time, Note_on_c / Note_off_c, channel, pitch, velocity
      
      //time
      string timeStr;
      int time;
      s >> timeStr;
      field = field.substr(0, field.length()-1); //ignore comma
      time = stoi(timeStr);
      
      string noteOn; //is the note starting or ending
      string channel; //irrelevant
      string pitch;  //irrelecant
      int velocity; 
      //velocity of 0 also means the end of a note
      //velocity is not followed by a comma
      s >> noteOn;
      
      if(noteOn != "End_track")
      {
        s >> channel >> pitch >> velocity;
  
        //if start of note, record that as start time in Note object
        noteOn = noteOn.substr(0,noteOn.length()-1);
        if(noteOn == "Note_on_c" && velocity != 0)
        {
          
          startTime = time;
          Note* n = new Note(startTime);
          notes.push_back(n);
        }
        else
        {
          
          //record duration
          duration = time - startTime;
          notes[currentNote]->setDuration(duration); //set duration of last note
          currentNote++;

          //would it be better to keep the original format of recording "start" and "end" times
          //in order to test if input is within a certain range, given the current time?
        }
      }//endif not End_track
      else{end = true;}
    }//endif track==1
  }//end while loop
  for(size_t i=0; i<notes.size(); i++)
  {
    //int d = notes[i]->getDuration();
    cout << "Note: " << i << endl;
    cout << "Start time: " << notes[i]->getStart() << endl;
    cout << "Duration: " << notes[i]->getDuration() << endl;
  }
  
}
*/
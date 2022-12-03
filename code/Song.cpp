#include "Song.h"

Song::Song(string fileName)
{
    //load audio file into music object
    loadSong(fileName);

    //read in file of same name with track data
    string csvFileName = fileName.substr(0,fileName.length()-3);
    csvFileName += "csv";
    cout << "CSV FILE NAME: " << csvFileName << endl;
    loadTracks(csvFileName);
}
int Song::getBPM()
{
    return 160; //temporary definition
}
void Song::loadSong(string fileName)
{
    m_music.openFromFile(fileName);
}
void Song::loadTracks(string fileName)
{
    //assume CSV will contain data for these instruments in this order
    ifstream in(fileName);
    
    Track* sax = new Track();   //MIDI track 1
    Track* piano = new Track(); //MIDI track 2 (track 3 is empty bass cleff data)
    Track* bass = new Track();  //MIDI track 4
    Track* drums = new Track(); //MIDI track 5

    m_tracks.push_back(sax);  //index 0
    m_tracks.push_back(piano);//index 1
    m_tracks.push_back(bass); //index 2
    m_tracks.push_back(drums);//index 3
    
    //once you get the track number, figure out how to turn the track number into vector index
    //start reading in data
    //get the BPM

    string field;
    int startTime;
    int duration;
    bool note = false;
    //bool endTrack = false;

    //store and clear values here to push into vectors
    vector<Note*> notes;
    
    int currentNote = 0;
    int currentTrack = 0;
    while(!in.eof())
    {
        string line;
        getline(in, line);
        stringstream s(line);

        //does the line have note data
        std::size_t found = line.find("Note_on_c");
        if (found!=std::string::npos)
            note = true;
        else
        {
            //does the line terminate the track data
            found = line.find("End_track");
            if (found!=std::string::npos)
            {
                note = false;
                currentTrack++;
            }
            //does the line have tempo data
            found = line.find("Tempo");
            if (found!=std::string::npos)
            {
                string field;
                s >> field >> field >> field;
                int uSecondsBeat;
                s >> uSecondsBeat;
                m_BPM = (60 * 1000 * 1000) / uSecondsBeat;
                cout << "Bpm: " << m_BPM << endl;
            }
            found = line.find("QUARTER_NOTE_TIME");
            if (found!=std::string::npos)
            {
                string field;
                s >> field;
                //int m_quarterTime;
                s >> m_quarterTime;
                
            }
        }
        //does the line terminate the note data
        //found = line.find("End");
        //if (found!=std::string::npos)
        //{
        //    note = false;
        //}

        if(note) //if line contains note data
        {
            //take care of the remaining 5 fields
            //(track), time, Note_on_c, channel, pitch, velocity
            int midiTrack; //midi track doesn't line up with vector index, ignore
            s >> midiTrack;
            s.ignore();
            if(midiTrack == 3){currentTrack--;} //skip this empty track
            
            int time;
            s >> time;
            s.ignore();
        
            string noteOn; //is the note "on"
            string channel; //ignore
            string pitch;  //ignore
            int velocity; 
            //velocity of 0 also means the end of a note

            s >> noteOn >> channel >> pitch >> velocity;
    
            //if start of note, record its start time
            noteOn = noteOn.substr(0,noteOn.length()-1);
            if(noteOn == "Note_on_c" && velocity != 0)
            {
            
                startTime = time;
                //Note* n = new Note(startTime);
                //notes.push_back(n);
            }
            else
            {
                //if note is ending, record duration
                duration = time - startTime; //current time minus start of note
                Note* note;
                if(duration >= m_quarterTime * 2) //Holder/Tapper depends on duration (half note)
                    note = new Holder(startTime); //set start time
                else
                    note = new Tapper(startTime);
                note->setDuration(duration); //set duration
                m_tracks[currentTrack]->addNote(note);
                currentNote++;
            }
        }//endif (note)
    }//end while (!eof)
    
    //output results
    for(size_t i=0; i<m_tracks.size(); i++)
    {
        for(size_t j=0; i<5; i++) //display 5 notes of each track
        {
            cout << "Note: " << i << endl;
            cout << "Start time: " << m_tracks.at(i)->getNote(j)->getStart() << endl;
            cout << "Duration: " << m_tracks.at(i)->getNote(j)->getStart() << endl;

        }
    }
}
Track Song::getTrack(int trackID)
{
    Track t;
    return t; //temp definition
}

void Song::play()
{
    m_music.setLoop(true);
    m_music.play();
}

//unnecessary since I can loop the song with sf::music settings
bool Song::isPlaying()
{
    bool isPlaying = false;
    if(m_music.getStatus() == m_music.Playing)
    {
        isPlaying = true;
    }
    return isPlaying;
}

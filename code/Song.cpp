#include "Song.h"

Song::Song(string fileName)
{
    //load audio file into music object
    //loadSong(fileName);
    loadSong("sound/Untitled Calibration A.ogg");
    //loadSong("sound/Untitled Calibration B.ogg");

    //read in file of same name with track data
    string songName = fileName.substr(0,fileName.length()-3);
    songName = songName.substr(6);
    string csvFileName = "game data/";
    csvFileName += songName;
    csvFileName += "csv";
    //cout << "CSV FILE NAME: " << csvFileName << endl;
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
    //cout << "Entering Song::loadTracks()" << endl;
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

    string field;
    int startTime;
    int duration;
    bool note = false;

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
            note = false;
            //does the line terminate the track data
            found = line.find("End_track");
            if (found!=std::string::npos)
                currentTrack++;
            //does the line have tempo data
            found = line.find("Tempo");
            if (found!=std::string::npos)
            {
                string field;
                s >> field >> field >> field;
                int uSecondsBeat;
                s >> uSecondsBeat;
                m_BPM = (60 * 1000 * 1000) / uSecondsBeat;
                //cout << "Bpm: " << m_BPM << endl;
            }
            found = line.find("QUARTER_NOTE_TIME");
            if (found!=std::string::npos)
            {
                string field;
                s >> field;
                s >> m_quarterTime;
                //cout << "Quarter time: " << m_quarterTime << endl;
            }
        }

        if(note) //if line contains note data
        {
            //take care of the remaining 5 fields
            //(track), time, Note_on_c, channel, pitch, velocity
            
            int midiTrack; //midi track doesn't line up with vector index
            s >> midiTrack;
            //convert to vector index
            if(midiTrack == 1){currentTrack = 0;}
            else if(midiTrack == 2){currentTrack = 1;}
            //else if(midiTrack == 3){currentTrack = 0;}
            else if(midiTrack == 4){currentTrack = 2;}
            else if(midiTrack == 5){currentTrack = 3;}
            s.ignore();
            //if(midiTrack == 4){currentTrack = 3;} //skip this empty track
            
            int time; //time value, may be start or end of note
            s >> time;
            s.ignore();

            string noteOn; //"Note_on_c"
            string channel; //ignore
            string pitch;  //ignore
            int velocity;  //velocity of 0 also means the end of a note

            s >> noteOn >> channel >> pitch >> velocity;
    
            //if start of note, record its start time
            
            noteOn = noteOn.substr(0,noteOn.length()-1); //ignore comma
            if(noteOn == "Note_on_c" && velocity != 0)
                startTime = time;
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
            }
        }//endif (note)
    }//end while (!eof)
    
    //output results
    /*
    for(size_t i=0; i<m_tracks.size(); i++)
    {
        for(size_t j=0; j<5; j++) //display 5 notes of each track
        {
            Note* n = m_tracks.at(i)->getNote(j);
            cout << "Track: " << i << endl;
            cout << "Note: " << j << endl;
            cout << "Start time: " << n->getStart() << endl;
            cout << "Duration: " << n->getDuration() << endl;
        }
    }
    */
   //TEST Track::getNotesInRange()
   //get bass notes in the first beat of the song
   /*
   vector<Note*> bassRange = m_tracks[3]->getNotesInRange(9600, 480);
   cout << "Drum data at 9600" << endl;
   for(size_t i=0; i<bassRange.size(); i++)
    {
        cout << "Note: " << i << endl;
        cout << "Start time: " << bassRange[i]->getStart() << endl;
        cout << "Duration: " << bassRange[i]->getDuration() << endl;
        cout << endl;
    }
    */
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

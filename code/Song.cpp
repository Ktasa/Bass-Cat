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
    return -1; //temporary definition
}
void Song::loadSong(string fileName)
{
    m_music.openFromFile(fileName);
}
void Song::loadTracks(string fileName)
{
    //assume CSV will contain data for these instruments in this order
    ifstream in(fileName);
    /*
    Track* sax = new Track();   //MIDI track 1
    Track* piano = new Track(); //MIDI track 2 (track 3 is empty bass cleff data)
    Track* bass = new Track();  //MIDI track 4
    Track* drums = new Track(); //MIDI track 5

    m_tracks.push_back(sax);  //index 0
    m_tracks.push_back(piano);//index 1
    m_tracks.push_back(bass); //index 2
    m_tracks.push_back(drums);//index 3
    */
    //once you get the track number, figure out how to turn the track number into vector index
    //start reading in data
    //get the BPM


}
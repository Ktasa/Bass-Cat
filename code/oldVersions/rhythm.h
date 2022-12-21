#ifndef RHYTHM_H
#define RHYTHM_H

#include<SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class rhythm
{
public:
    rhythm();
    void count(); //push back vector with time of input in ms
    void printTimes();
    void setValidInput(bool valid);
    bool getValidInput();

private:
    vector<Int64> times; //microseconds
    vector<Int64> intervals;
    Int64 totalTime;
    Clock clock;
    Time dt;
    bool full; //5 second input limit
    bool validInput;
};

rhythm::rhythm()
{
    full = false;
    validInput = true;
}
void rhythm::count()
{
    if(validInput)
    {
        if(totalTime > Int64(5000000))
            full = true;
        if(times.size()==0)
        {
            clock.restart();
            dt = clock.restart();
            times.push_back(dt.asMicroseconds());
            totalTime = dt.asMicroseconds();
        }
        else if(!full && validInput)
        {
            dt = clock.restart();
            totalTime += dt.asMicroseconds();
            times.push_back(totalTime);
            intervals.push_back(dt.asMicroseconds());
        }
    }
    else if(full)
        printTimes();
}

void rhythm::printTimes()
{
    cout << "Times:\n";
    for(Int64 t : times)
    {
        cout << t << endl;
    }
    cout << "Intervals:\n";
    for(Int64 i : intervals)
    {
        cout << i << endl;
    }
}
void rhythm::setValidInput(bool valid)
{
    validInput = valid;
}
bool rhythm::getValidInput()
{
    return validInput;
}


#endif
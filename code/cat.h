#ifndef CAT_H
#define CAT_H

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class cat
{
    public:
    cat();
    cat(string catName);
    int getFrame(); //return 1,2,3,4
    Sprite getSprite(int frameID);
    void loadTextureSprite(string catName);
    void setUpdateTime(float seconds);
    void hitThatBass();
    void setBoost(bool boost);
    int getInputTimeOut();
    int getHitFrame();

    private:
    Sprite sprites[4];
    Texture textures[4];
    int status[4]; //F1, hitThatBass, inputTimeout, hitFrame, etc
    bool player; //is this cat on the left or right of the screen
    bool F1; //animation always alternates between frame 1 and 2 of a nearly identical set
    bool hitBass; //activates action animation
    int inputTimeOut; //two frames of action will always be followed by two frames rest
    int hitFrame; //what is the current frame of the action animation
    float updateTime;
    bool update;
    int frameID;
    bool boost;


};

cat::cat(string catName)
{
    loadTextureSprite(catName);
    frameID = 1;
    F1 = true;
    hitBass = false;
    inputTimeOut = 0;
    hitFrame = 1;
    boost = false;
}
void cat::loadTextureSprite(string catName)
{
    //float scale = 0.5;
    float scale = 1;

    string fileName = "frames/" + catName + " A";
    for(int i=0; i<4; i++)
    {
        fileName += to_string(i+1) + ".png";
        //cout << fileName << endl;
        textures[i].loadFromFile(fileName);
        sprites[i].setTexture(textures[i]);
        sprites[i].setPosition(0, 0);
        sprites[i].setScale(scale, scale);
        fileName = fileName.substr(0,9+catName.length());
    }
}
void cat::setUpdateTime(float seconds)
{
    updateTime = seconds;
}
Sprite cat::getSprite(int frameID)
{
    return sprites[frameID-1];
}
//check update time outside of this function
int cat::getFrame()
{
    if (!hitThatBass || inputTimeOut > 0)
    {
        if (F1)
            frameID = 1;
        else
            frameID = 2;

        if(inputTimeOut > 0){inputTimeOut--;}
    }
    else if(hitThatBass && inputTimeOut==0 && !boost)
    {
        if (F1)
            frameID = 3;
        else
            frameID = 4;

        if (hitFrame == 1)
        {
            //if(bass.getStatus() == bass.Playing)
            //    bass.stop();
            //bass.play();
            
            hitFrame++;
        }
        else
        {
            inputTimeOut = 2;
            hitBass = false;
            hitFrame = 1;
        }
    }
    else if(hitBass && boost)
    {
        if(F1)
            frameID = 1;
        else
            frameID = 4;
    }

    F1 = !F1;
}

void cat::hitThatBass()
{
    hitBass = true;
}
void cat::setBoost(bool boost)
{
    this->boost = boost;
}
int cat::getInputTimeOut()
{
    return inputTimeOut;
}
int cat::getHitFrame()
{
    return hitFrame;
}

#endif
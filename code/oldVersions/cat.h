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
    Sprite getSprite();
    //void setUpdateTime(float seconds); //manage updates independently by passing time to getSprite
    void hitThatBass();
    void setBoost(bool boost);
    int getInputTimeOut();
    int getActionFrame();
    void loadSFX(string filename);

    private:

    int getFrame(); 
    void loadTextureSprite(string catName);
    Sprite sprites[4];
    Texture textures[4];
    int status[4]; //F1, hitThatBass, inputTimeout, hitFrame, etc
    bool player; //is this cat on the left or right of the screen
    bool F1; //animation always alternates between frame 1 and 2 of a nearly identical set
    bool action; //activates action animation
    int inputTimeOut; //two frames of action will always be followed by two frames rest
    int actionFrame; //what is the current frame of the action animation
    //float updateTime;
    //bool update;
    int frameID;
    bool boost;
    SoundBuffer sfxBuffer;
    Sound sfx;
};

cat::cat(string catName)
{
    loadTextureSprite(catName);
    frameID = 1;
    F1 = true;
    action = false;
    inputTimeOut = 0;
    actionFrame = 1;
    boost = false;
    loadSFX("sound/bass sfx O.ogg");
}
void cat::loadTextureSprite(string catName)
{
    //float scale = 0.5;
    float scale = 1;

    string fileName = "graphics/" + catName + " A";
    for(int i=0; i<4; i++)
    {
        fileName += to_string(i+1) + " reduced.png";
        //cout << fileName << endl;
        textures[i].loadFromFile(fileName);
        sprites[i].setTexture(textures[i]);
        sprites[i].setPosition(0, 0);
        sprites[i].setScale(scale, scale);
        fileName = fileName.substr(0,11+catName.length());
    }
}
/*
void cat::setUpdateTime(float seconds)
{
    updateTime = seconds;
}*/
Sprite cat::getSprite()
{
    return sprites[getFrame()-1];
}
//check update time outside of this function
int cat::getFrame()
{
    if (!action || inputTimeOut > 0)
    {
        if (F1)
            frameID = 1;
        else
            frameID = 2;

        if(inputTimeOut > 0){inputTimeOut--;}
    }
    else if(action && inputTimeOut==0 && !boost)
    {
        if (F1)
            frameID = 3;
        else
            frameID = 4;

        if (actionFrame == 1)
        {
            if(sfx.getStatus() == sfx.Playing)
                sfx.stop();
            sfx.play();
            
            actionFrame++;
        }
        else
        {
            inputTimeOut = 2;
            action = false;
            actionFrame = 1;
        }
    }
    else if(action && boost)
    {
        if(F1)
            frameID = 1;
        else
            frameID = 4;
    }
    F1 = !F1;
    return frameID;
}

void cat::hitThatBass()
{
    action = true;
}
void cat::setBoost(bool boost)
{
    this->boost = boost;
}
int cat::getInputTimeOut()
{
    return inputTimeOut;
}
int cat::getActionFrame()
{
    return actionFrame;
}
void cat::loadSFX(string fileName)
{
	sfxBuffer.loadFromFile("sound/bass sfx O.ogg");
	sfx.setBuffer(sfxBuffer);
}

#endif
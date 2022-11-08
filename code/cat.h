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
    //int getSprite(double seconds); //return 1,2,3,4
    Sprite getSprite(int frameID);
    void loadTextureSprite(string catName);

    private:
    Sprite sprites[4];
    Texture textures[4];
    int status[4]; //F1, hitThatBass, inputTimeout, hitFrame, etc
    bool player; //is this cat on the left or right of the screen

};

cat::cat(string catName)
{
    loadTextureSprite(catName);
}
void cat::loadTextureSprite(string catName)
{
    float scale = 0.5;

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
Sprite cat::getSprite(int frameID)
{
    return sprites[frameID-1];
}

#endif
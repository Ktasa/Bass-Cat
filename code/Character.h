#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"

using namespace sf;
using namespace std;

enum CharacterType{CAT, DOG};
enum PlayerID{P1, P2}; //replacing "side" to be more reusable
enum AnimationState
{
    IDLE, //frames 0&1
    ACTION, //frames 2&3
    VICTORY //frames 4&5
}; 

const int CHARACTER_SHEET_WIDTH = 1000;

class Character
{
public:
    Character(PlayerID playerID, CharacterType type, Color color, int BPM);
    void handleInput(); //use in input()
    void updateCharacter(float dtAsSeconds); //use in update()
    Sprite getSprite(); //use in draw()


    //to be used by Battle.h to set scene
    void setState(AnimationState state);
    void setPosition(Vector2f coord);
    void setScale(Vector2f xyScale);
    void setFrameTime(int BPM);
    void setInput(bool isInput);
    void resetTime(); //use to resync animation

private:
    Texture m_charTexture;
    Sprite m_charSprite; 

    CharacterType m_type; //cat or dog
    Color m_color; //line color
    PlayerID m_playerID;

    Vector2f m_position; //screen position

    AnimationState m_state;
    int m_frameID; //current frame
    int m_frameNum; //1 or 2 (all frames come in sets of 2 nearly identical images)
    float m_timePerFrame; //time per frame
    float m_timeUntilUpdate; 

    bool m_isPressed; //is player input live
    bool m_stateChange; //make animations repond to input without delay (bypass timer)
};

#endif
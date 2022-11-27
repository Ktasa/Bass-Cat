#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

enum CharacterType{CAT, DOG};
enum Side{LEFT, RIGHT};

const int CHARACTER_SHEET_WIDTH = 1000;

class Character
{
public:
    Character();
    Character(CharacterType type, Color color, Side side, int BPM);
    void updateCharacter(float dtAsSeconds);
    Sprite getSprite(); //use in draw()

    //to be used by Battle.h to set scene
    void setPosition(Vector2f coord);
    void setFrameTime(int BPM);
    void setInput(bool isInput);
    void resetTime(); //use to resync animation

private:
    Texture m_charTexture;
    Sprite m_charSprite; 

    CharacterType m_type; //cat or dog
    Color m_color; //line color
    Side m_side;

    Vector2f m_position; //screen position

    int m_frameID; //current frame
    int m_frameNum; //1 or 2 (all frames come in sets of 2 nearly identical images)
    float m_timePerFrame; //time per frame
    float m_timeUntilUpdate; 

    bool m_isPressed; //is player input live
};

#endif
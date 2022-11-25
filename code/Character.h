#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

enum CharacterType{CAT, DOG};
enum Side{LEFT, RIGHT};
enum LineColor{BLACK, WHITE};

const int CHARACTER_SHEET_WIDTH = 1000;

class Character
{
public:
    Character(CharacterType type, LineColor color, Side side, int BPM);
    //Sprite getSprite(); //unnecessary? (pass texture to draw by reference)
    void updateCharacter(float dtAsSeconds);

    //to be used by Battle.h to set scene
    void setPosition(Vector2f coord);
    void setFrameTime(int BPM);
    void setInput(bool isInput);
    void resetTime(); //use to resync animation

private:
    Texture m_charTexture;
    VertexArray m_charVA; //holds coords for sprites in sheet
    //Sprite m_sprite; //unnecessary? (pass texture to draw by reference)
        
    //CharacterType m_type; //cat or dog
    //LineColor m_lineColor;
    Side m_side; //left or right

    Vector2f m_position; //screen position

    int m_frameID; //current frame
    int m_frameNum; //1 or 2 (all frames come in sets of 2 nearly identical images)
    float m_timePerFrame; //time per frame
    float m_timeUntilUpdate; 

    bool m_isPressed; //is player input live
};

//window.draw(talkingFace, &faceTexture); draw vetrext array by reference

#endif
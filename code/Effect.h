#ifndef EFFECT_H
#define EFFECT_H

#include <SFML/Graphics.hpp>
#include "Battle.h"
#include "HSV.h"

using namespace std;
using namespace sf;

enum EffectType{MAGIC, DAMAGE};

class Effect
{
public:
    Effect();
    Sprite getSprite();
    void setUp(PlayerID id, EffectType type, int BPM);
    void setFrameTime(int BPM);
    void update(float dtAsSeconds);
    void setActive(bool active);
    bool getIsActive();
    void setRainbow();
    void resetColor();
    //void draw();

private:
    Sprite m_sprite;
    //Vector2f m_position;
    Color m_color; //color of effects will be based on health/accuracy stats?
    EffectType m_type;
    PlayerID m_playerNum;
    float m_frameTime;
    float m_timeUntilUpdate;
    bool m_active;
    bool m_rainbow; //color shifting if using magic attack
};

#endif
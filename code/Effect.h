#ifndef EFFECT_H
#define EFFECT_H

#include <SFML/Graphics.hpp>
#include "Battle.h"

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
    //void draw();

private:
    Sprite m_sprite;
    //Vector2f m_position;
    Color m_color; //color of effects will be based on health/accuracy stats?
    EffectType m_type;
    float m_frameTime;
    float m_timeUntilUpdate;
    bool m_active;
};

#endif
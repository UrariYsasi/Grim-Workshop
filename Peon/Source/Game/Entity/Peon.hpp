#pragma once
#include "Monster.hpp"

class Peon : public Monster
{
public:
    Peon(Game* game, Vector2D position);
    virtual ~Peon();

    virtual void Update();
    virtual void Render();

private:
    // TODO:
    // The hopping code should all be in the MoveAction.
    // However, this doesn't really work because the hop offset
    // is only supposed to be added to the rendering, not the actual
    // position. Restructure entire system?
    double m_hopIndex = 0;
    double m_hopOffset = 0;
    double m_hopAmplitude = 0;
    double m_hopFrequency = 0;
};

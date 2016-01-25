#include "../../PCH.hpp"
#include "Prop.hpp"

class Stockpile : public Prop
{
public:
    Stockpile(Game* game, Vector2D position);
    virtual ~Stockpile();

    virtual void Update();
    virtual void Render();
};

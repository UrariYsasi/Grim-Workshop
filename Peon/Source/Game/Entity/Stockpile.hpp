#include "../../PCH.hpp"
#include "Prop.hpp"
#include "../Item/Inventory.hpp"

class Stockpile : public Prop
{
public:
    Stockpile(Game* game, Vector2D position);
    virtual ~Stockpile();

    Inventory* GetInventory();

    virtual void Update();
    virtual void Render();

private:
    std::unique_ptr<Inventory> m_inventory;
};

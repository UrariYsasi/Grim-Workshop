#include "PCH.hpp"
#include "UIFactory.hpp"
#include "GrimUI.hpp"

namespace grim
{

namespace ui
{

std::unique_ptr<IUserInterface> CreateUIService(grim::Engine* engine)
{
    return std::make_unique<GrimUI>(engine);
}

}

}
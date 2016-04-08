#include "PCH.hpp"
#include "InputFactory.hpp"
#include "SDLInput.hpp"

namespace grim
{

namespace ui
{

std::unique_ptr<IInput> CreateInputService()
{
    return std::make_unique<SDLInput>();
}

}

}
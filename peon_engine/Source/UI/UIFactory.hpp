#pragma once

namespace grim
{

namespace ui
{

std::unique_ptr<IUserInterface> CreateUIService(grim::Engine* engine);

}

}
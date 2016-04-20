#pragma once

namespace grim
{

namespace ui
{

class IUserInterface
{
public:
    virtual bool Initialize() = 0;
    virtual void Terminate() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void RegisterWidget(grim::ui::Widget* widget) = 0;
};

}

}
#pragma once

namespace grim
{

namespace ui
{

class Widget
{
public:
    Widget();
    ~Widget();

    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
};

}

}
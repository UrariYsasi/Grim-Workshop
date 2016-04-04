#pragma once

namespace grim
{

namespace ui
{

class Widget;

class UserInterface
{
public:
    UserInterface();
    ~UserInterface();

    void Update(float deltaTime);
    void Render();

    void RegisterWidget(grim::ui::Widget* widget);

private:
    std::list<grim::ui::Widget*> m_widgets;
};

}

}
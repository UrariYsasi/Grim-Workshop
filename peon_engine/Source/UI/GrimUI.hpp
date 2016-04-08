#pragma once

namespace grim
{

namespace ui
{

class GrimUI : public IUserInterface
{
public:
    GrimUI();
    ~GrimUI();

    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void RegisterWidget(grim::ui::Widget* widget);

private:
    std::list<grim::ui::Widget*> m_widgets;
};

}

}
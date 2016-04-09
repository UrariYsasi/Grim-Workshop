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

    void SetPosition(const glm::vec2& position);
    glm::vec2 GetPosition() const;

protected:
    glm::vec2 m_position;
};

}

}
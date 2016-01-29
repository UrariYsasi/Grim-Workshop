#pragma once

class Monster;

class Action
{
public:
    Action(Monster* owner, const std::string& name);
    virtual ~Action();

    std::string GetName() const;
    bool IsComplete() const;

    virtual void Update(double deltaTime) = 0;
    void Complete();

protected:
    Monster* m_owner;
    std::string m_name;

private:
    bool m_isComplete;
};

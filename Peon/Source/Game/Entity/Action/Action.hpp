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

    /*
        Mark the finished Action as complete so it can be pushed off the stack.

        This function should be called when an Action has been completed
        SUCCESSFULLY. Any behavior that happens when an Action is successfully
        complete should be put into this function.
    */
    virtual void Complete();

protected:
    Monster* m_owner;
    std::string m_name;

private:
    bool m_isComplete;
};

/*
    GrimTimeModule.hpp
    Peon Engine

    Declan Hopkins
    8/2/2016

    A Time Module that uses std::chrono for high resolution timing.
*/

#pragma once

namespace grim
{

class GrimTimeModule : public ITimeModule
{
public:
    GrimTimeModule();
    ~GrimTimeModule();

    /*
        IModule Interface
    */

    virtual bool Initialize() override;
    virtual void Terminate() override;

    /*
        ITimeModule Interface
    */

    virtual double GetTimeSeconds() const override;
    virtual double GetTimeMilliseconds() const override;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
};

}
/*
    ITimeModule.hpp
    Peon Engine

    Declan Hopkins
    9/7/2016

    An Engine module responsible for retreiving and handling time values.
*/

#pragma once

namespace grim
{

namespace utility
{

class ITimeModule : public IModule
{
public:
    /*
        Get the time since the module initialized, in seconds.
    */
    virtual double GetTimeSeconds() const = 0;

    /*
        Get the time since the module initialized, in milliseconds.
    */
    virtual double GetTimeMilliseconds() const = 0;
};

}

}
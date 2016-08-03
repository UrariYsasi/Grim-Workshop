/*
    IModule.hpp
    Peon Engine

    Declan Hopkins
    8/2/2016

    The base Engine module interface. Provides a common interface for initializing and terminating
    modules.
*/

#pragma once

namespace grim
{

class IModule
{
public:
    /*
        Initialize the module.

        Return: Success boolean.
    */
    virtual bool Initialize() = 0;

    /*
        Terminate the module and free any resources owned by it.
    */
    virtual void Terminate() = 0;
};

}
/*
    WindowsFileModule.hpp
    Peon Engine

    Declan Hopkins
    8/6/2016

    A File Module that supports file I/O on the Windows platform. This Module will not compile on
    any other platform.
*/

#pragma once

namespace grim
{

class WindowsFileModule : public IFileModule
{
public:
    WindowsFileModule();
    ~WindowsFileModule();

    /*
        IModule Interface
    */

    virtual bool Initialize() override;
    virtual void Terminate() override;

    /*
        IFileModule Interface
    */
    virtual std::vector<std::string> FindAllFiles(const std::string& directoryPath) override;
};

}
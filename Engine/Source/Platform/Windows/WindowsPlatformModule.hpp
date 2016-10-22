/*
    WindowsPlatformModule.hpp
    Engine

    Declan Hopkins
    9/8/2016

    A Platform Module for Windows. This Module will not compile on any other platform.
*/

#pragma once

namespace grim::platform
{

class WindowsPlatformModule : public IPlatformModule
{
public:
    WindowsPlatformModule();
    ~WindowsPlatformModule();

    /*
        IModule Interface
    */

    virtual bool Initialize() override;
    virtual void Terminate() override;

    /*
        IPlatformModule Interface
    */
    virtual std::vector<std::string> FindAllFiles(const std::string& directoryPath) override;
    virtual std::string FindFileExtension(std::string const& filePath) override;
};

}
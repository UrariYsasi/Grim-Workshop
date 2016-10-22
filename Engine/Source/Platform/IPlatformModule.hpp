/*
    IPlatformModule.hpp
    Engine

    Declan Hopkins
    9/8/2016

    An Engine Module responsible for platform level operations, such as file I/O.
*/

#pragma once

namespace grim::platform
{

class IPlatformModule : public IModule
{
public:
    /*
        Finds all files, recursively, in the given directory path.

        Returns a vector containing the paths to the files that were found.
    */
    virtual std::vector<std::string> FindAllFiles(const std::string& directoryPath) = 0;
    virtual std::string FindFileExtension(std::string const& filePath) = 0;
};

}
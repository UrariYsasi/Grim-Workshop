/*
    IFileModule.hpp
    Engine

    Declan Hopkins
    9/8/2016

    An Engine Module responsible for file I/O. The implementation of this interface is platform 
    dependent.
*/

#pragma once

namespace grim::platform
{

class IFileModule : public IModule
{
public:
    /*
        Finds all files, recursively, in the given directory path.

        Returns a vector containing the paths to the files that were found.
    */
    virtual std::vector<std::string> FindAllFiles(const std::string& directoryPath) = 0;
};

}
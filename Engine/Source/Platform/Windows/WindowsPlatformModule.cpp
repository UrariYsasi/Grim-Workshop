/*
    WindowsPlatformModule.cpp
    Engine

    Declan Hopkins
    9/8/2016
*/

#include "PCH.hpp"
#include "WindowsPlatformModule.hpp"
#include <windows.h>

namespace grim::platform
{

WindowsPlatformModule::WindowsPlatformModule()
{
}

WindowsPlatformModule::~WindowsPlatformModule()
{
}

bool WindowsPlatformModule::Initialize()
{
    LOG() << "Platform Module WindowsPlatformModule initializing...";
    LOG() << "Platform Module WindowsPlatformModule initialized.";
    return true;
}

void WindowsPlatformModule::Terminate()
{
    LOG() << "Platform Module WindowsPlatformModule terminating...";
    LOG() << "Platform Module WindowsPlatformModule terminated.";
}

std::vector<std::string> WindowsPlatformModule::FindAllFiles(const std::string& directoryPath)
{
    std::vector<std::string> filePaths;
    std::string searchPath = directoryPath + "*";

    WIN32_FIND_DATA fd;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                if ((strcmp(fd.cFileName, ".") != 0) && (strcmp(fd.cFileName, "..") != 0))
                {
                    std::vector<std::string> moreFilePaths = FindAllFiles(directoryPath + fd.cFileName + "/");
                    filePaths.insert(filePaths.end(), moreFilePaths.begin(), moreFilePaths.end());
                }
            }
            else
            {
                filePaths.push_back(directoryPath + fd.cFileName);
            }
        } while (FindNextFile(hFind, &fd));
        FindClose(hFind);
    }

    return filePaths;
}

std::string WindowsPlatformModule::FindFileExtension(std::string const& filePath)
{
    std::string extension;
    if (filePath.find_last_of(".") != std::string::npos)
    {
        extension = filePath.substr(filePath.find_last_of(".") + 1);
    }

    return extension;
}

}
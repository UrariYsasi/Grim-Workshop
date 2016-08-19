/*
    WindowsFileModule.cpp
    Peon Engine

    Declan Hopkins
    8/6/2016
*/

#include "PCH.hpp"
#include "WindowsFileModule.hpp"
#include <windows.h>

namespace grim
{

WindowsFileModule::WindowsFileModule()
{
}

WindowsFileModule::~WindowsFileModule()
{
}

bool WindowsFileModule::Initialize()
{
    LOG() << "File Module WindowsFileModule initializing...";
    LOG() << "File Module WindowsFileModule initialized.";
    return true;
}

void WindowsFileModule::Terminate()
{
    LOG() << "File Module WindowsFileModule terminating...";
    LOG() << "File Module WindowsFileModule terminated.";
}

std::vector<std::string> WindowsFileModule::FindAllFiles(const std::string& directoryPath)
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

}
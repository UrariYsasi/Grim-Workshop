/*
    Importer.cpp
    Peon Engine

    Declan Hopkins
    10/11/2016
*/

#include "PCH.hpp"
#include "Importer.hpp"

namespace grim::assets
{

Importer::Importer(IAssetModule* const assetModule) :
    m_assetModule(assetModule)
{
}

Importer::~Importer()
{
}

std::string Importer::CreateId(std::string const& filePath) const
{
    std::string id = filePath;
    std::string assetDirectoryPath = ASSET_DIRECTORY_PATH;

    // Remove the directory path
    std::string::size_type pos = id.find(assetDirectoryPath);
    if (pos != std::string::npos)
    {
        id.erase(pos, assetDirectoryPath.length());
    }

    // Change slashes to dots
    std::replace(id.begin(), id.end(), '/', '.');

    // Remove the file extension
    std::string::size_type extensionPos = id.find_last_of(".");
    if (extensionPos != std::string::npos)
    {
        id = id.substr(0, extensionPos);
    }

    return id;
}

}
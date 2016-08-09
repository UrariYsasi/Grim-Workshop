/*
    AssetImporter.cpp
    Peon Engine

    Declan Hopkins
    8/7/2016
*/

#include "PCH.hpp"
#include "AssetImporter.hpp"

namespace grim
{

AssetImporter::AssetImporter(IAssetModule* const assetModule, IFileModule* const fileModule) :
    m_assetModule(assetModule),
    m_fileModule(fileModule)
{
}

AssetImporter::~AssetImporter()
{
}

}
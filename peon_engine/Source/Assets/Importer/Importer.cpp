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

}
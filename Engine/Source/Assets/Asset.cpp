/*
    Asset.cpp
    Engine

    Declan Hopkins
    10/6/2016
*/

#include "PCH.hpp"
#include "Asset.hpp"

namespace grim::assets
{

Asset::Asset(const std::string& id) :
    m_id(id)
{
}

Asset::~Asset()
{
}

std::string Asset::GetId()
{
    return m_id;
}

}
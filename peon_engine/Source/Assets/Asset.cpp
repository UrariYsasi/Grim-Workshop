#include "PCH.hpp"
#include "Asset.hpp"

namespace grim::asset
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
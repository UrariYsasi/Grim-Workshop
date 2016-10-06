/*
    Asset.hpp
    Engine

    Declan Hopkins
    10/6/2016

    The base class for a game asset.
*/

#pragma once

namespace grim::asset
{

class Asset
{
public:
    Asset(const std::string& id);
    ~Asset();

    std::string GetId();

private:
    const std::string m_id;
};

}
/*
    Metadata.cpp
    Engine

    Declan Hopkins
    10/23/2016
*/

#include "PCH.hpp"
#include "Metadata.hpp"

namespace grim::utility
{

Metadata::Metadata()
{
}

Metadata::~Metadata()
{
}

void Metadata::Store(std::string const& section, std::string const& key, std::string const& value)
{
    m_data[section][key] = value;
}

std::string Metadata::ToString() const
{
    std::string returnString("");
    
    for (auto section : m_data)
    {
        returnString += "\n";
        returnString += "[" + section.first + "]";

        for (auto key : section.second)
        {
            returnString += "\n";
            returnString += key.first + " = " + key.second;
        }
    }

    return returnString;
}

}
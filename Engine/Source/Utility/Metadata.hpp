/*
    Metadata.hpp
    Engine

    Declan Hopkins
    10/23/2016

    A container that holds data used for serialization, deserialization, or other purposes. Metadata
    objects are most commonly created from a file.
*/

#pragma once

namespace grim::utility
{

class Metadata
{
public:
    Metadata();
    ~Metadata();

    void Store(std::string const& section, std::string const& key, std::string const& value);
    std::string ToString() const;

private:
    std::map<std::string, std::map<std::string, std::string>> m_data;
};

}
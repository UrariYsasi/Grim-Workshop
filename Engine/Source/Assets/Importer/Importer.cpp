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

utility::Metadata Importer::ParseMetadata(std::string const& filePath) const
{
    utility::Metadata metadata;

    std::ifstream fileStream(filePath);
    if (!fileStream.is_open())
    {
        LOG_ERROR() << "Failed to read file at " << filePath << "!";
    }

    ParseState state = ParseState::None;
    std::string readBuffer("");
    std::string section("");
    std::string key("");
    std::string value("");

    std::vector<char> fileData((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
    for (char c : fileData)
    {
        if (c == ' ' || c == '\n' || c == '\r\n')
        {
            continue;
        }

        if (c == '[')
        {
            if (state == ParseState::None)
            {
                section.clear();
                state = ParseState::ParsingSection;
            }
            else
            {
                LOG_ERROR() << "Unexpected character \'" << c << "\' while parsing " << filePath;
                return metadata;
            }

            continue;
        }

        if (c == ']')
        {
            if (state == ParseState::ParsingSection)
            {
                section = readBuffer;
                readBuffer.clear();
                state = ParseState::None;
            }
            else
            {
                LOG_ERROR() << "Unexpected character \'" << c << "\' while parsing " << filePath;
                return metadata;
            }

            continue;
        }

        if (c == '=')
        {
            if (state == ParseState::ParsingKey)
            {
                key = readBuffer;
                readBuffer.clear();
                value.clear();
                state = ParseState::ParsingValue;
            }
            else
            {
                LOG_ERROR() << "Unexpected character \'" << c << "\' while parsing " << filePath;
                return metadata;
            }

            continue;
        }

        if (c == ';')
        {
            if (state == ParseState::ParsingValue)
            {
                value = readBuffer;
                readBuffer.clear();
                metadata.Store(section, key, value);
                state = ParseState::None;
            }
            else
            {
                LOG_ERROR() << "Unexpected character \'" << c << "\' while parsing " << filePath;
                return metadata;
            }

            continue;
        }

        if (state == ParseState::ParsingSection || state == ParseState::ParsingValue)
        {
            readBuffer += c;
            continue;
        }

        if (state != ParseState::ParsingKey)
        {
            key.clear();
            state = ParseState::ParsingKey;
        }

        readBuffer += c;
    }

    fileStream.close();

    return metadata;
}

}
/*
    GrimTimeModule.cpp
    Peon Engine

    Declan Hopkins
    8/2/2016
*/

#include "PCH.hpp"
#include "GrimTimeModule.hpp"

namespace grim
{

GrimTimeModule::GrimTimeModule() :
    m_startTimePoint()
{
}

GrimTimeModule::~GrimTimeModule()
{
}

bool GrimTimeModule::Initialize()
{
    m_startTimePoint = std::chrono::high_resolution_clock::now();

    std::cout << "Time Module GrimTimeModule initialized." << std::endl;
    return true;
}

void GrimTimeModule::Terminate()
{
    std::cout << "Time Module GrimTimeModule terminated." << std::endl;
}

double GrimTimeModule::GetTimeSeconds() const
{
    return GetTimeMilliseconds() / 1000.0;
}

double GrimTimeModule::GetTimeMilliseconds() const
{
    auto timeNowPoint = std::chrono::high_resolution_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(timeNowPoint - m_startTimePoint);

    return static_cast<double>(difference.count());
}

}
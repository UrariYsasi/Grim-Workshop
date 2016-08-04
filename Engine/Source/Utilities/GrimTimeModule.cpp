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
    LOG() << "Time Module GrimTimeModule initializing...";

    m_startTimePoint = std::chrono::high_resolution_clock::now();

    LOG() << "Time Module GrimTimeModule initialized.";
    return true;
}

void GrimTimeModule::Terminate()
{
    LOG() << "Time Module GrimTimeModule terminating...";
    LOG() << "Time Module GrimTimeModule terminated.";
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
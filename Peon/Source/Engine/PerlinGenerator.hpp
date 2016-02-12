#pragma once

class PerlinGenerator
{
public:
    PerlinGenerator();
    ~PerlinGenerator();

    double GeneratePerlin2D(const double& x, const double& y);

private:
    double InterpolatedNoise(const double& x, const double& y);
    double SmoothNoise(const int& x, const int& y);
    double Interpolate(const double& a, const double& b, const double& w);
    double Noise(const int& x, const int& y);

private:
    int offsetX = 20;
    int offsetY = 0;
    double persistence = .50;
    double octaves = 6;
    double scale = 30;
};
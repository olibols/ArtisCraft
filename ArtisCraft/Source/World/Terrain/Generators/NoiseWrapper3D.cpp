#include "NoiseWrapper3D.h"
#include <cmath>

NoiseWrapper3D::NoiseWrapper3D(int seed)
{
	m_noiseGen.SetSeed(seed);

	NoiseParams3D params;

	SetParams(params);
}

void NoiseWrapper3D::SetParams(NoiseParams3D & params)
{
	m_params = params;

	m_noiseGen.SetNoiseType(m_params.NoiseType);
	m_noiseGen.SetFractalType(m_params.FractalType);
	m_noiseGen.SetFrequency(m_params.Frequency);
	m_noiseGen.SetFractalOctaves(m_params.Octaves);
	m_noiseGen.SetFractalLacunarity(m_params.Lacunarity);
	m_noiseGen.SetFractalGain(m_params.Gain);
}

void NoiseWrapper3D::SetSeed(int seed)
{
	m_noiseGen.SetSeed(seed);
}

double NoiseWrapper3D::GetHeight(int x, int y, int z)
{
	return ((m_noiseGen.GetNoise(x, y, z) + 1.0) * m_params.Amplitude) + m_params.Offset;
}

double NoiseWrapper3D::GetHeight1_0(int x, int y, int z)
{
	return m_noiseGen.GetNoise(x, y, z);
}

double NoiseWrapper3D::GetRidgedHeight(int x, int y, int z)
{
	return (abs(m_noiseGen.GetNoise(x, y, z)));
}
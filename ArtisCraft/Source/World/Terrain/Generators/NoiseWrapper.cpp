#include "NoiseWrapper.h"
#include <cmath>

NoiseWrapper::NoiseWrapper(int seed)
{
	m_noiseGen.SetSeed(seed);

	NoiseParams params;

	SetParams(params);
}

void NoiseWrapper::SetParams(NoiseParams & params)
{
	m_params = params;

	m_noiseGen.SetNoiseType(m_params.NoiseType);
	m_noiseGen.SetFractalType(m_params.FractalType);
	m_noiseGen.SetFrequency(m_params.Frequency);
	m_noiseGen.SetFractalOctaves(m_params.Octaves);
	m_noiseGen.SetFractalLacunarity(m_params.Lacunarity);
	m_noiseGen.SetFractalGain(m_params.Gain);
}

double NoiseWrapper::GetHeight(int x, int z)
{
	return ((m_noiseGen.GetNoise(x, z) + 1) * m_params.Amplitude) + m_params.Offset;
}

double NoiseWrapper::GetHeight1_0(int x, int z)
{
	return ((m_noiseGen.GetNoise(x, z)) * m_params.Amplitude);
}

double NoiseWrapper::GetRidgedHeight(int x, int z)
{
	return (abs(m_noiseGen.GetNoise(x, z)) * m_params.Amplitude) + m_params.Offset;
}
#include "NoiseWrapper.h"
#include <cmath>

NoiseWrapper::NoiseWrapper(int seed)
{
	_noiseGen.SetSeed(seed);

	NoiseParams params;

	SetParams(params);
}

void NoiseWrapper::SetParams(NoiseParams & params)
{
	_params = params;

	_noiseGen.SetNoiseType(_params.NoiseType);
	_noiseGen.SetFractalType(_params.FractalType);
	_noiseGen.SetFrequency(_params.Frequency);
	_noiseGen.SetFractalOctaves(_params.Octaves);
	_noiseGen.SetFractalLacunarity(_params.Lacunarity);
	_noiseGen.SetFractalGain(_params.Gain);
}

double NoiseWrapper::GetHeight(int x, int z)
{
	return ((_noiseGen.GetNoise(x, z) + 1) * _params.Amplitude) + _params.Offset;
}

double NoiseWrapper::GetHeight1_0(int x, int z)
{
	return ((_noiseGen.GetNoise(x, z)) * _params.Amplitude);
}

double NoiseWrapper::GetRidgedHeight(int x, int z)
{
	return (abs(_noiseGen.GetNoise(x, z)) * _params.Amplitude) + _params.Offset;
}

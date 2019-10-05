#pragma once
#include "FastNoise.h"

struct NoiseParams {
	FastNoise::NoiseType NoiseType = FastNoise::PerlinFractal;
	FastNoise::FractalType FractalType = FastNoise::FBM;

	float Frequency = 0.003;
	float Octaves = 5;
	float Lacunarity = 2;
	float Gain = 0.3;
	float Amplitude = 160;
	float Offset = -80;
};

class NoiseWrapper {
public:
	NoiseWrapper(int seed);

	void SetParams(NoiseParams& params);

	double GetHeight(int x, int z);

private:
	int _seed;

	FastNoise _noiseGen;

	NoiseParams _params;

};
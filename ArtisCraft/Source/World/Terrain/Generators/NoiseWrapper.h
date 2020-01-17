#pragma once
#include "FastNoise.h"

struct NoiseParams {
	FastNoise::NoiseType NoiseType = FastNoise::PerlinFractal;
	FastNoise::FractalType FractalType = FastNoise::FBM;

	float Frequency = 0.007;
	float Octaves = 3;
	float Lacunarity = 1;
	float Gain = 0.1;
	float Amplitude = 20;
	float Offset = 5;
};

class NoiseWrapper {
public:
	NoiseWrapper(int seed);

	void SetParams(NoiseParams& params);

	double GetHeight(int x, int z);
	double GetHeight1_0(int x, int z);
	double GetRidgedHeight(int x, int z);

	inline FastNoise& GetNoise() { return m_noiseGen; };

	inline void SetAmplitude(int amp) { m_params.Amplitude = amp; };
	inline void SetOffset(int off) { m_params.Offset = off; };

private:
	int m_seed;

	FastNoise m_noiseGen;

	NoiseParams m_params;
};
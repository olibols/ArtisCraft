#pragma once
#include "FastNoise.h"

struct NoiseParams {
	FastNoise::NoiseType NoiseType = FastNoise::PerlinFractal;
	FastNoise::FractalType FractalType = FastNoise::FBM;

	float Frequency = 0.006;
	float Octaves = 5;
	float Lacunarity = 2;
	float Gain = 0.3;
	float Amplitude = 130;
	float Offset = -60;
};

class NoiseWrapper {
public:
	NoiseWrapper(int seed);

	void SetParams(NoiseParams& params);

	double GetHeight(int x, int z);
	double GetHeight1_0(int x, int z);
	double GetRidgedHeight(int x, int z);

	inline FastNoise& GetNoise() { return _noiseGen; };

	inline void SetAmplitude(int amp) { _params.Amplitude = amp; };
	inline void SetOffset(int off) { _params.Offset = off; };

private:
	int _seed;

	FastNoise _noiseGen;

	NoiseParams _params;

};
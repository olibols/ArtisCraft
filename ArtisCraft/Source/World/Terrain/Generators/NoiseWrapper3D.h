#pragma once
#include "FastNoise.h"

struct NoiseParams3D {
	FastNoise::NoiseType NoiseType = FastNoise::NoiseType::Simplex;
	FastNoise::FractalType FractalType = FastNoise::FractalType::FBM;

	float Frequency = 0.3;
	float Octaves = 3;
	float Lacunarity = 2.0;
	float Gain = 0.5;
	float Amplitude = 20;
	float Offset = 5;
};

class NoiseWrapper3D {
public:
	NoiseWrapper3D(int seed);

	void SetParams(NoiseParams3D& params);
	void SetSeed(int seed);

	double GetHeight(int x, int y, int z);
	double GetHeight1_0(int x, int y, int z);
	double GetRidgedHeight(int x, int y, int z);

	inline FastNoise& GetNoise() { return m_noiseGen; };

	inline void SetAmplitude(int amp) { m_params.Amplitude = amp; };
	inline void SetOffset(int off) { m_params.Offset = off; };

private:
	int m_seed;

	FastNoise m_noiseGen;

	NoiseParams3D m_params;
};
#pragma once

struct NoiseParameters {
	int octaves;
	int amplitude;
	int smoothness;
	int offset;

	double roughness;
};

class NoiseGenerator {
public:
	NoiseGenerator(int seed);

	double getHeight(int x, int z, int chunkX, int chunkZ);

	void setNoiseParameters(NoiseParameters& parameters);

private:
	double getNoise(int n);
	double getNoise(double x, double z);

	double interpolate(double a, double b, double c);

	double noise(double x, double z);

	NoiseParameters _noiseParameters;

	int _seed;
};
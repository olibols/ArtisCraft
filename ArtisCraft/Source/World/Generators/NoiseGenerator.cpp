#include "NoiseGenerator.h"
#include "../Constants.h"
#include <cmath>

NoiseGenerator::NoiseGenerator(int seed) : _seed(seed) {
	_noiseParameters.amplitude = 100;
	_noiseParameters.offset = -20;
	_noiseParameters.octaves = 9;
	_noiseParameters.roughness = 0.50;
	_noiseParameters.smoothness = 195;
}

double NoiseGenerator::getHeight(int x, int z, int chunkX, int chunkZ)
{
	int worldX = (x + (chunkX * CHUNK_SIZE));
	int worldZ = (z + (chunkZ * CHUNK_SIZE));

	double finalHeight = 0.0;

	for (int octave = 0; octave < _noiseParameters.octaves - 1; octave++) {
		double frequency = pow(2.0, octave);
		double amplitude = pow(_noiseParameters.roughness, octave);

		finalHeight += noise(
			((double)worldX) * frequency / _noiseParameters.smoothness,
			((double)worldZ) * frequency / _noiseParameters.smoothness) * amplitude;

		double val = (((finalHeight / 2.1) + 1.2) * _noiseParameters.amplitude) + _noiseParameters.offset;

		return val;
	}
}

void NoiseGenerator::setNoiseParameters(NoiseParameters & parameters)
{
	_noiseParameters = parameters;
}

double NoiseGenerator::getNoise(int n) // This was taken from the libnoise example at http://libnoise.sourceforge.net/noisegen/ , an explanation can be found there.
{
	n += _seed;

	n = (n >> 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double)nn / 1073741824.0);
}

double NoiseGenerator::getNoise(double x, double z)
{
	return getNoise(x + z * 64);
}

double NoiseGenerator::interpolate(double a, double b, double c) // Some standard Biliniar Interpolation function;
{
	double mu2 = (1 - std::cos(c * 3.14)) / 2;
	return (a * (1 - mu2) + b * mu2);
}

double NoiseGenerator::noise(double x, double z) // This function is kind of hard to explain, it just gets the noise at the parts surrounding x and z and interpolates them to make the S M O O T H
{
	double floorX = (double)((int)x);
	double floorZ = (double)((int)z);

	double  s = 0.0,
            t = 0.0,
            u = 0.0,
            v = 0.0;

	s = getNoise(floorX, floorZ);
	t = getNoise(floorX + 1, floorZ);
	u = getNoise(floorX, floorZ + 1);
	v = getNoise(floorX + 1, floorZ + 1);

	auto rec1 = interpolate(s, t, x - floorX);
	auto rec2 = interpolate(u, v, x - floorX);
	auto rec3 = interpolate(rec1, rec2, z - floorZ);
	return rec3;

}


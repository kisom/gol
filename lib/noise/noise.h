#ifndef __NOISE_H
#define __NOISE_H


namespace noise {


class NoiseGenerator {
public:
	NoiseGenerator();
	NoiseGenerator(bool standard);
	double sample(double x, double y, double z);
	void randomise();
private:
	void	randomPermutation();
	uint8_t	p[512];
	uint8_t	perm[256];
};


} // namespace noise
#endif // __NOISE_H

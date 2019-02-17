#ifndef __NOISE_H
#define __NOISE_H


class NoiseGenerator {
public:
	NoiseGenerator();
	double sample(double x, double y, double z);
	void randomise();
private:
	uint8_t	p[512];
	uint8_t	perm[256];
};


#endif // __NOISE_H

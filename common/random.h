#ifndef __CPP_ALGO_RANDOM_H
#define __CPP_ALGO_RANDOM_H

#include <random>
namespace tools {

class Random {
public:
	static double random(double a = 0.0, double b = 1.0);
	static int random(int a, int b);

private:
	static std::mt19937 SeededEng() {
		static std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
		return std::mt19937(seed);
	}

	static std::mt19937 eng;
	static std::random_device r;
};

} // namespace tools

#endif // __CPP_ALGO_RANDOM_H
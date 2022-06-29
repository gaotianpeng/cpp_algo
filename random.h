#ifndef __CPP_ALGO_RANDOM_H
#define __CPP_ALGO_RANDOM_H

#include <random>

class Random {
public:
	auto operator()(double a = 0.0, double b = 1.0) {
		std::uniform_real_distribution<double> dist(a, b);
		auto ret = dist(eng);
		while (ret == 1.0) {
			ret = dist(eng);
		}
		return ret;
	}

private:
	std::mt19937 SeededEng() {
		std::random_device r;
		std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
		return std::mt19937(seed);
	}

	std::mt19937 eng = SeededEng();
};

#endif // __CPP_ALGO_RANDOM_H
#ifndef __CPP_ALGO_RANDOM_H
#define __CPP_ALGO_RANDOM_H

#include <random>
namespace tools {

class Random {
public:
	static auto random(double a = 0.0, double b = 1.0) {
		std::uniform_real_distribution<double> dist(a, b);
		auto ret = dist(eng);
		while (ret == 1.0) {
			ret = dist(eng);
		}
		return ret;
	}

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
#include "common.h"
#include "random.h"

namespace tools {

int RandomVal(int min_val, int max_val) {
	return min_val + (int)(Random::random()*max_val - min_val);
}


} // namespace tools
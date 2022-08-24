#include "random.h"

namespace tools {


std::random_device Random::r;
std::mt19937 Random::eng = SeededEng();
} // namespace tools
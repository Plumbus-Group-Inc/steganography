#ifndef __INCLUDE_COMMON_HH__
#define __INCLUDE_COMMON_HH__

#include <cstdint>
#include <vector>

namespace mmht {

struct Data final {
  std::size_t freq = 0;
  std::vector<float> input;
};

}

#endif // __INCLUDE_COMMON_HH__

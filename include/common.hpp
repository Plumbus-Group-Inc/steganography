#ifndef __INCLUDE_COMMON_HH__
#define __INCLUDE_COMMON_HH__

#include <cstdint>
#include <vector>

namespace mmht {

struct Data final {
  std::size_t freq = 0;
  std::size_t channels = 0;
  std::size_t depth = 0;

  std::vector<uint32_t> left;
  std::vector<uint32_t> right;
};

}

#endif // __INCLUDE_COMMON_HH__

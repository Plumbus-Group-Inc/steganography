#ifndef __INCLUDE_ABSTRACT_HH__
#define __INCLUDE_ABSTRACT_HH__

#include <cstdint>
#include <vector>

namespace sgg {

class IEncoder {
public:
  virtual std::vector<std::uint32_t>
  encode(const std::vector<std::uint32_t> &input,
         const std::vector<std::uint8_t> &data) = 0;

  virtual ~IEncoder() = default;
};

class IDecoder {
public:
  virtual std::vector<std::uint8_t>
  decode(const std::vector<std::uint32_t> &input) = 0;

  virtual ~IDecoder() = default;
};

} // namespace sgg

#endif // __INCLUDE_ABSTRACT_HH__

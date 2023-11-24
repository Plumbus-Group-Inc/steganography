#ifndef __INCLUDE_ABSTRACT_HH__
#define __INCLUDE_ABSTRACT_HH__

#include <span>

#include "common.hpp"

namespace mmht {

class IEncoder {
public:
  virtual Data encode(const Data &input, std::span<std::byte> data) = 0;

  virtual ~IEncoder() = default;
};

class IDecoder {
public:
  virtual Data decode(const Data &input) = 0;

  virtual ~IDecoder() = default;
};

} // namespace mmht

#endif // __INCLUDE_ABSTRACT_HH__

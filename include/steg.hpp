#ifndef __INCLUDE_STEG_HH__
#define __INCLUDE_STEG_HH__

#include <memory>
#include <span>
#include <vector>

#include "common.hpp"

namespace mmht {

class IEncoder {
public:
  virtual Data encode(const Data &input, std::span<std::uint8_t> data) = 0;
  virtual ~IEncoder() = default;
};

std::unique_ptr<IEncoder> CreateLSBEncoder();

class IDecoder {
public:
  virtual std::vector<std::uint8_t> decode(const Data &input) = 0;
  virtual ~IDecoder() = default;
};

std::unique_ptr<IDecoder> CreateLSBDecoder();

} // namespace mmht

#endif // __INCLUDE_STEG_HH__

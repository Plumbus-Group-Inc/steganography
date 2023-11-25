#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>

#include "steg.hpp"

namespace mmht {

class LSBEncoder final : public IEncoder {
public:
  Data encode(const Data &input, std::span<std::uint8_t> data) override;
};

class LSBDecoder final : public IDecoder {
public:
  std::vector<std::uint8_t> decode(const Data &input) override;
};

std::unique_ptr<IEncoder> CreateLSBEncoder() {
  return std::make_unique<LSBEncoder>();
}

std::unique_ptr<IDecoder> CreateLSBDecoder() {
  return std::make_unique<LSBDecoder>();
}

struct Raw {
  std::uint32_t mantissa : 23;
  std::uint32_t exponent : 8;
  std::uint32_t sign : 1;
};

union Holder {
  std::uint32_t f;
  Raw raw;
};

static std::uint32_t writeLastByte(std::uint32_t in, std::uint8_t byte) {
  in &= ((~0u) << 8);
  in |= static_cast<std::uint32_t>(byte & 0xFFU);
  return in;
}

Data LSBEncoder::encode(const Data &input, std::span<std::uint8_t> data) {
  if (input.left.size() <= data.size()) {
    throw std::runtime_error{"WAV file is too small to hide message"};
  }

  auto output = input;

  union {
    std::size_t val;
    std::uint8_t raw[4];
  } msgSize;
  msgSize.val = data.size();

  std::size_t i = 0;
  for (; i < 4; ++i) {
    output.left[i] = writeLastByte(output.left[i], msgSize.raw[i]);
  }

  for (std::size_t size = data.size() + 4; i < size; ++i) {
    output.left[i] = writeLastByte(output.left[i], data[i - 4]);
  }

  for (std::size_t size = input.left.size(); i < size; ++i) {
    output.left[i] = writeLastByte(output.left[i], 0);
  }

  return output;
}

static std::uint8_t getLastByte(std::uint32_t in) {
  return std::uint8_t(in & 0xFFU);
}

std::vector<std::uint8_t> LSBDecoder::decode(const Data &input) {
  std::vector<std::uint8_t> output{};

  union {
    std::size_t val;
    std::uint8_t raw[4];
  } msgSize{0};

  for (size_t i = 0; i < 4; ++i) {
    msgSize.raw[i] = getLastByte(input.left[i]);
  }

  auto beg = input.left.begin() + 4;
  std::transform(beg, beg + msgSize.val, std::back_inserter(output),
                 [](const auto &sample) { return getLastByte(sample); });

  return output;
}

} // namespace mmht
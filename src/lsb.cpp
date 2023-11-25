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
  float f;
  Raw raw;
};

Data LSBEncoder::encode(const Data &input, std::span<std::uint8_t> data) {
  if (input.left.size() < data.size()) {
    throw std::runtime_error{"WAV file is too small to hide message"};
  }

  auto output = input;

  std::size_t i = 0;
  for (std::size_t size = data.size(); i < size; ++i) {
    Holder holder{};
    holder.f = output.left[i];
    holder.raw.mantissa &= ((~0u) << 8);
    holder.raw.mantissa |= static_cast<std::uint32_t>(data[i] & 0xFFU);
    output.left[i] = holder.f;
  }

  for (std::size_t size = input.left.size(); i < size; ++i) {
    Holder holder{};
    holder.f = output.left[i];
    holder.raw.mantissa &= ((~0u) << 8);
    output.left[i] = holder.f;
  }

  return output;
}

std::vector<std::uint8_t> LSBDecoder::decode(const Data &input) {
  std::vector<std::uint8_t> output{};

  std::transform(input.left.begin(), input.right.end(),
                 std::back_inserter(output), [](const auto &sample) {
                   Holder holder{};
                   holder.f = sample;
                   return std::uint8_t(holder.raw.mantissa & 0xFFU);
                 });

  return output;
}

} // namespace mmht
#ifndef __INCLUDE_WAV_HH__
#define __INCLUDE_WAV_HH__

#include <cstdint>
#include <filesystem>
#include <vector>

namespace sgg {

namespace fs = std::filesystem;

class WAV {};

class WAVLoader {
  WAVLoader(const fs::path &input);
  std::uint64_t getFreq();
  std::vector<std::uint32_t> getData();
};

}

#endif // __INCLUDE_WAV_HH__

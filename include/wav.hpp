#ifndef __INCLUDE_WAV_HH__
#define __INCLUDE_WAV_HH__

#include <cstdint>
#include <filesystem>
#include <vector>

#include "common.hpp"

namespace mmht {

namespace fs = std::filesystem;

class WAVLoader {
  WAVLoader(const fs::path &input);
  Data getData();
};

class WAVSaver {
  void save(const fs::path &path, const Data &data);
};

}

#endif // __INCLUDE_WAV_HH__

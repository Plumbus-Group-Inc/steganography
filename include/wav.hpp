#ifndef __INCLUDE_WAV_HH__
#define __INCLUDE_WAV_HH__

#include <cstdint>
#include <filesystem>
#include <memory>
#include <vector>

#include "common.hpp"

namespace mmht {

namespace fs = std::filesystem;

class ILoader {
public:
  virtual ~ILoader() = default;
  virtual Data loadData() = 0;
};

class ISaver {
public:
  virtual ~ISaver() = default;
  virtual void saveData(Data const &data) = 0;
};

std::unique_ptr<ILoader> CreateWAVLoader(fs::path const &path);
std::unique_ptr<ISaver> CreateWAVSaver(fs::path const &path);

} // namespace mmht

#endif // __INCLUDE_WAV_HH__

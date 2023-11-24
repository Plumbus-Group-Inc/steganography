#ifndef __INCLUDE_WAV_HH__
#define __INCLUDE_WAV_HH__

#include <cstdint>
#include <filesystem>
#include <vector>
#include <memory>

#include "common.hpp"

namespace mmht {

namespace fs = std::filesystem;

class ILoader {
public:
    virtual ~ILoader() = 0;
    virtual Data loadData() = 0;
};

class ISaver {
public:
    virtual ~ISaver() = 0;
    virtual void saveData(Data const& data) = 0;
};

std::unique_ptr<ILoader> CreateWAVLoader(fs::path const& path);
std::unique_ptr<ISaver> CreateWAVSaver(fs::path const& path);

}

#endif // __INCLUDE_WAV_HH__

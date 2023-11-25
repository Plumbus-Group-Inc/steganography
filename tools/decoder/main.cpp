#include <cstddef>
#include <filesystem>
#include <fstream>
#include <ostream>
#include <vector>

#include <CLI/CLI.hpp>
#include <CLI/Validators.hpp>

#include "steg.hpp"
#include "wav.hpp"

namespace fs = std::filesystem;

int main(int argc, char **argv) {
  CLI::App app{"Encoder"};

  fs::path inputPath{};
  app.add_option("-i, --input", inputPath, "<input.wav>")
      ->check(CLI::ExistingPath)
      ->required();

  fs::path outMsgPath{};
  app.add_option("-o, --output", outMsgPath, "path to output message")
      ->required();

  CLI11_PARSE(app, argc, argv);

  auto loader = mmht::CreateWAVLoader(inputPath);
  auto input = loader->loadData();

  auto decoder = mmht::CreateLSBDecoder();
  auto msg = decoder->decode(input);

  std::ofstream outMsgStream{outMsgPath, std::ios::out | std::ios::binary};
  outMsgStream.write(reinterpret_cast<const char *>(msg.data()), msg.size());

  return 0;
}

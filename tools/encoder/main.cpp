#include <cstddef>
#include <filesystem>
#include <fstream>
#include <vector>

#include <CLI/CLI.hpp>
#include <CLI/Validators.hpp>

#include "steg.hpp"
#include "wav.hpp"

namespace fs = std::filesystem;

static std::vector<std::uint8_t> readBinaryFile(const fs::path &filename) {
  // binary mode is only for switching off newline translation
  std::ifstream file(filename, std::ios::binary);
  file.unsetf(std::ios::skipws);

  std::streampos file_size;
  file.seekg(0, std::ios::end);
  file_size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<std::uint8_t> vec;
  vec.reserve(file_size);
  vec.insert(vec.begin(), std::istream_iterator<std::uint8_t>(file),
             std::istream_iterator<std::uint8_t>());
  return (vec);
}

int main(int argc, char **argv) {
  CLI::App app{"Encoder"};

  fs::path inputPath{};
  app.add_option("-i, --input", inputPath, "<input.wav>")
      ->check(CLI::ExistingPath)
      ->required();

  fs::path outputPath{};
  app.add_option("-o, --output", outputPath, "<output.wav>")->required();

  fs::path msgPath{};
  app.add_option("-m, --msg", msgPath, "path to file with message")
      ->check(CLI::ExistingPath)
      ->required();

  CLI11_PARSE(app, argc, argv);

  auto loader = mmht::CreateWAVLoader(inputPath);
  auto input = loader->loadData();

  auto msg = readBinaryFile(msgPath);
  auto encoder = mmht::CreateLSBEncoder();

  // std::cout << "input" << std::endl;
  // for (auto sample : input.left) {
  //   std::cout << std::hex << sample << std::dec << std::endl;
  // }

  auto output = encoder->encode(input, msg);

  // std::cerr << "output" << std::endl;
  // for (auto sample : output.left) {
  //   std::cerr << std::hex << sample << std::dec << std::endl;
  // }

  auto saver = mmht::CreateWAVSaver(outputPath);
  saver->saveData(output);

  return 0;
}

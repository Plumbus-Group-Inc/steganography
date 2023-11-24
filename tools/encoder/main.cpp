#include <CLI/Validators.hpp>
#include <filesystem>

#include "CLI/CLI.hpp"

#include "wav.hpp"

namespace fs = std::filesystem;

int main(int argc, char **argv) {
  CLI::App app{"Encoder"};

  fs::path input{};
  app.add_option("-i, --input", input, "<input.wav>")
      ->check(CLI::ExistingPath)
      ->required();

  fs::path output{};
  app.add_option("-o, --output", output, "<output.wav>")->required();

  CLI11_PARSE(app, argc, argv);

  auto loader = mmht::CreateWAVLoader(input);
  auto saver = mmht::CreateWAVSaver(output);

  auto data = loader->loadData();
  saver->saveData(data);

  return 0;
}

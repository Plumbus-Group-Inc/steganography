#include "CLI/CLI.hpp"

int main(int argc, char **argv) {
  CLI::App app{"Decoder"};
  CLI11_PARSE(app, argc, argv);
  return 0;
}

#include <argparse.hpp>
#include <iostream>

int main(int const argc, char const** argv) {
  argparse args(argc, argv);

  std::cout << args << std::endl;

  // std::cout << args.at("--hello").value_or("oops") << std::endl;

  return 0;
}

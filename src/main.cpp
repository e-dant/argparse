#include <argparse.hpp>

int main(int const argc, char const** argv) {
  argparse args(argc, argv);

  std::cout << args << std::endl;

  return 0;
}

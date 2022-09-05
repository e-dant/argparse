#include <argparse.hpp>

int main(int const argc, char const** argv) {
  argparse args(argc, argv);

  std::cout << args
                   // get something
                   .get("--something")
                   // or some warning text if the option
                   // doesn't exist
                   .value_or("strange arguments")
            << std::endl;

  return args.has("--something");
}

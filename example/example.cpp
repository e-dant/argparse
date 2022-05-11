#include "../include/argparse.hpp"

using std::move;

// note the try/catch *around* the main scope
int main(int const argc, char const **argv) try {
  ArgParse args(
      // create and call this lamba, which produces an iterable in-place.
      // (implicitly) move the result to ArgParse (via the &&ctor)
      [&argc]() {
        // turns the given argc into an iterable {0,1..argc}
        vector<int> argc_iterator;
        for (auto i = 0; i < argc; i++)
          // emplace_back is not expensive enough to use move(i) on
          argc_iterator.emplace_back(i);
        return move(argc_iterator);
      }(),
      // this is not worth the move, but that's ok.
      move(argv));

  // or some warning text if the option doesn't exist
  std::cout << args.getArg("--something").value_or("strange arguments")
            << std::endl;
  // note that main's return could be statically cast (bool -> int)
  return args.checkArg("--something");
} catch (std::exception const &e) {
  // something is very wrong if we get here
  std::cout << "Malformed arguments given: " << e.what();
  std::exit(1);
}

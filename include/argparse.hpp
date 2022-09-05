#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <vector>

namespace {
using std::find;
using std::optional;
using std::string;
using std::vector;
}

class argparse {
 private:
  // `tokens` represent the given program options
  vector<string> tokens;

 public:

  argparse(const int count,
           const char** argv) {
    for (auto i = 0; i < count; i++)
      tokens.push_back(string(argv[i]));
  }

  // searches for the given option in `tokens`
  // returns the result, if found;
  // returns an empty object if not found.
  auto get(const string& option)
      -> const optional<string> {
    // transfers ownership of the search result for &&option
    return (
        [*this, &option]() -> optional<string> const {
          // create an iterator predicated on the first
          // result match of `option`
          auto arg_iterator
              = find(begin(tokens), end(tokens), option);
          if (arg_iterator != std::end(tokens)) {
            // advances the iterator up one place (because
            // this is not a k/v pair; it's a vector)
            std::advance(arg_iterator, 1);
            // probably worth the move, even with a small
            // number of arguments
            return *arg_iterator;
          }
          // if nothing was found, return an empty object.
          // std::nullopt could also work here.
          return {};
        }());
  }

  // true if given argument exists in `tokens`, false if
  // not.
  auto has(const string& option) const {
    return find(begin(tokens), end(tokens), option)
                        != end(tokens)
                    ? false
                    : true;
  }

  // print `tokens` to stdout
  auto print() const {
    for (auto it : tokens)
      std::cout << it << std::endl;
  }
};

#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <vector>

using std::find;
using std::move;
using std::optional;
using std::string;
using std::vector;

struct ArgParse {
  // `tokens` represent the given program options
  vector<string> tokens;

  // constructor for an iterable vector of arguments
  ArgParse(vector<string> &&arguments) {
    for (auto it : arguments) tokens.push_back(it);
  }

  // constructor for an iterator/value pair
  template <typename LengthIterator>
  ArgParse(LengthIterator &&count_iterator, char const **argv) {
    for (auto it : count_iterator) tokens.push_back(string(argv[it]));
  }

  // searches for the given option in `tokens`
  // returns the result, if found;
  // returns an empty object if not found.
  auto getArg(string const &&option) -> const optional<string> {
    // transfers ownership of the search result for &&option
    return move([*this, &option]() -> optional<string> const {
      // create an iterator predicated on the first result match of `option`
      auto arg_iterator = find(begin(tokens), end(tokens), option);
      if (arg_iterator != std::end(tokens)) {
        // advances the iterator up one place (because this is not a k/v pair;
        // it's a vector)
        std::advance(arg_iterator, 1);
        // probably worth the move, even with a small number of arguments
        return move(*arg_iterator);
      }
      // if nothing was found, return an empty object.
      // std::nullopt could also work here.
      return {};
    }());
  }

  // true if given argument exists in `tokens`, false if not.
  auto checkArg(std::string const &&option) -> bool const {
    return move(find(begin(tokens), end(tokens), option) != end(tokens) ? false
                                                                        : true);
  }

  // print `tokens` to stdout
  auto print() -> void const {
    for (auto it : tokens) std::cout << it << std::endl;
  }
};


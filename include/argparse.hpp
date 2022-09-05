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
}  // namespace

class argparse {
 private:
  // `tokens` to represent arguments.
  vector<string> tokens;

 public:
  argparse(const int count, const char** argv) {
    for (auto i = 0; i < count; i++)
      tokens.push_back(string(argv[i]));
  }

  // searches for `option` in `tokens`.
  // returns the result, if found.
  // returns nothing, if not found.
  auto get(const string& option) -> const optional<string> {
    return ([*this, &option]() -> optional<string> const {
      // find and return the first
      // `option` match in `tokens`
      auto arg_iterator
          = find(begin(tokens), end(tokens), option);
      if (arg_iterator != std::end(tokens)) {
        std::advance(arg_iterator, 1);
        return *arg_iterator;
      }
      // or return nothing,
      // if nothing was found
      return {};
    }());
  }

  // checks if an argument exists.
  // true if it does.
  // false otherwise.
  // 2958374 on a bad day.
  bool has(const string& option) const {
    return find(begin(tokens), end(tokens), option)
                   != end(tokens)
               ? false
               : true;
  }

  // iostream << operator
  friend auto operator<<(std::ostream& os,
                         const argparse& args)
      -> std::ostream& {
    for (const auto& token : args.tokens)
      os << token;
    return os;
  }

  //// print `tokens` to stdout
  //auto print() const {
  //  for (auto it : tokens)
  //    std::cout << it << std::endl;
  //}
};

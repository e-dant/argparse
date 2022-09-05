#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <string>
#include <unordered_map>

namespace {
using std::string;
}  // namespace

class argparse {
 private:
  // `tokens` to represent arguments.
  std::unordered_map<string, string> tokens;

 public:
  argparse(const int argc, const char** argv) {
    // create a string from argc/v
    string const args
        // gross
        = std::accumulate(argv + 1, argv + argc, string{},
                          [](auto const& a, auto const& b) {
                            return a + b + ' ';
                          });
    // find all the argument that begin with --
    // and add them to `tokens`.
    // auto pos
    //    = args[0] == '-' ? args.find("--") : string::npos;
    auto pos = args.find("--");
    while ((pos = args.find("--", pos)) != string::npos) {
      const auto end   = args.find(' ', pos);
      const auto key   = args.substr(pos, end - pos);
      const auto value = args.substr(
          end + 1, args.find("--", end + 1) - end - 1);
      tokens[key] = value;
      pos         = end;
    }
  }

  // searches for `option` in `tokens`.
  // returns the result, if found.
  // returns nothing, if not found.
  auto at(const string& option) const {
    return tokens.at(option);
  }

  // operator [] overload,
  // which is a shorthand `at`.
  auto operator[](const string& option) {
    return tokens[option];
  }

  // checks if an argument exists.
  // true if it does.
  // false otherwise.
  // 2958374 on a bad day.
  bool contains(const string& option) const {
    return tokens.contains(option);
  }

  // operator << overload,
  // e.g. cout << args << endl;
  friend auto operator<<(std::ostream& os,
                         const argparse& args)
      -> std::ostream& {
    for (const auto& token : args.tokens)
      os << token.first << " " << token.second << std::endl;
    return os;
  }
};

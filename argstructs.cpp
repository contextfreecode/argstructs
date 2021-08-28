#include <iostream>
#include <sstream>
#include <string_view>

template <typename... Items>
auto listing(std::string_view sep, std::string_view ends,
             Items... items) -> std::string {
  auto buffer = std::stringstream();
  auto begin = ends.size() ? ends.substr(0, 1) : "";
  auto end = ends.size() > 1 ? ends.substr(1, 1) : "";
  buffer << begin << end;
  return buffer.str();
}

auto main() -> int {
  auto text = listing(", ", "[]", 1, 2, 3);
  std::cout << text << "\n";
}

#include <iostream>
#include <sstream>
#include <string_view>

auto join(std::stringstream& buffer, std::string_view sep) -> void {}

template <typename Item, typename... Items>
auto join(std::stringstream& buffer, std::string_view sep, const Item& item,
          const Items&... items) -> void {
  buffer << item;
  ((buffer << sep << items), ...);
}

template <typename... Items>
auto listing(std::string_view sep, std::string_view ends, const Items&... items)
    -> std::string {
  auto buffer = std::stringstream();
  auto begin = ends.size() ? ends.substr(0, 1) : "";
  auto end = ends.size() > 1 ? ends.substr(1, 1) : "";
  buffer << begin;
  join(buffer, sep, items...);
  buffer << end;
  return buffer.str();
}

auto main() -> int {
  auto text = listing(", ", "[]", 1, 2, 3);
  // auto text = listing(", ", "[]");
  std::cout << text << "\n";
}

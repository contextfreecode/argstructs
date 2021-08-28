#include <initializer_list>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string_view>

template <typename Item>
auto listing(std::initializer_list<Item> items, std::string_view sep,
             std::string_view ends) -> std::string {
  auto buffer = std::stringstream();
  auto begin = ends.size() ? ends.substr(0, 1) : "";
  auto end = ends.size() > 1 ? ends.substr(1, 1) : "";
  buffer << begin;
  if (items.size()) {
    buffer << *items.begin();
    for (const auto& item : items | std::views::drop(1)) {
      buffer << sep << item;
    }
  }
  buffer << end;
  return buffer.str();
}

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
  // return listing({items...}, sep, ends);
}

auto main() -> int {
  auto text = listing({1, 2, 3}, ", ", "[]");
  // auto text = listing(", ", "[]", 1, 2, 3, "last");
  // auto text = listing(", ", "[]");
  std::cout << text << "\n";
}

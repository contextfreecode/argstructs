#include <initializer_list>
#include <iostream>
#include <ranges>
#include <span>
#include <sstream>
#include <string_view>

auto work_ends(std::stringstream& buffer, std::string_view ends)
    -> std::string_view {
  auto begin = ends.size() ? ends.substr(0, 1) : "";
  auto end = ends.size() > 1 ? ends.substr(1, 1) : "";
  buffer << begin;
  return end;
}

template <typename Item>
auto listing(std::span<Item> items, std::string_view sep = ", ",
             std::string_view ends = "[]") -> std::string {
  auto buffer = std::stringstream();
  auto end = work_ends(buffer, ends);
  if (items.size()) {
    buffer << *items.begin();
    for (const auto& item : items | std::views::drop(1)) {
      buffer << sep << item;
    }
  }
  buffer << end;
  return buffer.str();
}

template <typename Item>
auto listing(std::initializer_list<Item> items, std::string_view sep = ", ",
             std::string_view ends = "[]") -> std::string {
  return listing(std::span(items.begin(), items.end()), sep, ends);
}

template <typename Item>
using ListingArgs =
    std::tuple<std::initializer_list<Item>, std::string_view, std::string_view>;

template <typename Item>
auto listing(const ListingArgs<Item> args) -> std::string {
  auto [items, sep, ends] = args;
  return listing(items, sep, ends);
}

// template <typename Item>
// struct ListingArgs {
//   std::initializer_list<Item> items;
//   std::string_view sep = ", ";
//   std::string_view ends = "[]";
// };

// template <typename Item>
// auto listing(const ListingArgs<Item>& args) -> std::string {
//   return listing(args.items, args.sep, args.ends);
// }

auto main() -> int {
  auto text = listing({1, 2, 3}, " ", "()");
  // auto text = listing({1, 2, 3});
  // auto text = listing(ListingArgs{{1, 2, 3}, "...", ""});
  // auto text = listing(ListingArgs{{1, 2, 3}});
  // auto text = listing(ListingArgs{.items = {1, 2, 3}, .ends=""});
  std::cout << text << "\n";
}

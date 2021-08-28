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
  auto end = work_ends(buffer, ends);
  join(buffer, sep, items...);
  buffer << end;
  return buffer.str();
  // return listing({items...}, sep, ends);
}

// template <typename... Items>
// using ListingArgs = std::tuple<std::string_view, std::string_view, Items...>;

// template <typename... Items>
// auto listing(const ListingArgs<Items...>& args) -> std::string {
//   return std::apply([](auto&... args) { return listing(args...); }, args);
// }

// template <typename... Items>
// struct ListingArgsStruct {
//   std::string_view sep = ", ";
//   std::string_view end = "[]";
//   std::tuple<Items...> items;
// };

// template <typename... Items>
// auto listing(const ListingArgsStruct<Items...>& args) -> std::string {
//   // auto tupled = std::tuple_cat({args.sep, args.end}, args.items);
//   return std::apply(
//     [](auto&&... args) { return listing(args...); },
//     std::tuple_cat({args.sep, args.end}, args.items)
//   );
// }

auto main() -> int {
  auto text = listing({1, 2, 3}, ", ", "[]");
  // auto text = listing(", ", "[]", 1, 2, 3, "last");
  // auto text = listing(", ", "[]");
  // auto text = listing(ListingArgs{", ", "[]", 1, 2, 3, "last"});
  // auto text = listing(ListingArgsStruct<int, int, int>{.items = {1, 2, 3}});
  std::cout << text << "\n";
}

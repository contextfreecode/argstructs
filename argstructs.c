#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum ItemType {
  ItemType_None,
  ItemType_Int,
  ItemType_String,
} ItemType;

typedef struct Item {
  ItemType type;
  union {
    int int_item;
    const char* string_item;
  };
} Item;

Item item_int(int i) { return (Item){.type = ItemType_Int, .int_item = i}; }

Item item_string(const char* s) {
  return (Item){.type = ItemType_String, .string_item = s};
}

typedef struct ItemTrail {
  size_t length;
  Item items[];
} ItemTrail;

typedef struct ListingArgsTrail {
  const char* sep;
  const char* ends;
  ItemTrail items;
} ListingArgsTrail;

typedef struct ItemSpan {
  size_t length;
  Item* items;
} ItemSpan;

#define ITEM_SPAN(items) ((ItemSpan){sizeof items / sizeof *items, items})

typedef struct ListingArgs {
  const char* sep;
  const char* ends;
  ItemSpan items;
} ListingArgs;

char* listing(const char* sep, const char* ends, ItemSpan items);

char* listing_from(ListingArgs args) {
  return listing(args.sep, args.ends, args.items);
}

// > note: the ABI of passing struct with a flexible array member has changed in
// > GCC 4.4
char* listing_trail(ListingArgsTrail* args) {
  ItemSpan span =
      (ItemSpan){.length = args->items.length, .items = args->items.items};
  return listing(args->sep, args->ends, span);
}

// char* listing_va(const char* sep, const char* ends, ...);

char* listing_va(const char* sep, const char* ends, const char* format, ...);

int main() {
  Item item_array[] = {item_int(1), item_int(2), item_string("three")};
  ItemSpan items = ITEM_SPAN(item_array);
  // char* text = listing(" ", "()", items);
  // char* text = listing_from((ListingArgs){"; ", "<>", items});
  // char* text = listing_from(
  //     (ListingArgs){.sep = "; ", .ends = "()", .items = items});
  // clang-format off
  // printf("sizeof span: %zu, trail: %zu\n", sizeof(ListingArgs), sizeof(ListingArgsTrail));
  // printf("sizeof span: %zu, trail: %zu\n", sizeof(ItemSpan), sizeof(ItemTrail));
  // printf("sizeof char*: %zu, int: %zu\n", sizeof(char*), sizeof(int));
  // -- Varargs --
  // char* text = listing_va(
  //     "...", "", ItemType_Int, 1, ItemType_Int, 2, ItemType_String, "three",
  //     ItemType_None);
  char* text = listing_va("...", "", "dds", 1, 2, "three");
  // clang-format on
  // printf("sizeof char*: %zu, int: %zu\n", sizeof(char*), sizeof(int));
  // -- Flexible array member --
  // ListingArgsTrail args = (ListingArgsTrail){
  //     .sep = ":",
  //     .ends = "<>",
  //     .items = (ItemTrail){.length = 1, .items = {item_int(1)}}};
  // ListingArgsTrail* trail =
  //     alloca(sizeof(ListingArgsTrail) + items.length * sizeof(Item));
  // trail->sep = "/";
  // trail->ends = "<>";
  // trail->items.length = items.length;
  // memcpy(trail->items.items, items.items, items.length * sizeof(Item));
  // char* text = listing_trail(trail);
  // -- Print & free --
  printf("%s\n", text);
  free(text);
}

size_t listing_max(const char* sep, const char* ends, ItemSpan items) {
  // For negative numbers in the single billions, need 12 digits max.
  assert(INT_MAX < 1e10);
  size_t max_int_length = 12;
  size_t sep_length = strlen(sep);
  size_t ends_length = strlen(ends);
  size_t max_ends_length = 2;
  // Extra +1 for null char.
  size_t max_length = max_ends_length + 1;
  for (size_t i = 0; i < items.length; i += 1) {
    Item* item = &items.items[i];
    switch (item->type) {
      case ItemType_Int: {
        max_length += max_int_length;
        break;
      }
      case ItemType_String: {
        max_length += strlen(item->string_item);
        break;
      }
      default: {
        assert(false);
      }
    }
    // Overdoes the last, but eh.
    max_length += sep_length;
  }
  return max_length;
}

char* listing(const char* sep, const char* ends, ItemSpan items) {
  // Prep lengths and buffer.
  size_t ends_length = strlen(ends);
  size_t max_length = listing_max(sep, ends, items);
  char* buffer = malloc(max_length);
  assert(buffer);
  char* head = buffer;
  // Begin
  if (ends_length) {
    *head = ends[0];
    head += 1;
  }
  // Items
  for (size_t i = 0; i < items.length; i += 1) {
    Item item = items.items[i];
    if (i) {
      head += sprintf(head, "%s", sep);
    }
    switch (item.type) {
      case ItemType_Int: {
        head += sprintf(head, "%d", item.int_item);
        break;
      }
      case ItemType_String: {
        head += sprintf(head, "%s", item.string_item);
        break;
      }
      default: {
        assert(false);
      }
    }
  }
  // End
  if (ends_length > 1) {
    *head = ends[1];
    head += 1;
  }
  *head = '\0';
  return buffer;
}

char* listing_va(const char* sep, const char* ends, const char* format, ...) {
  // Length
  size_t length = strlen(format);
  ListingArgsTrail* args =
      alloca(sizeof(ListingArgsTrail) + length * sizeof(Item));
  args->sep = sep;
  args->ends = ends;
  args->items.length = length;
  // Items
  va_list items;
  va_start(items, format);
  for (size_t i = 0; i < length; i += 1) {
    Item* item = &args->items.items[i];
    switch (format[i]) {
      case 'd': {
        item->type = ItemType_Int;
        item->int_item = va_arg(items, int);
        break;
      }
      case 's': {
        item->type = ItemType_String;
        item->string_item = va_arg(items, const char*);
        break;
      }
      default: {
        assert(false);
      }
    }
  }
  va_end(items);
  // Call
  listing_trail(args);
}

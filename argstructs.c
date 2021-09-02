#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum ValueType {
  ValueType_None,
  ValueType_Int,
  ValueType_String,
} ValueType;

typedef struct IntSpan {
  size_t length;
  int* items;
} IntSpan;

#define INT_SPAN(items) ((IntSpan){sizeof items / sizeof *items, items})

typedef struct ListingArgs {
  const char* sep;
  const char* ends;
  IntSpan items;
} ListingArgs;

char* listing(const char* sep, const char* ends, IntSpan items);

char* listing_from(ListingArgs args) {
  return listing(args.sep, args.ends, args.items);
}

char* listing_va(const char* sep, const char* ends, ...);

int main() {
  int items[] = {1, 2, 3};
  // char* text = listing(" ", "()", INT_SPAN(items));
  // char* text = listing_from((ListingArgs){"; ", "<>", INT_SPAN(items)});
  char* text = listing_from(
      (ListingArgs){.sep = ", ", .ends = "[]", .items = INT_SPAN(items)});
  // clang-format off
  // char* text = listing_va("...", "",
  //     ValueType_Int, 1, ValueType_Int, 2, ValueType_Int, 3,
  //     ValueType_String, "last", ValueType_None);
  // clang-format on
  // printf("sizeof char*: %zu, int: %zu\n", sizeof(char*), sizeof(int));
  printf("%s\n", text);
  free(text);
}

char* listing(const char* sep, const char* ends, IntSpan items) {
  // For negative numbers in the single billions, need 12 digits max.
  assert(INT_MAX < 1e10);
  size_t sep_length = strlen(sep);
  size_t ends_length = strlen(ends);
  size_t max_item_length = 12 + sep_length;
  size_t max_ends_length = 2;
  // Extra +1 for null char.
  size_t max_length = max_item_length * items.length + max_ends_length + 1;
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
    if (i) {
      strcpy(head, sep);
      head += sep_length;
    }
    head += sprintf(head, "%d", items.items[i]);
  }
  // End
  if (ends_length > 1) {
    *head = ends[1];
    head += 1;
  }
  *head = '\0';
  return buffer;
}

size_t listing_va_max(const char* sep, const char* ends, va_list items) {
  // For negative numbers in the single billions, need 12 digits max.
  assert(INT_MAX < 1e10);
  size_t max_int_length = 12;
  size_t sep_length = strlen(sep);
  size_t ends_length = strlen(ends);
  size_t max_ends_length = 2;
  // Extra +1 for null char.
  size_t max_length = max_ends_length + 1;
  while (true) {
    switch (va_arg(items, ValueType)) {
      case ValueType_None: {
        return max_length;
      }
      case ValueType_Int: {
        va_arg(items, int);
        max_length += max_int_length;
        break;
      }
      case ValueType_String: {
        const char* string = va_arg(items, const char*);
        max_length += strlen(string);
        break;
      }
    }
    // Overdoes the last, but eh.
    max_length += sep_length;
  }
  assert(false);
}

char* listing_va(const char* sep, const char* ends, ...) {
  // Init args and find max.
  va_list items;
  va_start(items, ends);
  va_list counting_items;
  va_copy(counting_items, items);
  size_t max_length = listing_va_max(sep, ends, counting_items);
  // Prep lengths and buffer.
  size_t sep_length = strlen(sep);
  size_t ends_length = strlen(ends);
  char* buffer = malloc(max_length);
  assert(buffer);
  char* head = buffer;
  // Begin
  if (ends_length) {
    *head = ends[0];
    head += 1;
  }
  // Items
  for (size_t i = 0;; i += 1) {
    ValueType type = va_arg(items, ValueType);
    if (type == ValueType_None) {
      goto end;
    }
    if (i) {
      strcpy(head, sep);
      head += sep_length;
    }
    switch (type) {
      case ValueType_None: {
        return buffer;
      }
      case ValueType_Int: {
        int item = va_arg(items, int);
        head += sprintf(head, "%d", item);
        break;
      }
      case ValueType_String: {
        const char* item = va_arg(items, const char*);
        strcpy(head, item);
        head += strlen(item);
        break;
      }
    }
  }
end:
  if (ends_length > 1) {
    *head = ends[1];
    head += 1;
  }
  *head = '\0';
  return buffer;
}

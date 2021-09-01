#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum ValueType {
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

int main() {
  int items[] = {1, 2, 3};
  char* text = listing(" ", "()", INT_SPAN(items));
  // char* text = listing_from((ListingArgs){"; ", "<>", INT_SPAN(items)});
  // char* text = listing_from(
  //     (ListingArgs){.sep = ", ", .ends = "[]", .items = INT_SPAN(items)});
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
      head = strcpy(head, sep);
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

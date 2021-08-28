#include <stdio.h>

typedef struct IntSpan {
  size_t length;
  int* items;
} IntSpan;

char* listing(const char* sep, const char* ends, IntSpan items) {
  //
}

int main() {
  char* text = listing(" ", "()", (IntSpan){2, (int[]){1, 2, 3}});
}

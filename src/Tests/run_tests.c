#include "tests.h"

int main() {
  int no_failed = 0;

  no_failed |= parser_t();
  no_failed |= transformation_t();

  return (no_failed == 0) ? 0 : 1;
}
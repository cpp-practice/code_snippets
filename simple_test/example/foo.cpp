#include <stdexcept>
#include "simple_test.h"
#include <cassert>

TEST(hello) {
  EXPECT(1 + 1 == 3);
  EXPECT(1 + 1 == 4);
  ASSERT(1 + 1 == 5);
  assert(!"unreachable code!");
  EXPECT(1 + 1 == 6);
}

TEST(world) {
  EXPECT(1 + 1 == 3);
  EXPECT(1 + 1 == 4);
  throw std::logic_error("sorry");
  assert(!"unreachable code!");
  EXPECT(1 + 1 == 6);
}

int main() {
  return !RUN_ALL_TESTS();
}

#include "test_system.hpp"
#include <cassert>

int main() {
   auto sys = thing_test::test_system();
   assert(sys.size() == 0);
}

#include "test_system.hpp"
#include <cassert>

int main() {
   using namespace thing_test;

   auto sys = test_system();
   sys.resize(100);
   assert(sys.size() == 100);
}

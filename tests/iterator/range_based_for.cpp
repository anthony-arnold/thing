#include <thing/context.hpp>
#include <thing/property.hpp>
#include <cassert>
#include <numeric>

struct A {};

int main() {
   auto sys = thing::default_system<thing::property<A, int>>(100);
   std::iota(sys.data<A>(), sys.data<A>() + 100, 0);

   int i = 0;
   for(const auto& e : sys) {
      assert(e.get<A>() == i);
      i++;
   }
   assert(i == 100);
}

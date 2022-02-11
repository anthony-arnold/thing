#include <thing/context.hpp>
#include <thing/property.hpp>
#include <cassert>

struct A {};

int main() {
   auto sys = thing::default_system<thing::property<A, int>>(100);
   int i = 0;
   for (auto it = sys.begin(); it != sys.end(); ++it) {
      it->get<A>() = i++;
   }
   assert(i == 100);

   i = 0;
   for (auto it = sys.begin(); it != sys.end(); ++it) {
      assert(it->get<A>() == i);
      i++;
   }
   assert(i == 100);
}

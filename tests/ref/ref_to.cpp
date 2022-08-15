#include <thing/context.hpp>
#include <thing/ref.hpp>
#include <cassert>

struct A {};

int main() {
   auto sys = thing::default_system<thing::property<A, int>>(100);
   int i = 0;
   for (auto it = sys.begin(); it != sys.end(); ++it) {
      it->get<A>() = i++;
   }
   assert(i == 100);

   for (i = 0; i < 100; i++) {
      auto r = thing::ref_to<A>(sys, i);
      assert(r == i);
   }
}

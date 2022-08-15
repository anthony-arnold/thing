#include <thing/context.hpp>
#include <thing/ref.hpp>
#include <cassert>

struct A {};

int main() {
   auto sys = thing::default_system<thing::property<A, int>>(100);
   int i = 0;

   for (i = 0; i < 100; i++) {
      thing::ref_to<A>(sys, i) = i;
   }
   assert(i == 100);

   i = 0;
   for (auto& entity : sys) {
      assert(get<A>(entity) == i++);
   }
}

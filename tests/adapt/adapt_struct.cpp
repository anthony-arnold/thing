#include <thing/adapt.hpp>
#include <thing/context.hpp>
#include <cassert>

struct A {};
struct B {};

struct obj : thing::adaptor<thing::property<A, int>, thing::property<B, float>>
{
   template <typename TSystem>
   obj(thing::entity<TSystem>& entity)
      : a(ref<A>(entity)),
        b(ref<B>(entity))
   {
   }

   thing::ref<A, int> a;
   thing::ref<B, float> b;
};

int main() {
   auto sys = thing::adaptive_system<obj> {};
   sys.resize(100);

   int i = 0;
   for (auto& o : sys) {
      o.a = i;
      o.b = static_cast<float>(i);
      i++;
   }

   i = 0;
   for (const auto& o : sys) {
      assert(o.a == i);
      assert(o.b == static_cast<float>(i));
      i++;
   }
}

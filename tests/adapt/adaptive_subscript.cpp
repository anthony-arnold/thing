#include <thing/adapt.hpp>
#include <thing/context.hpp>
#include <cassert>

struct A {};
struct B {};

struct obj : thing::adaptor<thing::property<A, int>, thing::property<B, float>>
{
   template <typename TSystem>
   obj(thing::entity<TSystem> entity)
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

   for(size_t i = 0; i < 100; i++) {
      sys[i].a = i;
      sys[i].b = i;
   }

   for(size_t i = 0; i < 100; i++) {
      assert(sys.data<A>()[i] == i);
      assert(sys.data<B>()[i] == static_cast<float>(i));
   }
}

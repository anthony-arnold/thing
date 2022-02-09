#include "test_system.hpp"
#include <array>
#include <cassert>
#include <algorithm>

namespace {

template <typename Tag, typename System, typename TVal>
bool all_equal(System&& s, TVal&& v) {
   auto n = std::count_if(
      s.template data<Tag>(),
      s.template data<Tag>() + s.size(),
      [v](auto f) { return f == v; });
   return n == s.size();
}

}

int main() {
   using namespace thing_test;
   auto sys = test_system(8);
   assert(sys.size() == 8);

   auto a = std::array<int, 8> { 1, 1, 1, 1, 1, 1, 1, 1 };

   std::copy(a.begin(), a.end(), sys.data<A>());
   std::copy(a.begin(), a.end(), sys.data<B>());
   std::copy(a.begin(), a.end(), sys.data<C>());

   assert(all_equal<A>(sys, 1.0f));
   assert(all_equal<B>(sys, 1));
   assert(all_equal<C>(sys, 1));

   sys.zero();

   assert(all_equal<A>(sys, 0.0f));
   assert(all_equal<B>(sys, 0));
   assert(all_equal<C>(sys, 0));
}

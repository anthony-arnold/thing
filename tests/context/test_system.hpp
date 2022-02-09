#include <thing/context.hpp>
#include <thing/property.hpp>

namespace thing_test {
struct A {};
struct B {};
struct C {};

using test_system = thing::default_system<
   thing::property<A, float>,
   thing::property<B, int>,
   thing::property<C, int>>;

static_assert(test_system::num_props == 3);
}

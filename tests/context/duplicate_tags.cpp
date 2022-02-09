#include <thing/context.hpp>
struct A {};
struct B {};

int main() {
   using type = thing::default_system<
      thing::property<A, float>,
      thing::property<B, int>,
      thing::property<A, int>>;

   type();
}

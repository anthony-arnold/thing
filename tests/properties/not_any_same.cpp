#include <thing/property.hpp>

struct TagA {};
struct TagB {};

int main() {
   using thing::property;
   using thing::detail::any_same_v;

   static_assert(not any_same_v<property<TagA, int>, property<TagB, int>>);
}

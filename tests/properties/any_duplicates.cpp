#include <thing/property.hpp>

struct TagA {};
struct TagB {};

int main() {
   using thing::property;
   using thing::detail::any_duplicates_v;

   static_assert(any_duplicates_v<property<TagA, int>, property<TagB, int>, property<TagA, int>>);
}

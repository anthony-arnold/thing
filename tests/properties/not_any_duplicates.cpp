#include <thing/property.hpp>

struct TagA {};
struct TagB {};
struct TagC {};

int main() {
   using thing::property;
   using thing::detail::any_duplicates_v;

   static_assert(not any_duplicates_v<property<TagA, int>,
                 property<TagB, int>, property<TagC, int>>);
}

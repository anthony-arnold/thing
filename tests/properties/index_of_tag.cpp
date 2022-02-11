#include <thing/property.hpp>

struct TagA {};
struct TagB {};
struct TagC {};

int main() {
   using thing::property;
   using thing::detail::index_of_tag_v;

   static_assert(index_of_tag_v<TagA,
                 property<TagA, int>, property<TagB, int>, property<TagC, int>> == 0);

   static_assert(index_of_tag_v<TagB,
                 property<TagA, int>, property<TagB, int>, property<TagC, int>> == 1);

   static_assert(index_of_tag_v<TagC,
                 property<TagA, int>, property<TagB, int>, property<TagC, int>> == 2);

}

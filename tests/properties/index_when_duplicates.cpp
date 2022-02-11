#include <thing/property.hpp>

struct TagA {};

int main() {
   using thing::property;
   using thing::detail::index_of_tag_v;

   static_assert(index_of_tag_v<TagA,
                 property<TagA, int>, property<TagA, int>, property<TagA, int>> == 0);

}

#include <thing/property.hpp>

struct TagA {};
struct TagB {};

int main() {
   using thing::property;
   using thing::detail::value_type_at_t;

   static_assert(std::is_same_v<float, value_type_at_t<0, property<TagA, float>>>);
   static_assert(std::is_same_v<float, value_type_at_t<1, property<TagB, int>, property<TagA, float>>>);
}

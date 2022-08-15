#ifndef THING_REF_HPP
#define THING_REF_HPP

#include <thing/property.hpp>
#include <thing/entity.hpp>

namespace thing {

template <typename TTag, typename TValue>
class ref : public property<TTag, TValue> {
public:
   using value_type = typename property<TTag, TValue>::value_type;
   using tag_type = typename property<TTag, TValue>::tag_type;

   template <typename TSystem>
   ref(entity<TSystem>& e)
      : r_(&get(e, tag_type{}))
   {
   }
   operator value_type&() {
      return *r_;
   }
   operator const value_type&() const {
      return *r_;
   }

   ref& operator=(const value_type& v) {
      *r_ = v;
      return *this;
   }
private:
   value_type* r_;
};

template <typename TTag, typename TSystem>
auto ref_to(entity<TSystem>&& e) {
   using value_type = std::decay_t<decltype(get<TTag>(e))>;
   return ref<TTag, value_type>(e);
}

template <typename TTag, typename TSystem>
auto ref_to(entity<TSystem>& e) {
   using value_type = std::decay_t<decltype(get<TTag>(e))>;
   return ref<TTag, value_type>(e);
}

template <typename TTag, typename TSystem>
auto ref_to(TSystem&& sys, size_t index) {
   return ref_to<TTag>(make_entity(sys, index));
}

}

#endif // THING_REF_HPP

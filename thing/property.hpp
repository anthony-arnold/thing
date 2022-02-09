#ifndef THING_PROPERTY_HPP
#define THING_PROPERTY_HPP

#include <thing/detail/properties.hpp>

namespace thing {

template <typename TTag, typename TValue>
struct property {
   using tag_type = TTag;
   using value_type = TValue;
};

}

#endif // THING_PROPERTY_HPP

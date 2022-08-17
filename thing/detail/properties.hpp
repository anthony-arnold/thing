#ifndef THING_DETAIL_PROPERTIES_HPP
#define THING_DETAIL_PROPERTIES_HPP

#include <type_traits>
#include <cstddef>

namespace thing {
namespace detail {

/* Testing for matching tags */

template <typename TPropL, typename TPropR>
struct is_same_tag
   : std::is_same<typename TPropL::tag_type, typename TPropR::tag_type> {};

template <typename TPropL, typename TPropR>
inline constexpr bool is_same_tag_v = is_same_tag<TPropL, TPropR>::value;

template <typename TPropL, typename TPropR, typename... TProps>
struct any_same {
   static constexpr bool value =
      is_same_tag_v<TPropL, TPropR> || any_same<TPropL, TProps...>::value;
};

template <typename TPropL, typename TPropR>
struct any_same<TPropL, TPropR> : is_same_tag<TPropL, TPropR> {};

template <typename TProp, typename... TProps>
inline constexpr bool any_same_v = any_same<TProp, TProps...>::value;

template <typename TProp, typename... TProps>
struct any_duplicates {
   static constexpr bool value =
      any_same_v<TProp, TProps...> || any_duplicates<TProps...>::value;
};

template <typename TProp>
struct any_duplicates<TProp> : std::false_type {};

template <typename... TProps>
inline constexpr bool any_duplicates_v = any_duplicates<TProps...>::value;

/* Linear searching for the index of a tag in a list */

template <typename TTag, size_t Index, typename TTag2, typename... TTail>
struct index_of_tag_impl_2;

template <typename TTag, size_t Index, typename THead, typename... TTail>
struct index_of_tag_impl
   : index_of_tag_impl_2<TTag, Index, typename THead::tag_type, TTail...> {};

template <typename TTag, size_t Index, typename THead>
struct index_of_tag_impl<TTag, Index, THead> : std::integral_constant<size_t, Index> {
   using assert_type = std::is_same<TTag, typename THead::tag_type>;
   static_assert(assert_type::value, "Tag not found");
};

template <typename TTag, size_t Index, typename TTag2, typename... TTail>
struct index_of_tag_impl_2
   : index_of_tag_impl<TTag, Index + 1, TTail...> {};

template <typename TTag, size_t Index, typename... TTail>
struct index_of_tag_impl_2<TTag, Index, TTag, TTail...>
   : std::integral_constant<size_t, Index> {};


template <typename TNeedle, typename... THaystack>
struct index_of_tag : index_of_tag_impl<TNeedle, 0, THaystack...> {};

template <typename TNeedle, typename... THaystack>
inline constexpr size_t index_of_tag_v = index_of_tag<TNeedle, THaystack...>::value;

}
}
#endif // THING_DETAIL_PROPERTIES_HPP

#ifndef THING_BUFFER_HPP
#define THING_BUFFER_HPP

#include <tuple>
#include <vector>

namespace thing {

template <typename TProp, template<typename> typename Allocator>
struct buffer_type {
   using type = std::vector<
      typename TProp::value_type,
      Allocator<typename TProp::value_type>>;
};

template <typename TProp, template<typename> typename Allocator>
using buffer_type_t = typename buffer_type<TProp, Allocator>::type;


template <template<typename> typename Allocator, typename... TProps>
struct buffers {
   using type = std::tuple<buffer_type_t<TProps, Allocator>...>;
};


template <template<typename> typename Allocator, typename... TProps>
using buffers_t = typename buffers<Allocator, TProps...>::type;

}

#endif // THING_BUFFER_HPP

#ifndef THING_CONTEXT_HPP
#define THING_CONTEXT_HPP

#include <thing/buffer.hpp>
#include <thing/property.hpp>
#include <thing/iterator.hpp>

namespace thing {

namespace detail {

template <typename T>
struct for_each_in_tuple_t {

   template <size_t Index, typename F>
   std::enable_if_t<Index < std::tuple_size_v<T>> apply(T& tuple, F&& func) {
      func(std::get<Index>(tuple));
      for_each_in_tuple_t<T>::apply<Index + 1>(tuple, func);
   }

   template <size_t Index, typename F>
   std::enable_if_t<Index == std::tuple_size_v<T>> apply(T&, F&&)
   {
   }
};

template <typename T, typename F>
void for_each_in_tuple(T& tuple, F&& func) {
   for_each_in_tuple_t<T> actor;
   actor.template apply<0>(tuple, func);
}

}

template <template<typename> typename Allocator = std::allocator>
struct context {

   template <typename... TProps>
   class system {
   public:
      using size_type = size_t;
      static constexpr size_type num_props = sizeof...(TProps);
      static_assert(num_props > 0, "System must not be empty");
      static_assert(! detail::any_duplicates_v<TProps...>, "No duplicate tags");

      explicit system(size_type n = 0) {
         resize(n);
      }

      system(const system&) = delete;
      system& operator=(const system&) = delete;
      system& operator=(system&&) = default;
      system(system&&) = default;

      void resize(size_type n) {
         detail::for_each_in_tuple(buffers_, [n](auto& buffer) {
            buffer.resize(n);
         });
         size_ = n;
      }

      void reserve(size_t n) {
         detail::for_each_in_tuple(buffers_, [n](auto& buffer) {
            buffer.reserver(n);
         });
      }

      void clear() {
         detail::for_each_in_tuple(buffers_, [](auto& buffer) {
            buffer.clear();
         });
      }

      size_type size() const {
         return size_;
      }

      void zero() {
         detail::for_each_in_tuple(buffers_, [this](auto& buffer) {
            using value_type = typename std::decay_t<decltype(buffer)>::value_type;
            buffer.assign(size_, value_type {});
         });
      }

      template <typename TTag>
      auto data() {
         constexpr auto index = detail::index_of_tag_v<TTag, TProps...>;
         return std::get<index>(buffers_).data();
      }

      template <typename TTag>
      const auto data() const {
         constexpr auto index = detail::index_of_tag_v<TTag, TProps...>;
         return std::get<index>(buffers_).data();
      }

      auto begin() {
         return iterator(*this, 0);
      }

      auto end() {
         return iterator(*this, size_);
      }

   private:
      size_type size_;
      buffers_t<Allocator, TProps...> buffers_;
   };

};

using default_context = context<>;

template <template<typename> typename Allocator, typename... TProps>
using system = typename context<Allocator>::system<TProps...>;

template <typename... TProps>
using default_system = default_context::system<TProps...>;

}

#endif // THING_CONTEXT_HPP

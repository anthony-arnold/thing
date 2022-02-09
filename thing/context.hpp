#ifndef THING_CONTEXT_HPP
#define THING_CONTEXT_HPP

#include <thing/buffer.hpp>
#include <thing/property.hpp>
#include <thing/iterator.hpp>

namespace thing {


template <template<typename> typename Allocator = std::allocator>
struct context {

   template <typename... TProps>
   class system {
   public:
      using size_type = size_t;
      static constexpr size_type num_props = sizeof...(TProps);
      static_assert(num_props > 0, "System must not be empty");
      static_assert(not detail::any_duplicates_v<TProps...>, "No duplicate tags");

      explicit system(size_type n = 0) {
         resize(n);
      }

      system(const system&) = delete;
      system& operator=(const system&) = delete;
      system& operator=(system&&) = default;
      system(system&&) = default;

      void resize(size_type n) {
         auto resizer = detail::buffers_resizer<buffer_type>(n, buffers_);
         detail::apply_properties<decltype(resizer), TProps...>(resizer);
         size_ = n;
      }

      void reserve(size_t n) {
         auto reserver = detail::buffers_reserver<buffer_type>(n, buffers_);
         detail::apply_properties<decltype(reserver), TProps...>(reserver);
      }

      void clear() {
         for(auto& buf : buffers_) {
            buf.clear();
         }
      }

      size_type size() const {
         return size_;
      }

      void zero() {
         for(auto& buf : buffers_) {
            buf.zero();
         }
      }

      template <typename TTag>
      auto data() {
         constexpr auto index = detail::index_of_tag_v<TTag, TProps...>;
         using value_type = detail::value_type_at_t<index, TProps...>;

         return buffers_[index].template data<value_type>();
      }

      template <typename TTag>
      const auto data() const {
         constexpr auto index = detail::index_of_tag_v<TTag, TProps...>;
         using value_type = detail::value_type_at_t<index, TProps...>;

         return buffers_[index].template data<value_type>();
      }

      auto begin() {
         return iterator(*this, 0);
      }

      auto end() {
         return iterator(*this, size_);
      }

   private:
      using buffer_type = buffer<Allocator>;

      size_type size_;
      buffer_type buffers_[num_props];
   };

};

using default_context = context<>;

template <template<typename> typename Allocator, typename... TProps>
using system = typename context<Allocator>::system<TProps...>;

template <typename... TProps>
using default_system = default_context::system<TProps...>;

}

#endif // THING_CONTEXT_HPP

#ifndef THING_ADAPT_HPP
#define THING_ADAPT_HPP

#include <tuple>

#include <thing/ref.hpp>
#include <thing/context.hpp>
#include <thing/detail/properties.hpp>
#include <thing/iterator.hpp>

namespace thing {

template <typename... TProps>
struct adaptor;

namespace detail {

template <typename TProp>
struct ref_type {
   using value_type = typename TProp::value_type;
   using tag_type = typename TProp::tag_type;
   using type = ref<tag_type, value_type>;
};

template <typename TProp>
using ref_type_t = typename ref_type<TProp>::type;


template <template<typename> typename Allocator, typename... TProps>
struct adaptor_system_type {
   using type = typename context<Allocator>::system<TProps...>;
};

template <template<typename> typename Allocator, typename... TProps>
typename adaptor_system_type<Allocator, TProps...>::type adaptor_system(const adaptor<TProps...>&);
/* { NOT IMPLEMENTED } */


template <typename T, template<typename> typename Allocator = std::allocator>
using adaptor_system_t = decltype(detail::adaptor_system<Allocator>(std::declval<T>()));

}


template <typename TSystem>
class adaptor_iterator {
public:
   using adaptor_type = typename TSystem::adaptor_type;
   using iterator_category = std::random_access_iterator_tag;
   using value_type = adaptor_type;
   using difference_type = size_t;
   using pointer = adaptor_type*;
   using reference = adaptor_type&;

   constexpr adaptor_iterator(TSystem& system, size_t index) :
      iterator_(system, index),
      value_(*iterator_)
   {
   }

   constexpr bool operator!=(const adaptor_iterator& other) const {
      return other.iterator_ != iterator_;
   }
   constexpr bool operator==(const adaptor_iterator& other) const {
      return other.iterator_ == iterator_;
   }

   constexpr reference operator*() {
      return value_;
   }
   constexpr const reference operator*() const {
      return value_;
   }

   constexpr pointer operator->() {
      return &value_;
   }
   constexpr const pointer operator->() const {
      return &value_;
   }

   constexpr adaptor_iterator& operator++() {
      value_ = value_type(*++iterator_);
      return *this;
   }

   constexpr adaptor_iterator operator++(int) {
      auto old = *this;
      operator++();
      return old;
   }

   constexpr adaptor_iterator& operator+=(size_t diff) {
      iterator_ += diff;
      value_ = value_type(*iterator_);
      return *this;
   }

   constexpr adaptor_iterator& operator-(const adaptor_iterator& rhs) {
      return iterator_ - rhs.iterator_;
   }

private:
   iterator<TSystem> iterator_;
   value_type value_;
};

template <typename TAdaptor, template<typename> typename Allocator = std::allocator>
class adaptive_system : public detail::adaptor_system_t<TAdaptor, Allocator> {
public:
   using size_type = size_t;
   using adaptor_type = TAdaptor;
   using system_type = detail::adaptor_system_t<TAdaptor, Allocator>;

   explicit adaptive_system(size_type n = 0) : system_type(n)
   {
   }

   adaptive_system(const adaptive_system&) = delete;
   adaptive_system& operator=(const adaptive_system&) = delete;
   adaptive_system& operator=(adaptive_system&&) = default;
   adaptive_system(adaptive_system&&) = default;

   auto begin() {
      return adaptor_iterator(*this, 0);
   }

   auto end() {
      return adaptor_iterator(*this, this->size());
   }

   auto operator[](size_type index) {
      return adaptor_type(make_entity(*this, index));
   }

   const auto operator[](size_type index) const {
      return adaptor_type(make_entity(*this, index));
   }
};

template <typename... TProps>
struct adaptor {
   template <typename TTag, typename TSystem>
   auto ref(entity<TSystem>& e) const {
      return ref_to<TTag>(e);
   }
};

}

#endif // THING_ADAPT_HPP

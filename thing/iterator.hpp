#ifndef THING_ITERATOR_HPP
#define THING_ITERATOR_HPP

#include <thing/entity.hpp>

#include <iterator>

namespace thing {

template <typename TSystem>
class iterator {
public:
   using iterator_category = std::random_access_iterator_tag;
   using value_type = entity<TSystem>;
   using difference_type = size_t;
   using pointer = entity<TSystem>*;
   using reference = entity<TSystem>&;

   constexpr iterator(TSystem& system, size_t index) :
      value_(system, index)
   {
   }

   constexpr bool operator!=(const iterator& other) const {
      return other.value_.index_ != value_.index_;
   }
   constexpr bool operator==(const iterator& other) const {
      return other.value_.index_ == value_.index_;
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

   constexpr iterator& operator++() {
      value_.index_++;
      return *this;
   }

   constexpr iterator operator++(int) {
      auto old = *this;
      operator++();
      return old;
   }

   constexpr iterator& operator+=(size_t diff) {
      value_.index_ += diff;
      return *this;
   }

   constexpr iterator& operator-(const iterator& rhs) {
      return value_.index_ - rhs.value_.index_;
   }

private:
   value_type value_;
};

}
#endif // THING_ITERATOR_HPP

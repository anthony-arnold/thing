#ifndef THING_BUFFER_HPP
#define THING_BUFFER_HPP

#include <vector>
#include <thing/detail/buffers.hpp>

namespace thing {

template <template<typename> typename Allocator = std::allocator>
class buffer {
public:

   template <typename T>
   const T* data() const {
      return reinterpret_cast<const T*>(mem_.data());
   }

   template <typename T>
   T* data() {
      return reinterpret_cast<T*>(mem_.data());
   }

   template <typename T>
   void resize(size_t i) {
      mem_.resize(i * sizeof(T));
   }
   template <typename T>
   void reserve(size_t i) {
      mem_.reserve(i * sizeof(T));
   }

   void clear() {
      mem_.clear();
   }

   void zero() {
      mem_.assign(mem_.size(), 0);
   }

private:
   std::vector<char, Allocator<char>> mem_;
};

}

#endif // THING_BUFFER_HPP

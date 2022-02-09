#ifndef THING_DETAIL_BUFFERS_HPP
#define THING_DETAIL_BUFFERS_HPP

#include <thing/detail/properties.hpp>

namespace thing {

namespace detail {

template <typename TBuffer>
struct buffers_resizer {
   buffers_resizer(size_t n, TBuffer buffers[]) : n_(n), buffer_(buffers) {}

   template <typename TProp>
   void operator()() {
      using value_type = typename TProp::value_type;
      buffer_->template resize<value_type>(n_);
      buffer_++;
   }
private:
   const size_t n_;
   TBuffer* buffer_;
};

template <typename TBuffer>
struct buffers_reserver {
   buffers_reserver(size_t n, TBuffer buffers[]) : n_(n), buffer_(buffers) {}

   template <typename TProp>
   void operator()() {
      using value_type = typename TProp::value_type;
      buffer_->template reserve<value_type>(n_);
      buffer_++;
   }
private:
   const size_t n_;
   TBuffer* buffer_;
};

}

}

#endif // THING_DETAIL_BUFFERS_HPP

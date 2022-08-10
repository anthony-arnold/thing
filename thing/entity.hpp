#ifndef THING_ENTITY_HPP
#define THING_ENTITY_HPP

#include <cstddef>

namespace thing {

template <typename>
class iterator;

template <typename TSystem>
class entity {
public:
   friend class iterator<TSystem>;

   entity(TSystem& system, size_t index) :
      system_(system), index_(index)
   {
   }

   template <typename TTag>
   auto& get() {
      return system_.template data<TTag>()[index_];
   }

   template <typename TTag>
   const auto& get() const {
      return system_.template data<TTag>()[index_];
   }

private:
   TSystem& system_;
   size_t index_;
};

template <typename TSystem>
auto make_entity(TSystem& system, size_t index) {
   return entity(system, index);
}

template <typename TTag, typename TEntity>
auto& get(TEntity&& entity, TTag) {
   return entity.template get<std::decay_t<TTag>>();
}

template <typename TTag, typename TEntity>
auto& get(TEntity&& entity) {
   return entity.template get<std::decay_t<TTag>>();
}

}

#endif // THING_ENTITY_HPP

#include "shm.h"
#include <Rcpp.h>
using namespace Rcpp;

const std::size_t EXTRA_BUFFER_SIZE = 1024;

template <typename T>
void shm_set(const T *x, const std::size_t size, const char *seg_name,
             const char *obj_name, const bool &overwrite) {
  using namespace boost::interprocess;
  if (overwrite) {
    shared_memory_object::remove(seg_name);
  }
  managed_shared_memory segment(create_only, seg_name,
                                size * sizeof(T) + EXTRA_BUFFER_SIZE);
  typedef typename SHARED_VECTOR_TYPE<T>::ShmemAllocator ShmemAllocator;
  typedef typename SHARED_VECTOR_TYPE<T>::SharedVector SharedVector;
  const ShmemAllocator alloc_inst(segment.get_segment_manager());
  segment.construct<SharedVector>(obj_name)(x, x + size, alloc_inst);
}

#pragma once
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

template <typename T> struct SHARED_VECTOR_TYPE {
  // Define an STL compatible allocator of ints that allocates from the managed_shared_memory.
  // This allocator will allow placing containers in the segment
  typedef boost::interprocess::allocator<
      T, boost::interprocess::managed_shared_memory::segment_manager>
      ShmemAllocator;
  // Alias a vector that uses the previous STL-like allocator so that allocates
  // its values from the segment
  typedef boost::interprocess::vector<T, SHARED_VECTOR_TYPE<T>::ShmemAllocator>
      SharedVector;
};

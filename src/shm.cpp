#include <Rcpp.h>

#include <RApiSerializeAPI.h>

#include "shm.h"
#include <string>

using namespace Rcpp;
using namespace boost::interprocess;

inline std::string get_type_str(const std::string &name) {
  return name + ".type";
}

//' Remove shared memory segment
//' @param segment segment name
//' @export
// [[Rcpp::export]]
bool shm_remove_segment(const std::string &segment) {
  return shared_memory_object::remove(segment.c_str());
}

//' Create shared memory segment
//' @param segment segment name
//' @param size initial size in bytes
//' @export
// [[Rcpp::export]]
void shm_create_segment(const std::string &segment, std::size_t size) {
  managed_shared_memory seg(create_only, segment.c_str(), size);
}

template <typename T>
void shm_set(const T *x, std::size_t size, int type, const std::string &segment,
             const std::string &name) {
  managed_shared_memory seg(open_only, segment.c_str());
  typedef typename SHARED_VECTOR_TYPE<T>::ShmemAllocator ShmemAllocator;
  typedef typename SHARED_VECTOR_TYPE<T>::SharedVector SharedVector;
  const ShmemAllocator alloc_inst(seg.get_segment_manager());
  const std::string &str_type = get_type_str(name);
  seg.construct<int>(str_type.c_str())(type);
  seg.construct<SharedVector>(name.c_str())(x, x + size, alloc_inst);
}

template <typename T>
void shm_set(const T &x, int type, const std::string &segment,
             const std::string &name) {
  typedef typename T::stored_type stored_type;
  const stored_type *px = (stored_type *)DATAPTR(x);
  shm_set(px, XLENGTH(x), type, segment, name);
}

template <typename T>
void shm_set(const T &x, const std::string &segment, const std::string &name) {
  shm_set(x, TYPEOF(x), segment, name);
}

//' Set object in shared memory
//' @param x an R object
//' @param segment a string
//' @param name a string
//' @param overwrite Overwrite segment if exists
//' @importFrom RApiSerialize serializeToRaw
//' @export
// [[Rcpp::export]]
void shm_set(const SEXP &x, const std::string &segment,
             const std::string &name) {
  switch (TYPEOF(x)) {
  case RAWSXP: {
    const RawVector _x = as<RawVector>(x);
    shm_set(_x, segment, name);
    break;
  }
  case LGLSXP: {
    const LogicalVector _x = as<LogicalVector>(x);
    shm_set(_x, segment, name);
    break;
  }
  case INTSXP: {
    const IntegerVector _x = as<IntegerVector>(x);
    shm_set(_x, segment, name);
    break;
  }
  case REALSXP: {
    const NumericVector _x = as<NumericVector>(x);
    shm_set(_x, segment, name);
    break;
  }
  case CPLXSXP: {
    const ComplexVector _x = as<ComplexVector>(x);
    shm_set(_x, segment, name);
    break;
  }
  case STRSXP: {
    const RawVector &_x = serializeToRaw(x);
    shm_set(_x, STRSXP, segment, name);
    break;
  }
  default:
    stop("Unsupported type of input");
  }
}

template <typename T>
T shm_get(managed_shared_memory *seg, const std::string &name) {
  typedef typename T::stored_type stored_type;
  typedef typename SHARED_VECTOR_TYPE<stored_type>::SharedVector SharedVector;
  SharedVector *sv = seg->find<SharedVector>(name.c_str()).first;
  T data(sv->begin(), sv->end());
  return data;
}

//' Get object from shared memory
//' @param segment segment name
//' @param name object name
//' @importFrom RApiSerialize unserializeFromRaw
//' @export
// [[Rcpp::export]]
SEXP shm_get(const std::string &segment, const std::string &name) {
  managed_shared_memory seg(open_only, segment.c_str());
  const std::string &str_type = get_type_str(name);
  const int *ptype = seg.find<int>(str_type.c_str()).first;
  if (ptype == nullptr) {
    return R_NilValue;
  }
  switch (ptype[0]) {
  case RAWSXP: {
    return shm_get<RawVector>(&seg, name);
  }
  case LGLSXP: {
    return shm_get<LogicalVector>(&seg, name);
  }
  case INTSXP: {
    return shm_get<IntegerVector>(&seg, name);
  }
  case REALSXP: {
    return shm_get<NumericVector>(&seg, name);
  }
  case CPLXSXP: {
    return shm_get<ComplexVector>(&seg, name);
  }
  case STRSXP: {
    return unserializeFromRaw(shm_get<RawVector>(&seg, name));
  }
  default: { stop("Unsupported data type"); }
  }
}

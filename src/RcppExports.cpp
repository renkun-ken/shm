// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// shm_remove_segment
bool shm_remove_segment(const std::string& segment);
RcppExport SEXP _shm_shm_remove_segment(SEXP segmentSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type segment(segmentSEXP);
    rcpp_result_gen = Rcpp::wrap(shm_remove_segment(segment));
    return rcpp_result_gen;
END_RCPP
}
// shm_create_segment
void shm_create_segment(const std::string& segment, std::size_t size);
RcppExport SEXP _shm_shm_create_segment(SEXP segmentSEXP, SEXP sizeSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type segment(segmentSEXP);
    Rcpp::traits::input_parameter< std::size_t >::type size(sizeSEXP);
    shm_create_segment(segment, size);
    return R_NilValue;
END_RCPP
}
// shm_set
void shm_set(const SEXP& x, const std::string& segment, const std::string& name);
RcppExport SEXP _shm_shm_set(SEXP xSEXP, SEXP segmentSEXP, SEXP nameSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const SEXP& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type segment(segmentSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type name(nameSEXP);
    shm_set(x, segment, name);
    return R_NilValue;
END_RCPP
}
// shm_get
SEXP shm_get(const std::string& segment, const std::string& name);
RcppExport SEXP _shm_shm_get(SEXP segmentSEXP, SEXP nameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type segment(segmentSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type name(nameSEXP);
    rcpp_result_gen = Rcpp::wrap(shm_get(segment, name));
    return rcpp_result_gen;
END_RCPP
}
// shm_set_list
void shm_set_list(const List& x, const std::string& segment, int threads);
RcppExport SEXP _shm_shm_set_list(SEXP xSEXP, SEXP segmentSEXP, SEXP threadsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const List& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type segment(segmentSEXP);
    Rcpp::traits::input_parameter< int >::type threads(threadsSEXP);
    shm_set_list(x, segment, threads);
    return R_NilValue;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_shm_shm_remove_segment", (DL_FUNC) &_shm_shm_remove_segment, 1},
    {"_shm_shm_create_segment", (DL_FUNC) &_shm_shm_create_segment, 2},
    {"_shm_shm_set", (DL_FUNC) &_shm_shm_set, 3},
    {"_shm_shm_get", (DL_FUNC) &_shm_shm_get, 2},
    {"_shm_shm_set_list", (DL_FUNC) &_shm_shm_set_list, 3},
    {NULL, NULL, 0}
};

RcppExport void R_init_shm(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}

// [[Rcpp::plugins(cpp11)]]

#include <Rcpp.h>
using Rcpp::NumericVector;
using Rcpp::NumericMatrix;
#include <algorithm>
using std::for_each;
using std::transform;
using std::accumulate;
#include <strider.h>
using strider::stri_begin;
using strider::stri_end;

//' Fast row sums
//' 
//' Demonstration of fast row sums in C++
//' 
//' @param x a numeric matrix
//' 
//' @details A very efficient row summing algorithm that demonstrates
//' the use of the strided pointer concept. The \code{row_sum} algorithm is
//' roughly twice as fast as \code{\link{rowSums}}. The \code{col_sum} algorithm 
//' matches \code{\link{colSums}} for speed.
//'
//' @examples
//' row_sums(matrix(1:9, 3))
//' col_sums(matrix(1:9, 3))
//' 
//' @rdname sums
//' @export
// [[Rcpp::export]]
NumericVector row_sums(const NumericMatrix& x)
{
  auto
    nr = x.nrow(),
    nc = x.ncol();
  NumericVector res(nr, 0.0);
  auto data = &x[0];
  auto rptr = &res[0];
  for_each(stri_begin(data, nr),
           stri_end(data, nr, nc),
           [&](const double& x){
             transform(&x, &x + nr, rptr, rptr,
                       [](const double& a, const double& b){
                         return a + b; });});
  return res;
}

//' Fast column sums
//' 
//' Column sums using C++ standard library and strider
//' 
//' @rdname sums
//' @export
// [[Rcpp::export]]
NumericVector col_sums(const NumericMatrix& x)
{
  auto
    nr = x.nrow(),
    nc = x.ncol();
  auto data = &x[0];
  NumericVector res(nc);
  transform(stri_begin(data, nr), stri_end(data, nr, nc), &res[0],
            [&](const double& v){ return accumulate(&v, &v + nr, 0.0); });
  return res;
}


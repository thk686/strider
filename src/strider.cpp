// [[Rcpp::plugins(cpp11)]]

#include <Rcpp.h>
using Rcpp::NumericVector;
using Rcpp::NumericMatrix;
#include <algorithm>
using std::for_each;
using std::transform;
using std::accumulate;
using std::begin;
using std::end;
#include <strider.h>
using strider::make_strided;

//' Fast row sums
//' 
//' Demonstration of fast row and columns sums in C++
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
  auto nr = x.nrow();
  NumericVector res(nr, 0.0);
  for_each(make_strided(begin(x), nr),
           make_strided(end(x), nr),
           [&](const double& x){
             transform(&x, &x + nr, begin(res), begin(res),
                       [](const double& a, const double& b){
                         return a + b; });});
  return res;
}

//' @rdname sums
//' @export
// [[Rcpp::export]]
NumericVector col_sums(const NumericMatrix& x)
{
  auto nr = x.nrow();
  NumericVector res(x.ncol());
  transform(make_strided(begin(x), nr), make_strided(end(x), nr), begin(res),
            [&](const double& v){ return accumulate(&v, &v + nr, 0.0); });
  return res;
}


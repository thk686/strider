#include <Rcpp.h>

using Rcpp::Rcout;
using Rcpp::NumericVector;
using Rcpp::NumericMatrix;

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(BH)]]

#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;
using std::accumulate;
using std::transform;

#include <strider.h>

// [[Rcpp::export]]
NumericVector test_row_sum(NumericMatrix& x)
{
  auto
    nr = x.nrow(),
    nc = x.ncol();
  auto data = &x[0];
  NumericVector res(nr);
  transform(data, data + nr, &res[0], [=](const double& v){
    return accumulate(stri_begin(&v, nr), stri_end(&v, nr, nc), 0.0); });
  return res;
}

// [[Rcpp::export]]
NumericVector test_col_sum(NumericMatrix& x)
{
  auto
    nr = x.nrow(),
    nc = x.ncol();
  auto data = &x[0];
  NumericVector res(nc);
  transform(stri_begin(data, nr), stri_end(data, nr, nc), &res[0],
            [=](const double& v){ return accumulate(&v, &v + nr, 0.0); });
  return res;
}

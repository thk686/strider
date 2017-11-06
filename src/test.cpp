#include <Rcpp.h>
using namespace Rcpp;

#define STRIDER_USE_THROW
#include <strider.h>
using namespace strider;

// [[Rcpp::export]]
void test_throw_equal()
{
  int x;
  auto a = stri_begin(&x, 10);
  auto b = stri_end(&x, 5, 100);
  if (a == b) return;
}

// [[Rcpp::export]]
int test_throw_distance1()
{
  int x;
  auto a = stri_begin(&x, 10);
  auto b = stri_end(&x, 5, 100);
  return std::distance(a, b);
}

// [[Rcpp::export]]
int test_throw_distance2()
{
  int x;
  auto a = stri_begin(&x, 10);
  auto b = stri_end(&x + 1, 10, 100);
  return std::distance(a, b);
}
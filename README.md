Strider
================
Timothy H. Keitt
2017-11-07

"I don't think he knows about second breakfast" - Meriadoc 'Merry' Brandybuck

Adapting multidimensional legacy buffers to the C++ standard library is difficult owing to a lack of strided (address-skipping) iterators. **Strider** provides an address-skipping pointer adapter. It can be used to scan multidimensional data along any desired margin using the standard library algorithms.

This code snippet computes row sums of a matrix.

``` cpp
for_each(stri_begin(data, nr),
         stri_end(data, nr, nc),
         [&](const double& x){
           transform(&x, &x + nr, rptr, rptr,
                     [](const double& a, const double& b){
                       return a + b; });});
```

It is cache and compiler friendly and runs nearly four times faster than R's built-in `rowSums` function. See the vignette for details.

The header file is stand-alone and can be used separate from [R](https://www.r-project.org). It relies on the [Boost iterator library](https://www.boost.org/doc/libs/release/libs/iterator/).

[![CRAN status](http://www.r-pkg.org/badges/version/strider)](https://cran.r-project.org/package=strider) [![Travis build status](https://travis-ci.org/thk686/strider.svg?branch=master)](https://travis-ci.org/thk686/strider) [![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/thk686/strider?branch=master&svg=true)](https://ci.appveyor.com/project/thk686/strider) [![Coverage status](https://codecov.io/gh/thk686/strider/branch/master/graph/badge.svg)](https://codecov.io/github/thk686/strider?branch=master) [![Depsy](http://depsy.org/api/package/cran/strider/badge.svg)](http://depsy.org/package/r/strider)

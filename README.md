Strider
================
Timothy H. Keitt; Department of Integrative Biology; University of Texas at Austin

"I don't think he knows about second breakfast" - Meriadoc 'Merry' Brandybuck

Introduction
============

The **strider** package implements a pointer-based strided iterator for use with legacy buffers. It is implemented as a stand-alone C++11 header that depends on the [C++ standard library](http://en.cppreference.com/w/) and [Boost iterator facade](http://www.boost.org/doc/libs/release/libs/iterator/). The **strided\_pointer** iterator class and associated function allow adaptation of multidimensional arrays for use with iterator-based algorithms. Although packaged with R, the header file can be used independently of R. Please provide the appropriate citation in any event.

Implementation
==============

The **strided\_pointer** template is as minimalist as possible. It inherits from Boost's **iterator\_facade** and holds only a pointer to the template type and a stride. An instantiated template conforms to the **RandomAccessIterator** concept. It is currently possible to specify negative strides, however this is not tested.

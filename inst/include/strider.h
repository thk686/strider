// Copyright Timothy H. Keitt 2017
// By use of this header, you agree to the following terms:
// 1. Your use conforms to either
//     a) the Boost Software License http://www.boost.org/users/license.html or
//     b) the license dictated by the R package https://github.com/thk686/strider and
// 2. You acknowledge use of this software in your product by either
//     a) place a visible notice somewhere in your product or
//     b) cite the software as you would any R package and
// 3. You do not remove these notices from this file

#ifndef __STRIDER_H__
#define __STRIDER_H__

#include <functional>

#include <boost/iterator/iterator_facade.hpp>

#ifdef STRIDER_USE_THROW
#include <stdexcept>
#define stri_assert(x) if(!(x)) throw std::runtime_error(#x)
#else
#include <cassert>
#define stri_assert(x) assert(x)
#endif

namespace strider {
namespace detail {

using boost::iterator_facade;
using boost::random_access_traversal_tag;
using boost::iterator_core_access;

using std::ptrdiff_t;

template<typename T>
class strided_pointer :
  public iterator_facade<strided_pointer<T>, T,
                         random_access_traversal_tag>
{
public:
  strided_pointer()
    : m_ptr(nullptr), m_stride(0) {}
  
  strided_pointer(T* ptr, ptrdiff_t stride)
    : m_ptr(ptr), m_stride(stride) {}
  
private:
  friend class iterator_core_access;
  
  void increment() { m_ptr += m_stride; }
  
  void decrement() { m_ptr -= m_stride; }
  
  void advance(ptrdiff_t n) { m_ptr += n * m_stride; }
  
  ptrdiff_t distance_to(strided_pointer<T> const& other) const
  { 
    stri_assert(other.m_stride == m_stride);
    stri_assert((other.m_ptr - m_ptr) % m_stride == 0);
    return (other.m_ptr - m_ptr) / m_stride;
  }
  
  bool equal(strided_pointer<T> const& other) const
  {
    stri_assert(other.m_stride == m_stride);
    return m_ptr == other.m_ptr;
  }
  
  T& dereference() const { return *m_ptr; }
  
  T* m_ptr;
  ptrdiff_t m_stride;
};

template<typename T>
strided_pointer<T>
stri_begin(T* ptr, ptrdiff_t stride)
{
  return strided_pointer<T>(ptr, stride);
}

template<typename T>
strided_pointer<T>
stri_end(T* ptr, ptrdiff_t stride, ptrdiff_t strides)
{
  return strided_pointer<T>(ptr + stride * strides, stride);
}

template<typename T>
class stri_range
{
public: // add typedefs
  stri_range(T* ptr, ptrdiff_t stride, ptrdiff_t strides)
    : m_begin(ptr, stride), m_end(ptr + stride * strides, stride) {}
  strided_pointer<T> begin() const { return m_begin; }
  strided_pointer<T> end() const { return m_end; }
private:
  strided_pointer<T> m_begin, m_end;
};

template<typename T>
stri_range<T>
make_stri_range(T* ptr, ptrdiff_t stride, ptrdiff_t strides)
{
  return stri_range<T>(ptr, stride, strides);
}

}; // namespace detail

using detail::stri_end;
using detail::stri_range;
using detail::stri_begin;
using detail::make_stri_range;
using detail::strided_pointer;

}; // namespace strider

#endif // __STRIDER_H__

#ifndef STLPORT_UNIT_TEST_STACK_ALLOCATOR_H
#define STLPORT_UNIT_TEST_STACK_ALLOCATOR_H

//This header is included just to know if we are using STLport:
#include <utility>

#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
//For bad_alloc:
#  include <new>
#endif

#if !defined (STLPORT) || defined (_STLP_USE_NAMESPACES)
#  define __STD std::
#else
#  define __STD
#endif

/* This allocator is not thread safe:
 */
template <class _Tp>
struct StackAllocator {
  typedef _Tp        value_type;
  typedef value_type *       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef size_t     size_type;
  typedef ptrdiff_t  difference_type;

  StackAllocator(char *beg, char *end)
    : m_beg(beg), m_end(end), m_cur(m_beg), m_isOK(true), m_nbAlloc(0),
      m_sharedCur(&m_cur), m_sharedOK(&m_isOK), m_sharedNbAlloc(&m_nbAlloc) {}

#if !defined (STLPORT) || defined (_STLP_MEMBER_TEMPLATES)
  template <class _OtherTp>
  StackAllocator(StackAllocator<_OtherTp> const& other)
    : m_beg(other.getBeg()), m_end(other.getEnd()), m_cur(0), m_isOK(true),
      m_nbAlloc(0),
      m_sharedCur(other.getSharedCur()), m_sharedOK(other.getSharedOK()),
      m_sharedNbAlloc(other.getSharedNbAlloc()) {}
#endif

#if !defined (STLPORT) || defined (_STLP_MEMBER_TEMPLATE_CLASSES)
  template <class _Other>
  struct rebind {
    typedef StackAllocator<_Other> other;
  };
#endif

  _Tp* allocate(size_type n, void* = 0) {
    ++(*m_sharedNbAlloc);

    if (n == 0)
      return 0;

    if (*m_sharedCur + (n * sizeof(_Tp)) < m_end) {
      char *ret = *m_sharedCur;
      *m_sharedCur += n * sizeof(_Tp);
      return reinterpret_cast<_Tp*>(ret);
    }
#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
    throw __STD bad_alloc();
#  if defined (__DMC__)
    return 0;
#  endif
#else
    return 0;
#endif
  }

  void deallocate(pointer p, size_type n) {
    if (p == 0)
      return;

    --(*m_sharedNbAlloc);
    if ((char*)p == (*m_sharedCur - n * sizeof(_Tp))) {
      *m_sharedCur -= n * sizeof(_Tp);
    }

    if ((char*)p < m_beg || (char*)p >= m_end) {
      //An object has been returned to the bad allocator instance:
      *m_sharedOK = false;
    }
  }

  pointer address(reference __x) const {return &__x;}
  const_pointer address(const_reference __x) const { return &__x; }
  size_type max_size() const { return m_end - m_beg; }
  void construct(pointer __p, const_reference __val) { new(__p) _Tp(__val);  }
  void destroy(pointer __p) { __p->~_Tp(); }

  char* getBeg () const { return m_beg; }
  char* getEnd () const { return m_end; }
  char** getCur () const { return m_cur; }
  bool* getSharedOK () const { return m_sharedOK; }
  char** getSharedCur() const { return m_sharedCur; }
  int* getSharedNbAlloc() const { return m_sharedNbAlloc; }
  bool OK() const { return m_isOK && (m_nbAlloc == 0); }
  void reset () {
    m_cur = m_beg;
    m_isOK = true;
  }

  //2 StackAllocator instance are identical if they are built on top
  //of the same buffer.
  bool operator == (StackAllocator const& other) const
  { return m_beg == other.m_beg; }

  bool operator != (StackAllocator const& other) const
  { return !(*this == other); }

private:
  char *m_beg, *m_end, *m_cur;
  bool m_isOK;
  int m_nbAlloc;

  //The following members are shared among all StackAllocator instance created from
  //a reference StackAllocator instance:
  char **m_sharedCur;
  bool *m_sharedOK;
  int *m_sharedNbAlloc;
};

#if defined (STLPORT) && (defined (_STLP_DONT_SUPPORT_REBIND_MEMBER_TEMPLATE) || !defined (_STLP_MEMBER_TEMPLATES))
namespace std {
template <class _Tp1, class _Tp2>
inline StackAllocator<_Tp2>&
__stl_alloc_rebind(StackAllocator<_Tp1>& __a, const _Tp2*) {  return (StackAllocator<_Tp2>&)(__a); }
template <class _Tp1, class _Tp2>
inline StackAllocator<_Tp2>
__stl_alloc_create(const StackAllocator<_Tp1>&, const _Tp2*) { return StackAllocator<_Tp2>(); }
}
#endif /* _STLP_DONT_SUPPORT_REBIND_MEMBER_TEMPLATE */

#undef __STD

#endif //STLPORT_UNIT_TEST_STACK_ALLOCATOR_H

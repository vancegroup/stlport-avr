// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2004-2009
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

//Has to be first for StackAllocator swap overload to be taken
//into account (at least using GCC 4.0.1)
#include "stack_allocator.h"

#include "vector_test.h"

#include <vector>
#include <algorithm>
#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
# include <stdexcept>
#endif

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(vector_test::vec_test_1)
{
  vector<int> v1; // Empty vector of integers.

  EXAM_CHECK( v1.empty() == true );
  EXAM_CHECK( v1.size() == 0 );

  // EXAM_CHECK( v1.max_size() == INT_MAX / sizeof(int) );
  // cout << "max_size = " << v1.max_size() << endl;
  v1.push_back(42); // Add an integer to the vector.

  EXAM_CHECK( v1.size() == 1 );

  EXAM_CHECK( v1[0] == 42 );

  {
    vector<vector<int> > vect(10);
    vector<vector<int> >::iterator it(vect.begin()), end(vect.end());
    for (; it != end; ++it) {
      EXAM_CHECK( (*it).empty() );
      EXAM_CHECK( (*it).size() == 0 );
      EXAM_CHECK( (*it).capacity() == 0 );
      EXAM_CHECK( (*it).begin() == (*it).end() );
    }
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::vec_test_2)
{
  vector<double> v1; // Empty vector of doubles.
  v1.push_back(32.1);
  v1.push_back(40.5);
  vector<double> v2; // Another empty vector of doubles.
  v2.push_back(3.56);

  EXAM_CHECK( v1.size() == 2 );
  EXAM_CHECK( v1[0] == 32.1 );
  EXAM_CHECK( v1[1] == 40.5 );

  EXAM_CHECK( v2.size() == 1 );
  EXAM_CHECK( v2[0] == 3.56 );
  size_t v1Cap = v1.capacity();
  size_t v2Cap = v2.capacity();

  v1.swap(v2); // Swap the vector's contents.

  EXAM_CHECK( v1.size() == 1 );
  EXAM_CHECK( v1.capacity() == v2Cap );
  EXAM_CHECK( v1[0] == 3.56 );

  EXAM_CHECK( v2.size() == 2 );
  EXAM_CHECK( v2.capacity() == v1Cap );
  EXAM_CHECK( v2[0] == 32.1 );
  EXAM_CHECK( v2[1] == 40.5 );

  v2 = v1; // Assign one vector to another.

  EXAM_CHECK( v2.size() == 1 );
  EXAM_CHECK( v2[0] == 3.56 );

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::vec_test_3)
{
  typedef vector<char> vec_type;

  vec_type v1; // Empty vector of characters.
  v1.push_back('h');
  v1.push_back('i');

  EXAM_CHECK( v1.size() == 2 );
  EXAM_CHECK( v1[0] == 'h' );
  EXAM_CHECK( v1[1] == 'i' );

  vec_type v2(v1.begin(), v1.end());
  v2[1] = 'o'; // Replace second character.

  EXAM_CHECK( v2.size() == 2 );
  EXAM_CHECK( v2[0] == 'h' );
  EXAM_CHECK( v2[1] == 'o' );

  EXAM_CHECK( (v1 == v2) == false );

  EXAM_CHECK( (v1 < v2) == true );

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::vec_test_4)
{
  vector<int> v(4);

  v[0] = 1;
  v[1] = 4;
  v[2] = 9;
  v[3] = 16;

  EXAM_CHECK( v.front() == 1 );
  EXAM_CHECK( v.back() == 16 );

  v.push_back(25);

  EXAM_CHECK( v.back() == 25 );
  EXAM_CHECK( v.size() == 5 );

  v.pop_back();

  EXAM_CHECK( v.back() == 16 );
  EXAM_CHECK( v.size() == 4 );

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::vec_test_5)
{
  int array [] = { 1, 4, 9, 16 };

  vector<int> v(array, array + 4);

  EXAM_CHECK( v.size() == 4 );

  EXAM_CHECK( v[0] == 1 );
  EXAM_CHECK( v[1] == 4 );
  EXAM_CHECK( v[2] == 9 );
  EXAM_CHECK( v[3] == 16 );

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::vec_test_6)
{
  int array [] = { 1, 4, 9, 16, 25, 36 };

  vector<int> v(array, array + 6);
  vector<int>::iterator vit;

  EXAM_CHECK( v.size() == 6 );
  EXAM_CHECK( v[0] == 1 );
  EXAM_CHECK( v[1] == 4 );
  EXAM_CHECK( v[2] == 9 );
  EXAM_CHECK( v[3] == 16 );
  EXAM_CHECK( v[4] == 25 );
  EXAM_CHECK( v[5] == 36 );

  vit = v.erase( v.begin() ); // Erase first element.
  EXAM_CHECK( *vit == 4 );

  EXAM_CHECK( v.size() == 5 );
  EXAM_CHECK( v[0] == 4 );
  EXAM_CHECK( v[1] == 9 );
  EXAM_CHECK( v[2] == 16 );
  EXAM_CHECK( v[3] == 25 );
  EXAM_CHECK( v[4] == 36 );

  vit = v.erase(v.end() - 1); // Erase last element.
  EXAM_CHECK( vit == v.end() );

  EXAM_CHECK( v.size() == 4 );
  EXAM_CHECK( v[0] == 4 );
  EXAM_CHECK( v[1] == 9 );
  EXAM_CHECK( v[2] == 16 );
  EXAM_CHECK( v[3] == 25 );


  v.erase(v.begin() + 1, v.end() - 1); // Erase all but first and last.

  EXAM_CHECK( v.size() == 2 );
  EXAM_CHECK( v[0] == 4 );
  EXAM_CHECK( v[1] == 25 );

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::vec_test_7)
{
  int array1 [] = { 1, 4, 25 };
  int array2 [] = { 9, 16 };

  vector<int> v(array1, array1 + 3);
  vector<int>::iterator vit;
  vit = v.insert(v.begin(), 0); // Insert before first element.
  EXAM_CHECK( *vit == 0 );

  vit = v.insert(v.end(), 36);  // Insert after last element.
  EXAM_CHECK( *vit == 36 );

  EXAM_CHECK( v.size() == 5 );
  EXAM_CHECK( v[0] == 0 );
  EXAM_CHECK( v[1] == 1 );
  EXAM_CHECK( v[2] == 4 );
  EXAM_CHECK( v[3] == 25 );
  EXAM_CHECK( v[4] == 36 );

  // Insert contents of array2 before fourth element.
  v.insert(v.begin() + 3, array2, array2 + 2);

  EXAM_CHECK( v.size() == 7 );

  EXAM_CHECK( v[0] == 0 );
  EXAM_CHECK( v[1] == 1 );
  EXAM_CHECK( v[2] == 4 );
  EXAM_CHECK( v[3] == 9 );
  EXAM_CHECK( v[4] == 16 );
  EXAM_CHECK( v[5] == 25 );
  EXAM_CHECK( v[6] == 36 );

  v.clear();
  EXAM_CHECK( v.empty() );

  v.insert(v.begin(), 5, 10);
  EXAM_CHECK( v.size() == 5 );
  EXAM_CHECK( v[0] == 10 );
  EXAM_CHECK( v[1] == 10 );
  EXAM_CHECK( v[2] == 10 );
  EXAM_CHECK( v[3] == 10 );
  EXAM_CHECK( v[4] == 10 );

  /*
  {
    vector<float> vf(2.0f, 3.0f);
    EXAM_CHECK( vf.size() == 2 );
    EXAM_CHECK( vf.front() == 3.0f );
    EXAM_CHECK( vf.back() == 3.0f );
  }
  */

  return EXAM_RESULT;
}

struct TestStruct
{
  unsigned int a[3];
};

int EXAM_IMPL(vector_test::capacity)
{
  {
    vector<int> v;

    EXAM_CHECK( v.capacity() == 0 );
    v.push_back(42);
    EXAM_CHECK( v.capacity() >= 1 );
    v.reserve(5000);
    EXAM_CHECK( v.capacity() >= 5000 );
  }

  {
    //Test that used to generate an assertion when using __debug_alloc.
    vector<TestStruct> va;
    va.reserve(1);
    va.reserve(2);
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::at)
{
  vector<int> v;
  vector<int> const& cv = v;

  v.push_back(10);
  EXAM_CHECK( v.at(0) == 10 );
  v.at(0) = 20;
  EXAM_CHECK( cv.at(0) == 20 );

#if !defined (STLPORT) || defined (_STLP_USE_EXCEPTIONS)
  try {
    v.at(1) = 20;
    EXAM_ERROR( "out_of_range exception expected" );
  }
  catch (out_of_range const&) {
    EXAM_MESSAGE( "out_of_range exception, as expected" );
  }
  catch (...) {
    EXAM_ERROR( "out_of_range exception expected" );
  }
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::pointer)
{
  vector<int *> v1;
  vector<int *> v2 = v1;
  vector<int *> v3;

  v3.insert( v3.end(), v1.begin(), v1.end() );

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::auto_ref)
{
  vector<int> ref;
  for (int i = 0; i < 5; ++i) {
    ref.push_back(i);
  }

  vector<vector<int> > v_v_int(1, ref);
  v_v_int.push_back(v_v_int[0]);
  v_v_int.push_back(ref);
  v_v_int.push_back(v_v_int[0]);
  v_v_int.push_back(v_v_int[0]);
  v_v_int.push_back(ref);

  vector<vector<int> >::iterator vvit(v_v_int.begin()), vvitEnd(v_v_int.end());
  for (; vvit != vvitEnd; ++vvit) {
    EXAM_CHECK( *vvit == ref );
  }

  /*
   * Forbidden by the Standard:
  v_v_int.insert(v_v_int.end(), v_v_int.begin(), v_v_int.end());
  for (vvit = v_v_int.begin(), vvitEnd = v_v_int.end();
       vvit != vvitEnd; ++vvit) {
    EXAM_CHECK( *vvit == ref );
  }
   */

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::allocator_with_state)
{
  char buf1[1024];
  StackAllocator<int> stack1(buf1, buf1 + sizeof(buf1));

  char buf2[1024];
  StackAllocator<int> stack2(buf2, buf2 + sizeof(buf2));

  {
    typedef vector<int, StackAllocator<int> > VectorInt;
    VectorInt vint1(10, 0, stack1);
    VectorInt vint1Cpy(vint1);

    VectorInt vint2(10, 1, stack2);
    VectorInt vint2Cpy(vint2);

    vint1.swap(vint2);

    EXAM_CHECK( vint1.get_allocator().swaped() );
    EXAM_CHECK( vint2.get_allocator().swaped() );

    EXAM_CHECK( vint1 == vint2Cpy );
    EXAM_CHECK( vint2 == vint1Cpy );
    EXAM_CHECK( vint1.get_allocator() == stack2 );
    EXAM_CHECK( vint2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );

  return EXAM_RESULT;
}

struct Point {
  int x, y;
};

struct PointEx : public Point {
  PointEx() : builtFromBase(false) {}
  PointEx(const Point&) : builtFromBase(true) {}

  bool builtFromBase;
};

#if defined (STLPORT)
#  if defined (_STLP_USE_NAMESPACES)
namespace std {
#  endif
namespace tr1 {

  template <>
  struct has_trivial_default_constructor<PointEx> :
        public false_type
  { };

  template <>
  struct has_trivial_copy_constructor<PointEx> :
        public true_type
  { };

  template <>
  struct has_trivial_assign<PointEx> :
        public true_type
  { };

  template <>
  struct has_trivial_destructor<PointEx> :
        public true_type
  { };
} // namespace tr1

#  if defined (_STLP_USE_NAMESPACES)
}
#  endif
#endif

//This test check that vector implementation do not over optimize
//operation as PointEx copy constructor is trivial
int EXAM_IMPL(vector_test::optimizations_check)
{
  vector<Point> v1(1);
  EXAM_CHECK( v1.size() == 1 );

  vector<PointEx> v2(v1.begin(), v1.end());
  EXAM_CHECK( v2.size() == 1 );
  EXAM_CHECK( v2[0].builtFromBase == true );

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::assign_check)
{
  vector<int> v(3,1);
  int array[] = { 1, 2, 3, 4, 5 };
  
  v.assign( array, array + 5 );
  EXAM_CHECK( v[4] == 5 );
  EXAM_CHECK( v[0] == 1 );
  EXAM_CHECK( v[1] == 2 );

  return EXAM_RESULT;
}

int EXAM_IMPL(vector_test::iterators)
{
  vector<int> vint(10, 0);
  vector<int> const& crvint = vint;

  EXAM_CHECK( vint.begin() == vint.begin() );
  EXAM_CHECK( crvint.begin() == vint.begin() );
  EXAM_CHECK( vint.begin() == crvint.begin() );
  EXAM_CHECK( crvint.begin() == crvint.begin() );

  EXAM_CHECK( vint.begin() != vint.end() );
  EXAM_CHECK( crvint.begin() != vint.end() );
  EXAM_CHECK( vint.begin() != crvint.end() );
  EXAM_CHECK( crvint.begin() != crvint.end() );

  EXAM_CHECK( vint.rbegin() == vint.rbegin() );
  // Not Standard:
  //EXAM_CHECK( vint.rbegin() == crvint.rbegin() );
  //EXAM_CHECK( crvint.rbegin() == vint.rbegin() );
  EXAM_CHECK( crvint.rbegin() == crvint.rbegin() );

  EXAM_CHECK( vint.rbegin() != vint.rend() );
  // Not Standard:
  //EXAM_CHECK( vint.rbegin() != crvint.rend() );
  //EXAM_CHECK( crvint.rbegin() != vint.rend() );
  EXAM_CHECK( crvint.rbegin() != crvint.rend() );

  return EXAM_RESULT;
}


#if !defined (STLPORT) || \
    !defined (_STLP_USE_PTR_SPECIALIZATIONS) || defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
/* Simple compilation test: Check that nested types like iterator
 * can be access even if type used to instanciate container is not
 * yet completely defined.
 */
class IncompleteClass
{
  vector<IncompleteClass> instances;
  typedef vector<IncompleteClass>::iterator it;
};
#endif

#if defined (STLPORT)
#  define NOTHROW _STLP_NOTHROW
#else
#  define NOTHROW throw()
#endif

/* This allocator implementation purpose is simply to break some
 * internal STLport mecanism specific to the STLport own allocator
 * implementation. */
template <class _Tp>
struct NotSTLportAllocator : public allocator<_Tp> {
  template <class _Tp1> struct rebind {
    typedef NotSTLportAllocator<_Tp1> other;
  };
  NotSTLportAllocator() NOTHROW {}
  template <class _Tp1> NotSTLportAllocator(const NotSTLportAllocator<_Tp1>&) NOTHROW {}
  NotSTLportAllocator(const NotSTLportAllocator<_Tp>&) NOTHROW {}
  ~NotSTLportAllocator() NOTHROW {}
};

/* This test check a potential issue with empty base class
 * optimization. Some compilers (VC6) do not implement it
 * correctly resulting ina wrong behavior. */
int EXAM_IMPL(vector_test::ebo)
{
  // We use heap memory as test failure can corrupt vector internal
  // representation making executable crash on vector destructor invocation.
  // We prefer a simple memory leak, internal corruption should be reveal
  // by size or capacity checks.
  typedef vector<int, NotSTLportAllocator<int> > V;
  V *pv1 = new V(1, 1);
  V *pv2 = new V(10, 2);

  size_t v1Capacity = pv1->capacity();
  size_t v2Capacity = pv2->capacity();

  pv1->swap(*pv2);

  EXAM_CHECK( pv1->size() == 10 );
  EXAM_CHECK( pv1->capacity() == v2Capacity );
  EXAM_CHECK( (*pv1)[5] == 2 );

  EXAM_CHECK( pv2->size() == 1 );
  EXAM_CHECK( pv2->capacity() == v1Capacity );
  EXAM_CHECK( (*pv2)[0] == 1 );

  delete pv2;
  delete pv1;

  return EXAM_RESULT;
}

int EXAM_IMPL(bvector_test::bvec1)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  bool ii[3]= {1,0,1};
  bit_vector b(3);

  EXAM_CHECK(b[0]==0);
  EXAM_CHECK(b[1]==0);
  EXAM_CHECK(b[2]==0);

  b[0] = b[2] = 1;

  EXAM_CHECK(b[0]==1);
  EXAM_CHECK(b[1]==0);
  EXAM_CHECK(b[2]==1);

  b.insert(b.begin(),(bool*)ii, ii+2);

  EXAM_CHECK(b[0]==1);
  EXAM_CHECK(b[1]==0);
  EXAM_CHECK(b[2]==1);
  EXAM_CHECK(b[3]==0);
  EXAM_CHECK(b[4]==1);

  bit_vector bb = b;
  if (bb != b)
    exit(1);

  b[0] |= 0;
  b[1] |= 0;
  b[2] |= 1;
  b[3] |= 1;
  EXAM_CHECK(!((b[0] != 1) || (b[1] != 0) || (b[2] != 1) || (b[3] != 1)));


  bb[0] &= 0;
  bb[1] &= 0;
  bb[2] &= 1;
  bb[3] &= 1;
  EXAM_CHECK(!((bb[0] != 0) || (bb[1] != 0) || (bb[2] != 1) || (bb[3] != 0)));
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

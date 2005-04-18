#include <vector>
#include <algorithm>
#include <vector>
#include <string>
#include <slist>
#include <list>
#include <deque>
//#include <iostream>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class MoveConstructorTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(MoveConstructorTest);
  CPPUNIT_TEST(move_construct_test);
  CPPUNIT_TEST(deque_test);
  CPPUNIT_TEST(vector_test);
  CPPUNIT_TEST(move_traits);
  CPPUNIT_TEST_SUITE_END();

protected:
  void move_construct_test();
  void deque_test();
  void vector_test();
  void move_traits();

  /*
  template <class _Container>
  void standard_test1(_Container const& ref_cont) {
    vector<_Container> vec_cont(1, ref_cont);
    typedef typename _Container::value_type value_type;
    value_type *pvalue = &(*vec_cont.front().begin());
    size_t cur_capacity= vec_cont.capacity();
    //force reallocation
    while (cur_capacity == vec_cont.capacity()) {
      vec_cont.push_back(ref_cont);
    }
    bool b=( (pvalue==(&(*vec_cont.front().begin()))) );
    CPPUNIT_ASSERT(b);
  }
  */
};

CPPUNIT_TEST_SUITE_REGISTRATION(MoveConstructorTest);

//
// tests implementation
//
void MoveConstructorTest::move_construct_test()
{
  //cout << "vector<vector<int>>";
  vector<int> const ref_vec(10, 0);
  vector<vector<int> > v_v_ints(1, ref_vec);

  int *pint = &(v_v_ints.front().front());

  size_t cur_capacity = v_v_ints.capacity();
  while (v_v_ints.capacity() <= cur_capacity) {
    v_v_ints.push_back(ref_vec);
  }

  //v_v_ints has been resized
  CPPUNIT_ASSERT((pint == &v_v_ints.front().front()));

  //cout << "vector<vector<int>>::erase";
  //We need at least 3 elements:
  while (v_v_ints.size() < 3) {
    v_v_ints.push_back(ref_vec);
  }

  //We erase the 2nd
  pint = &v_v_ints[2].front();
  v_v_ints.erase(v_v_ints.begin() + 1);
  CPPUNIT_ASSERT((pint == &v_v_ints[1].front()));

  //cout << "vector<string>";
  string const ref_str("ref string, big enough to be a dynamic one");
  vector<string> vec_strs(1, ref_str);

  char const* pstr = vec_strs.front().c_str();
  cur_capacity = vec_strs.capacity();
  while (vec_strs.capacity() <= cur_capacity) {
    vec_strs.push_back(ref_str);
  }

  //vec_str has been resized
  CPPUNIT_ASSERT((pstr == vec_strs.front().c_str()));

  //cout << "vector<string>::erase";
  //We need at least 3 elements:
  while (vec_strs.size() < 3) {
    vec_strs.push_back(ref_str);
  }

  //We erase the 2nd
  pstr = vec_strs[2].c_str();
  vec_strs.erase(vec_strs.begin() + 1);
  CPPUNIT_ASSERT((pstr == vec_strs[1].c_str()));

  //cout << "swap(vector<int>, vector<int>)";
  vector<int> elem1(10, 0), elem2(10, 0);
  int *p1 = &elem1.front();
  int *p2 = &elem2.front();
  swap(elem1, elem2);
  CPPUNIT_ASSERT(((p1 == &elem2.front()) && (p2 == &elem1.front())));

  {
    vector<bool> bit_vec(5, true);
    bit_vec.insert(bit_vec.end(), 5, false);
    vector<vector<bool> > v_v_bits(1, bit_vec);

    /*
     * This is a STLport specific test as we are using internal implementation
     * details to check that the move has been correctly handled. For other
     * STL implementation it is only a compile check.
     */
#ifdef STLPORT
#  if defined (_STLP_DEBUG)
    unsigned int *punit = v_v_bits.front().begin()._M_iterator._M_p;
#  else
    unsigned int *punit = v_v_bits.front().begin()._M_p;
#  endif
#endif

    size_t cur_capacity = v_v_bits.capacity();
    while (v_v_bits.capacity() <= cur_capacity) {
      v_v_bits.push_back(bit_vec);
    }

#ifdef STLPORT
    //v_v_bits has been resized
#  if defined (_STLP_DEBUG)
    CPPUNIT_ASSERT( punit == v_v_bits.front().begin()._M_iterator._M_p );
#  else
    CPPUNIT_ASSERT( punit == v_v_bits.front().begin()._M_p );
#  endif
#endif
  }

  // zero: don't like this kind of tests
  // because of template test function 
  // we should find another way to provide
  // move constructor testing...

/*
  standard_test1(list<int>(10));


  standard_test1(slist<int>(10));

  standard_test1(deque<int>(10));
*/

  /*
  int int_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  
  set<int> int_set(int_values, int_values + sizeof(in_values) / sizeof(int));
  standard_test1(int_set);
  
  multiset<int> int_multiset(int_values, int_values + sizeof(in_values) / sizeof(int));
  standard_test1(int_multiset);
  */

  /*
  CheckFullMoveSupport(string());
  CheckFullMoveSupport(vector<int>());
  CheckFullMoveSupport(deque<int>());
  CheckFullMoveSupport(list<int>());
  CheckFullMoveSupport(slist<int>());
  */
}

void MoveConstructorTest::deque_test()
{
  //Check the insert range method.
  //To the front:
  {
    deque<vector<int> > vect_deque;
    vector<int*> bufs;
    vect_deque.assign(3, vector<int>(10));
    bufs.push_back(&vect_deque[0].front());
    bufs.push_back(&vect_deque[1].front());
    bufs.push_back(&vect_deque[2].front());

    int nb_insert = 5;
    //Initialize to 1 to generate a front insertion:
    int pos = 1;
    while (nb_insert--) {
      vector<vector<int> > vect_vect(2, vector<int>(10));
      vect_deque.insert(vect_deque.begin() + pos, vect_vect.begin(), vect_vect.end());
      bufs.insert(bufs.begin() + pos, &vect_deque[pos].front());
      bufs.insert(bufs.begin() + pos + 1, &vect_deque[pos + 1].front());
      ++pos;
    }
    CPPUNIT_ASSERT( vect_deque.size() == 13 );
    for (int i = 0; i < 5; ++i) {
      CPPUNIT_ASSERT( bufs[i] == &vect_deque[i].front() );
      CPPUNIT_ASSERT( bufs[11 - i] == &vect_deque[11 - i].front() );
    }
  }

  //To the back
  {
    deque<vector<int> > vect_deque;
    vector<int*> bufs;
    vect_deque.assign(3, vector<int>(10));
    bufs.push_back(&vect_deque[0].front());
    bufs.push_back(&vect_deque[1].front());
    bufs.push_back(&vect_deque[2].front());

    int nb_insert = 5;
    //Initialize to 2 to generate a back insertion:
    int pos = 2;
    while (nb_insert--) {
      vector<vector<int> > vect_vect(2, vector<int>(10));
      vect_deque.insert(vect_deque.begin() + pos, vect_vect.begin(), vect_vect.end());
      bufs.insert(bufs.begin() + pos, &vect_deque[pos].front());
      bufs.insert(bufs.begin() + pos + 1, &vect_deque[pos + 1].front());
      ++pos;
    }
    CPPUNIT_ASSERT( vect_deque.size() == 13 );
    for (int i = 0; i < 5; ++i) {
      CPPUNIT_ASSERT( bufs[i + 1] == &vect_deque[i + 1].front() );
      CPPUNIT_ASSERT( bufs[12 - i] == &vect_deque[12 - i].front() );
    }
  }

  //Check the different erase methods.
  {
    deque<vector<int> > vect_deque;
    vect_deque.assign(20, vector<int>(10));
    deque<vector<int> >::iterator vdit(vect_deque.begin()), vditEnd(vect_deque.end());
    vector<int*> bufs;
    for (; vdit != vditEnd; ++vdit) {
      bufs.push_back(&vdit->front());
    }

    {
      // This check, repeated after each operation, check the deque consistency:
      deque<vector<int> >::iterator it = vect_deque.end() - 5;
      int nb_incr = 0;
      for (; it != vect_deque.end() && nb_incr <= 6; ++nb_incr, ++it) {}
      CPPUNIT_ASSERT( nb_incr == 5 );
    }

    {
      //erase in front:
      vect_deque.erase(vect_deque.begin() + 2);
      bufs.erase(bufs.begin() + 2);
      CPPUNIT_ASSERT( vect_deque.size() == 19 );
      deque<vector<int> >::iterator dit(vect_deque.begin()), ditEnd(vect_deque.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      deque<vector<int> >::iterator it = vect_deque.end() - 5;
      int nb_incr = 0;
      for (; it != vect_deque.end() && nb_incr <= 6; ++nb_incr, ++it) {}
      CPPUNIT_ASSERT( nb_incr == 5 );
    }

    {
      //erase in the back:
      vect_deque.erase(vect_deque.end() - 2);
      bufs.erase(bufs.end() - 2);
      CPPUNIT_ASSERT( vect_deque.size() == 18 );
      deque<vector<int> >::iterator dit(vect_deque.begin()), ditEnd(vect_deque.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      deque<vector<int> >::iterator it = vect_deque.end() - 5;
      int nb_incr = 0;
      for (; it != vect_deque.end() && nb_incr < 6; ++nb_incr, ++it) {}
      CPPUNIT_ASSERT( nb_incr == 5 );
    }

    {
      //range erase in front
      vect_deque.erase(vect_deque.begin() + 3, vect_deque.begin() + 5);
      bufs.erase(bufs.begin() + 3, bufs.begin() + 5);
      CPPUNIT_ASSERT( vect_deque.size() == 16 );
      deque<vector<int> >::iterator dit(vect_deque.begin()), ditEnd(vect_deque.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      deque<vector<int> >::iterator it = vect_deque.end() - 5;
      int nb_incr = 0;
      for (; it != vect_deque.end() && nb_incr <= 6; ++nb_incr, ++it) {}
      CPPUNIT_ASSERT( nb_incr == 5 );
    }

    {
      //range erase in back
      vect_deque.erase(vect_deque.end() - 5, vect_deque.end() - 3);
      bufs.erase(bufs.end() - 5, bufs.end() - 3);
      CPPUNIT_ASSERT( vect_deque.size() == 14 );
      deque<vector<int> >::iterator dit(vect_deque.begin()), ditEnd(vect_deque.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }
  }

  //Check the insert value(s)
  {
    deque<vector<int> > vect_deque;
    vect_deque.assign(20, vector<int>(10));
    deque<vector<int> >::iterator vdit(vect_deque.begin()), vditEnd(vect_deque.end());
    vector<int*> bufs;
    for (; vdit != vditEnd; ++vdit) {
      bufs.push_back(&vdit->front());
    }

    {
      //2 values in front:
      vect_deque.insert(vect_deque.begin() + 2, 2, vector<int>(10));
      bufs.insert(bufs.begin() + 2, &vect_deque[2].front());
      bufs.insert(bufs.begin() + 3, &vect_deque[3].front());
      CPPUNIT_ASSERT( vect_deque.size() == 22 );
      deque<vector<int> >::iterator dit(vect_deque.begin()), ditEnd(vect_deque.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      //2 values in back:
      vect_deque.insert(vect_deque.end() - 2, 2, vector<int>(10));
      bufs.insert(bufs.end() - 2, &vect_deque[20].front());
      bufs.insert(bufs.end() - 2, &vect_deque[21].front());
      CPPUNIT_ASSERT( vect_deque.size() == 24 );
      deque<vector<int> >::iterator dit(vect_deque.begin()), ditEnd(vect_deque.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      //1 value in front:
      deque<vector<int> >::iterator ret;
      ret = vect_deque.insert(vect_deque.begin() + 2, vector<int>(10));
      bufs.insert(bufs.begin() + 2, &vect_deque[2].front());
      CPPUNIT_ASSERT( vect_deque.size() == 25 );
      CPPUNIT_ASSERT( &ret->front() == bufs[2] );
      deque<vector<int> >::iterator dit(vect_deque.begin()), ditEnd(vect_deque.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      //1 value in back:
      deque<vector<int> >::iterator ret;
      ret = vect_deque.insert(vect_deque.end() - 2, vector<int>(10));
      bufs.insert(bufs.end() - 2, &vect_deque[23].front());
      CPPUNIT_ASSERT( vect_deque.size() == 26 );
      CPPUNIT_ASSERT( &ret->front() == bufs[23] );
      deque<vector<int> >::iterator dit(vect_deque.begin()), ditEnd(vect_deque.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }
  }
}

void MoveConstructorTest::vector_test()
{
  //Check the insert range method.
  //To the front:
  {
    vector<vector<int> > vect_vector;
    vector<int*> bufs;
    vect_vector.assign(3, vector<int>(10));
    bufs.push_back(&vect_vector[0].front());
    bufs.push_back(&vect_vector[1].front());
    bufs.push_back(&vect_vector[2].front());

    int nb_insert = 5;
    int pos = 1;
    while (nb_insert--) {
      vector<vector<int> > vect_vect(2, vector<int>(10));
      vect_vector.insert(vect_vector.begin() + pos, vect_vect.begin(), vect_vect.end());
      bufs.insert(bufs.begin() + pos, &vect_vector[pos].front());
      bufs.insert(bufs.begin() + pos + 1, &vect_vector[pos + 1].front());
      ++pos;
    }
    CPPUNIT_ASSERT( vect_vector.size() == 13 );
    for (int i = 0; i < 5; ++i) {
      CPPUNIT_ASSERT( bufs[i] == &vect_vector[i].front() );
      CPPUNIT_ASSERT( bufs[11 - i] == &vect_vector[11 - i].front() );
    }
  }

  //To the back
  {
    vector<vector<int> > vect_vector;
    vector<int*> bufs;
    vect_vector.assign(3, vector<int>(10));
    bufs.push_back(&vect_vector[0].front());
    bufs.push_back(&vect_vector[1].front());
    bufs.push_back(&vect_vector[2].front());

    int nb_insert = 5;
    //Initialize to 2 to generate a back insertion:
    int pos = 2;
    while (nb_insert--) {
      vector<vector<int> > vect_vect(2, vector<int>(10));
      vect_vector.insert(vect_vector.begin() + pos, vect_vect.begin(), vect_vect.end());
      bufs.insert(bufs.begin() + pos, &vect_vector[pos].front());
      bufs.insert(bufs.begin() + pos + 1, &vect_vector[pos + 1].front());
      ++pos;
    }
    CPPUNIT_ASSERT( vect_vector.size() == 13 );
    for (int i = 0; i < 5; ++i) {
      CPPUNIT_ASSERT( bufs[i + 1] == &vect_vector[i + 1].front() );
      CPPUNIT_ASSERT( bufs[12 - i] == &vect_vector[12 - i].front() );
    }
  }

  //Check the different erase methods.
  {
    vector<vector<int> > vect_vector;
    vect_vector.assign(20, vector<int>(10));
    vector<vector<int> >::iterator vdit(vect_vector.begin()), vditEnd(vect_vector.end());
    vector<int*> bufs;
    for (; vdit != vditEnd; ++vdit) {
      bufs.push_back(&vdit->front());
    }

    {
      // This check, repeated after each operation, check the vector consistency:
      vector<vector<int> >::iterator it = vect_vector.end() - 5;
      int nb_incr = 0;
      for (; it != vect_vector.end() && nb_incr <= 6; ++nb_incr, ++it) {}
      CPPUNIT_ASSERT( nb_incr == 5 );
    }

    {
      //erase in front:
      vect_vector.erase(vect_vector.begin() + 2);
      bufs.erase(bufs.begin() + 2);
      CPPUNIT_ASSERT( vect_vector.size() == 19 );
      vector<vector<int> >::iterator dit(vect_vector.begin()), ditEnd(vect_vector.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      vector<vector<int> >::iterator it = vect_vector.end() - 5;
      int nb_incr = 0;
      for (; it != vect_vector.end() && nb_incr <= 6; ++nb_incr, ++it) {}
      CPPUNIT_ASSERT( nb_incr == 5 );
    }

    {
      //erase in the back:
      vect_vector.erase(vect_vector.end() - 2);
      bufs.erase(bufs.end() - 2);
      CPPUNIT_ASSERT( vect_vector.size() == 18 );
      vector<vector<int> >::iterator dit(vect_vector.begin()), ditEnd(vect_vector.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      vector<vector<int> >::iterator it = vect_vector.end() - 5;
      int nb_incr = 0;
      for (; it != vect_vector.end() && nb_incr < 6; ++nb_incr, ++it) {}
      CPPUNIT_ASSERT( nb_incr == 5 );
    }

    {
      //range erase in front
      vect_vector.erase(vect_vector.begin() + 3, vect_vector.begin() + 5);
      bufs.erase(bufs.begin() + 3, bufs.begin() + 5);
      CPPUNIT_ASSERT( vect_vector.size() == 16 );
      vector<vector<int> >::iterator dit(vect_vector.begin()), ditEnd(vect_vector.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      vector<vector<int> >::iterator it = vect_vector.end() - 5;
      int nb_incr = 0;
      for (; it != vect_vector.end() && nb_incr <= 6; ++nb_incr, ++it) {}
      CPPUNIT_ASSERT( nb_incr == 5 );
    }

    {
      //range erase in back
      vect_vector.erase(vect_vector.end() - 5, vect_vector.end() - 3);
      bufs.erase(bufs.end() - 5, bufs.end() - 3);
      CPPUNIT_ASSERT( vect_vector.size() == 14 );
      vector<vector<int> >::iterator dit(vect_vector.begin()), ditEnd(vect_vector.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }
  }

  //Check the insert value(s)
  {
    vector<vector<int> > vect_vector;
    vect_vector.assign(20, vector<int>(10));
    vector<vector<int> >::iterator vdit(vect_vector.begin()), vditEnd(vect_vector.end());
    vector<int*> bufs;
    for (; vdit != vditEnd; ++vdit) {
      bufs.push_back(&vdit->front());
    }

    {
      //2 values in front:
      vect_vector.insert(vect_vector.begin() + 2, 2, vector<int>(10));
      bufs.insert(bufs.begin() + 2, &vect_vector[2].front());
      bufs.insert(bufs.begin() + 3, &vect_vector[3].front());
      CPPUNIT_ASSERT( vect_vector.size() == 22 );
      vector<vector<int> >::iterator dit(vect_vector.begin()), ditEnd(vect_vector.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      //2 values in back:
      vect_vector.insert(vect_vector.end() - 2, 2, vector<int>(10));
      bufs.insert(bufs.end() - 2, &vect_vector[20].front());
      bufs.insert(bufs.end() - 2, &vect_vector[21].front());
      CPPUNIT_ASSERT( vect_vector.size() == 24 );
      vector<vector<int> >::iterator dit(vect_vector.begin()), ditEnd(vect_vector.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      //1 value in front:
      vector<vector<int> >::iterator ret;
      ret = vect_vector.insert(vect_vector.begin() + 2, vector<int>(10));
      bufs.insert(bufs.begin() + 2, &vect_vector[2].front());
      CPPUNIT_ASSERT( vect_vector.size() == 25 );
      CPPUNIT_ASSERT( &ret->front() == bufs[2] );
      vector<vector<int> >::iterator dit(vect_vector.begin()), ditEnd(vect_vector.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }

    {
      //1 value in back:
      vector<vector<int> >::iterator ret;
      ret = vect_vector.insert(vect_vector.end() - 2, vector<int>(10));
      bufs.insert(bufs.end() - 2, &vect_vector[23].front());
      CPPUNIT_ASSERT( vect_vector.size() == 26 );
      CPPUNIT_ASSERT( &ret->front() == bufs[23] );
      vector<vector<int> >::iterator dit(vect_vector.begin()), ditEnd(vect_vector.end());
      for (size_t i = 0; dit != ditEnd; ++dit, ++i) {
        CPPUNIT_ASSERT( bufs[i] == &dit->front() );
      }
    }
  }
}

#ifdef STLPORT
struct MovableStruct {
  MovableStruct() {
    ++nb_dft_construct_call;
  }
  MovableStruct(MovableStruct const&) {
    ++nb_cpy_construct_call;
  }
  MovableStruct(__move_source<MovableStruct>) {
    ++nb_mv_construct_call;
  }

  ~MovableStruct() {
    ++nb_destruct_call;
  }

  static unsigned int nb_dft_construct_call;
  static unsigned int nb_cpy_construct_call;
  static unsigned int nb_mv_construct_call;
  static unsigned int nb_destruct_call;
};

unsigned int MovableStruct::nb_dft_construct_call = 0;
unsigned int MovableStruct::nb_cpy_construct_call = 0;
unsigned int MovableStruct::nb_mv_construct_call = 0;
unsigned int MovableStruct::nb_destruct_call = 0;

namespace std {
  _STLP_TEMPLATE_NULL
  struct __move_traits<MovableStruct> {
    typedef __true_type implemented;
    typedef __false_type complete;
  };
}

struct CompleteMovableStruct {
  CompleteMovableStruct() {
    ++nb_dft_construct_call;
  }
  CompleteMovableStruct(CompleteMovableStruct const&) {
    ++nb_cpy_construct_call;
  }
  CompleteMovableStruct(__move_source<CompleteMovableStruct>) {
    ++nb_mv_construct_call;
  }

  ~CompleteMovableStruct() {
    ++nb_destruct_call;
  }

  static unsigned int nb_dft_construct_call;
  static unsigned int nb_cpy_construct_call;
  static unsigned int nb_mv_construct_call;
  static unsigned int nb_destruct_call;
};

unsigned int CompleteMovableStruct::nb_dft_construct_call = 0;
unsigned int CompleteMovableStruct::nb_cpy_construct_call = 0;
unsigned int CompleteMovableStruct::nb_mv_construct_call = 0;
unsigned int CompleteMovableStruct::nb_destruct_call = 0;

namespace std {
  _STLP_TEMPLATE_NULL
  struct __move_traits<CompleteMovableStruct> {
    typedef __true_type implemented;
    typedef __true_type complete;
  };
}
#endif //STLPORT

void MoveConstructorTest::move_traits()
{
  //Only relevant for an STLport test:
#ifdef STLPORT
  {
    {
      vector<MovableStruct> vect;
      vect.push_back(MovableStruct());
      vect.push_back(MovableStruct());
      vect.push_back(MovableStruct());
      vect.push_back(MovableStruct());

      // vect contains 4 elements
      CPPUNIT_ASSERT( MovableStruct::nb_dft_construct_call == 4 );
      CPPUNIT_ASSERT( MovableStruct::nb_cpy_construct_call == 4 );
      CPPUNIT_ASSERT( MovableStruct::nb_mv_construct_call == 3 );
      CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 7 );

      // Following test violate requirements to sequiences (23.1.1 Table 67)
      /*
      vect.insert(vect.begin() + 2, vect.begin(), vect.end());
      // vect contains 8 elements
      CPPUNIT_ASSERT( MovableStruct::nb_dft_construct_call == 4 );
      CPPUNIT_ASSERT( MovableStruct::nb_cpy_construct_call == 8 );
      CPPUNIT_ASSERT( MovableStruct::nb_mv_construct_call == 7 );
      CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 11 );
      */

      vector<MovableStruct> v2 = vect;
      CPPUNIT_ASSERT( MovableStruct::nb_dft_construct_call == 4 );
      CPPUNIT_ASSERT( MovableStruct::nb_cpy_construct_call == 8 );
      CPPUNIT_ASSERT( MovableStruct::nb_mv_construct_call == 3 );
      CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 7 );

      vect.insert(vect.begin() + 2, v2.begin(), v2.end() );

      // vect contains 8 elements
      CPPUNIT_ASSERT( MovableStruct::nb_dft_construct_call == 4 );
      CPPUNIT_ASSERT( MovableStruct::nb_cpy_construct_call == 12 );
      CPPUNIT_ASSERT( MovableStruct::nb_mv_construct_call == 7 );
      CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 11 );

      vect.erase(vect.begin(), vect.begin() + 2 );

      // vect contains 6 elements
      CPPUNIT_ASSERT( MovableStruct::nb_mv_construct_call == 13 );
      CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 19 );

      vect.erase(vect.begin());

      // vect contains 5 elements
      CPPUNIT_ASSERT( MovableStruct::nb_mv_construct_call == 18 );
      CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 25 );
    }
    // CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 30 );
    CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 34 );
  }

  {
    {
      vector<CompleteMovableStruct> vect;
      vect.push_back(CompleteMovableStruct());
      vect.push_back(CompleteMovableStruct());
      vect.push_back(CompleteMovableStruct());
      vect.push_back(CompleteMovableStruct());

      // vect contains 4 elements
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_dft_construct_call == 4 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_cpy_construct_call == 4 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_mv_construct_call == 3 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 4 );

      // Following test violate requirements to sequiences (23.1.1 Table 67)
      /*
      vect.insert(vect.begin() + 2, vect.begin(), vect.end());

      // vect contains 8 elements
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_dft_construct_call == 4 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_cpy_construct_call == 8 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_mv_construct_call == 7 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 4 );
      */

      vector<CompleteMovableStruct> v2 = vect;

      vect.insert(vect.begin() + 2, v2.begin(), v2.end());

      // vect contains 8 elements
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_dft_construct_call == 4 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_cpy_construct_call == 12 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_mv_construct_call == 7 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 4 );

      vect.erase(vect.begin(), vect.begin() + 2);

      // vect contains 6 elements
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_mv_construct_call == 13 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 6 );

      vect.erase(vect.begin());

      // vect contains 5 elements
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_mv_construct_call == 18 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 7 );
    }
    //CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 12 );
    CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 16 );
  }
#endif //STLPORT
}

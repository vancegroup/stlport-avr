#include <vector>
#include <algorithm>
#include <vector>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class SwapTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(SwapTest);
  CPPUNIT_TEST(swap1);
  CPPUNIT_TEST(swprnge1);
#if defined (STLPORT) && \
   !defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER) && !defined (_STLP_USE_PARTIAL_SPEC_WORKAROUND)
  CPPUNIT_IGNORE;
#endif
  CPPUNIT_TEST(swap_container);
  CPPUNIT_TEST_SUITE_END();

protected:
  void swap1();
  void swprnge1();
  void swap_container();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SwapTest);

//
// tests implementation
//
void SwapTest::swap1()
{
  int a = 42;
  int b = 19;
  swap(a, b);

  CPPUNIT_ASSERT(a==19);
  CPPUNIT_ASSERT(b==42);
}

void SwapTest::swprnge1()
{
  char word1[] = "World";
  char word2[] = "Hello";
  swap_ranges((char*)word1, (char*)word1 + ::strlen(word1), (char*)word2);
  CPPUNIT_ASSERT(!strcmp(word1, "Hello"));
  CPPUNIT_ASSERT(!strcmp(word2, "World"));
}

class Obj
{
  public:
    Obj() :
        v( 0 )
      { }
    Obj( const Obj& ) :
        v( 1 )
      { }

    Obj& operator =( const Obj& )
      { v = 2; return *this; }

    int v;
};

void SwapTest::swap_container()
{
#if !defined (STLPORT) || \
     defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER) || defined (_STLP_USE_PARTIAL_SPEC_WORKAROUND)
  vector<Obj> v1;
  vector<Obj> v2;

  v1.push_back( Obj() );
  v1.push_back( Obj() );

  v1[0].v = -1;
  v1[1].v = -2;

  v2.push_back( Obj() );
  v2.push_back( Obj() );
  v2.push_back( Obj() );

  v2[0].v = 10;
  v2[1].v = 11;
  v2[2].v = 12;

  swap( v1, v2 ); // this should has effect v1.swap( v2 )

  CPPUNIT_CHECK( v1.size() == 3 );
  CPPUNIT_CHECK( v2.size() == 2 );

  CPPUNIT_CHECK( v1[0].v == 10 );
  CPPUNIT_CHECK( v1[1].v == 11 );
  CPPUNIT_CHECK( v1[2].v == 12 );

  CPPUNIT_CHECK( v2[0].v == -1 );
  CPPUNIT_CHECK( v2[1].v == -2 );
#endif
}

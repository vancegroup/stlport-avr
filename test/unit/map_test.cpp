#include <map>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class MapTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(MapTest);
  CPPUNIT_TEST(map1);
  CPPUNIT_TEST(mmap1);
  CPPUNIT_TEST(mmap2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void map1();
  void mmap1();
  void mmap2();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MapTest);

//
// tests implementation
//
void MapTest::map1()
{
  typedef map<char, int, less<char> > maptype;
  maptype m;
  // Store mappings between roman numerals and decimals.
  m['l'] = 50;
  m['x'] = 20; // Deliberate mistake.
  m['v'] = 5;
  m['i'] = 1;
//  cout << "m['x'] = " << m['x'] << endl;
  CPPUNIT_ASSERT( m['x']==20 );
  m['x'] = 10; // Correct mistake.
  CPPUNIT_ASSERT( m['x']==10 );
  CPPUNIT_ASSERT( m['z']==0 );
  //cout << "m['z'] = " << m['z'] << endl; // Note default value is added.
  CPPUNIT_ASSERT( m.count('z')==1 );
  //cout << "m.count('z') = " << m.count('z') << endl;
  pair<maptype::iterator, bool> p = m.insert(pair<const char, int>('c', 100));
  CPPUNIT_ASSERT(p.second);

  p = m.insert(pair<const char, int>('c', 100));
  CPPUNIT_ASSERT(!p.second); // already existing pair
}
void MapTest::mmap1()
{
  typedef multimap<char, int, less<char> > mmap;
  mmap m;
  CPPUNIT_ASSERT(m.count('X')==0);

  m.insert(pair<const char, int>('X', 10)); // Standard way.
  CPPUNIT_ASSERT(m.count('X')==1);

  m.insert(pair<const char, int>('X', 20));	// jbuck: standard way
  CPPUNIT_ASSERT(m.count('X')==2);

  m.insert(pair<const char, int>('Y', 32));	// jbuck: standard way
  mmap::iterator i = m.find('X'); // Find first match.
  CPPUNIT_ASSERT((*i).first=='X');
  CPPUNIT_ASSERT((*i).second==10);
  i++;
  CPPUNIT_ASSERT((*i).first=='X');
  CPPUNIT_ASSERT((*i).second==20);
  i++;
  CPPUNIT_ASSERT((*i).first=='Y');
  CPPUNIT_ASSERT((*i).second==32);
  i++;
  CPPUNIT_ASSERT(i==m.end());

  int count = m.erase('X');
  CPPUNIT_ASSERT(count==2);
}
void MapTest::mmap2()
{
  typedef pair<const int, char> pair_type;

  pair_type p1(3, 'c');
  pair_type p2(6, 'f');
  pair_type p3(1, 'a');
  pair_type p4(2, 'b');
  pair_type p5(3, 'x');
  pair_type p6(6, 'f');

  typedef multimap<int, char, less<int> > mmap;

  pair_type array [] =
  {
    p1,
    p2,
    p3,
    p4,
    p5,
    p6
  };

  mmap m(array+0, array + 6);
  mmap::iterator i;
  i = m.lower_bound(3);
  CPPUNIT_ASSERT((*i).first==3);
  CPPUNIT_ASSERT((*i).second=='c');

  i = m.upper_bound(3);
  CPPUNIT_ASSERT((*i).first==6);
  CPPUNIT_ASSERT((*i).second=='f');
}

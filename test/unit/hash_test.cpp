#include <vector>
#include <algorithm>
#include <hash_map>
#include <hash_set>
#include <rope>

#include "cppunit/cppunit_proxy.h"

#if defined (__MVS__)
  #define star   92 
#else
  #define star   42
#endif

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class HashTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(HashTest);
  CPPUNIT_TEST(hmap1);
  CPPUNIT_TEST(hmmap1);
  CPPUNIT_TEST(hmset1);
  CPPUNIT_TEST(hset2);
  CPPUNIT_TEST_SUITE_END();

  typedef hash_multiset<char, hash<char>, equal_to<char> > hmset;

protected:
  void hmap1();
  void hmmap1();
  void hmset1();
  void hset2();
};

CPPUNIT_TEST_SUITE_REGISTRATION(HashTest);

//
// tests implementation
//
void HashTest::hmap1()
{
  typedef hash_map<char, crope, hash<char>, equal_to<char> > maptype;
  maptype m;
  // Store mappings between roman numerals and decimals.
  m['l'] = "50";
  m['x'] = "20"; // Deliberate mistake.
  m['v'] = "5";
  m['i'] = "1";
  CPPUNIT_ASSERT( !strcmp(m['x'].c_str(),"20") );
  m['x'] = "10"; // Correct mistake.
  CPPUNIT_ASSERT( !strcmp(m['x'].c_str(),"10") );
  
  CPPUNIT_ASSERT( !strcmp(m['z'].c_str(),"") );
  
  CPPUNIT_ASSERT( m.count('z')==1 );
  pair<maptype::iterator, bool> p =m.insert(pair<const char, crope>('c', crope("100")));
  
  CPPUNIT_ASSERT(p.second);

  p = m.insert(pair<const char, crope>('c', crope("100")));
  CPPUNIT_ASSERT(!p.second);
}
void HashTest::hmmap1()
{
  typedef hash_multimap<char, int, hash<char>,equal_to<char> > mmap;
  mmap m;
  CPPUNIT_ASSERT(m.count('X')==0);
  m.insert(pair<const char,int>('X', 10)); // Standard way.
  CPPUNIT_ASSERT(m.count('X')==1);
//  m.insert('X', 20); // Non-standard, but very convenient!
  m.insert(pair<const char,int>('X', 20));	// jbuck: standard way
  CPPUNIT_ASSERT(m.count('X')==2);
//  m.insert('Y', 32);
  m.insert(pair<const char,int>('Y', 32));	// jbuck: standard way
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
void HashTest::hmset1()
{
  hmset s;
  CPPUNIT_ASSERT(s.count(star)==0);
  s.insert(star);
  CPPUNIT_ASSERT(s.count(star)==1);
  s.insert(star);
  CPPUNIT_ASSERT(s.count(star)==2);
  hmset::iterator i = s.find(40);
  CPPUNIT_ASSERT(i == s.end());

  i = s.find(star);
  CPPUNIT_ASSERT(i != s.end())
  CPPUNIT_ASSERT(*i=='*');
  int count = s.erase(star);
  CPPUNIT_ASSERT(count==2);
}
void HashTest::hset2()
{
  hash_set<int, hash<int>, equal_to<int> > s;
  pair<std::hash_set<int, hash<int>, equal_to<int> >::const_iterator, bool> p = s.insert(42);
  CPPUNIT_ASSERT(p.second);
  CPPUNIT_ASSERT(*(p.first)==42);

  p = s.insert(42);
  CPPUNIT_ASSERT(!p.second);
}

#include <list>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class ListTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(ListTest);
  CPPUNIT_TEST(list1);
  CPPUNIT_TEST(list2);
  CPPUNIT_TEST(list3);
  CPPUNIT_TEST(list4);
  CPPUNIT_TEST_SUITE_END();

protected:
  void list1();
  void list2();
  void list3();
  void list4();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ListTest);

//
// tests implementation
//
void ListTest::list1()
{
  int array1 [] = { 9, 16, 36 };
  int array2 [] = { 1, 4 };

  list<int> l1(array1, array1 + 3);
  list<int> l2(array2, array2 + 2);
  std::list<int>::iterator i1 = l1.begin();
  std::list<int>::const_iterator ci(i1);
  std::list<int>::const_iterator ci1(ci);
  l1.splice(i1, l2);
  std::list<int>::iterator i2 = l1.begin();
  CPPUNIT_ASSERT(*i2++==1);
  CPPUNIT_ASSERT(*i2++==4);
  CPPUNIT_ASSERT(*i2++==9);
  CPPUNIT_ASSERT(*i2++==16);
  CPPUNIT_ASSERT(*i2++==36);
}
void ListTest::list2()
{
  int array1 [] = { 1, 16 };
  int array2 [] = { 4, 9 };

  list<int> l1(array1, array1 + 2);
  list<int> l2(array2, array2 + 2);
  std::list<int>::iterator i = l1.begin();
  i++;
  l1.splice(i, l2, l2.begin(), l2.end());
  i = l1.begin();
  CPPUNIT_ASSERT(*i++==1);
  CPPUNIT_ASSERT(*i++==4);
  CPPUNIT_ASSERT(*i++==9);
  CPPUNIT_ASSERT(*i++==16);
}
void ListTest::list3()
{
  char array [] = { 'x', 'l', 'x', 't', 's', 's' };

  list<char> str(array, array + 6);
  std::list<char>::iterator i;

  str.reverse();
  i = str.begin();
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='t');
  CPPUNIT_ASSERT(*i++=='x');
  CPPUNIT_ASSERT(*i++=='l');
  CPPUNIT_ASSERT(*i++=='x');

  str.remove('x');
  i = str.begin();
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='t');
  CPPUNIT_ASSERT(*i++=='l');

  str.unique();
  i = str.begin();
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='t');
  CPPUNIT_ASSERT(*i++=='l');

  str.sort();
  i = str.begin();
  CPPUNIT_ASSERT(*i++=='l');
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='t');
}
void ListTest::list4()
{
  int array1 [] = { 1, 3, 6, 7 };
  int array2 [] = { 2, 4 };

  list<int> l1(array1, array1 + 4);
  list<int> l2(array2, array2 + 2);
  l1.merge(l2);
  std::list<int>::iterator i = l1.begin();
  CPPUNIT_ASSERT(*i++==1);
  CPPUNIT_ASSERT(*i++==2);
  CPPUNIT_ASSERT(*i++==3);
  CPPUNIT_ASSERT(*i++==4);
  CPPUNIT_ASSERT(*i++==6);
  CPPUNIT_ASSERT(*i++==7);

  //We use distance to avoid a simple call to an internal counter
  CPPUNIT_ASSERT(distance(l1.begin(), l1.end()) == 6);
  CPPUNIT_ASSERT(distance(l2.begin(), l2.end()) == 0);

  l1.swap(l2);
  
  CPPUNIT_ASSERT(distance(l1.begin(), l1.end()) == 0);
  CPPUNIT_ASSERT(distance(l2.begin(), l2.end()) == 6);
}

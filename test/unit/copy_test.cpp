#include <algorithm>
#include <cstring>
#include <sstream>
#include <vector>
#include <iterator>
#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class CopyTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(CopyTest);
  CPPUNIT_TEST(copy1);
  CPPUNIT_TEST(copy2);
  CPPUNIT_TEST(copy3);
  CPPUNIT_TEST(copy4);
  CPPUNIT_TEST(copyb);
  CPPUNIT_TEST(copyb0);
  CPPUNIT_TEST_SUITE_END();

protected:
  void copy1();
  void copy2();
  void copy3();
  void copy4();
  void copyb();
  void copyb0();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CopyTest);

//
// tests implementation
//
void CopyTest::copy1()
{
  char string[23] = "A string to be copied.";
  char result[23];
  copy(string, string + 23, result);
  CPPUNIT_ASSERT(!strncmp(string, result, 23));
}
void CopyTest::copy2()
{
  vector <int> v(10);
  for(size_t i = 0; i < v.size(); i++)
    v[i] = i;
  
  ostringstream os;
  ostream_iterator<int> iter(os, " ");
  copy(v.begin(), v.end(), iter);
  string result = os.str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(),"0 1 2 3 4 5 6 7 8 9 "));
}
void CopyTest::copy3()
{
  vector <int> v1(10);
  for(size_t i = 0; i < v1.size(); i++)
    v1[i] = i;

  vector <int> v2(10);
  copy(v1.begin(), v1.end(), v2.begin());

  ostringstream os;
  ostream_iterator<int> iter(os, " ");
  copy(v2.begin(), v2.end(), iter);
  string result = os.str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(),"0 1 2 3 4 5 6 7 8 9 "));
}
void CopyTest::copy4()
{
  typedef vector<int> IVec;
  vector<int> v1(10);
  for(size_t loc = 0; loc < v1.size(); loc++)
    v1[loc] = loc;
  vector<int> v2;
  insert_iterator<IVec> i(v2, v2.begin());
  copy(v1.begin(), v1.end(), i);

  ostringstream os;
  ostream_iterator<int> outIter(os, " ");
  copy(v2.begin(), v2.end(), outIter);
  string result = os.str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(),"0 1 2 3 4 5 6 7 8 9 "));
}
void CopyTest::copyb()
{
  vector <int> v1(10);
  for(size_t i = 0; i < v1.size(); i++)
    v1[i] = i;
  vector <int> v2(v1.size());
  copy_backward(v1.begin(), v1.end(), v2.end());

  ostringstream os;
  ostream_iterator<int> iter(os, " ");
  copy(v2.begin(), v2.end(), iter);
  string result = os.str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(),"0 1 2 3 4 5 6 7 8 9 "));
}
void CopyTest::copyb0()
{
  int numbers[5] = { 1, 2, 3, 4, 5 };

  int result[5];
  copy_backward(numbers, numbers + 5, (int*)result + 5);
  CPPUNIT_ASSERT(result[0]==numbers[0]);
  CPPUNIT_ASSERT(result[1]==numbers[1]);
  CPPUNIT_ASSERT(result[2]==numbers[2]);
  CPPUNIT_ASSERT(result[3]==numbers[3]);
  CPPUNIT_ASSERT(result[4]==numbers[4]);
}

#include <vector>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class SortTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(SortTest);
  CPPUNIT_TEST(sort1);
  CPPUNIT_TEST(sort2);
  CPPUNIT_TEST(stblsrt1);
  CPPUNIT_TEST(stblsrt2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void sort1();
  void sort2();
  void stblsrt1();
  void stblsrt2();

  static bool string_less(const char* a_, const char* b_)
  {
    return strcmp(a_, b_) < 0 ? 1 : 0;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(SortTest);

//
// tests implementation
//
void SortTest::stblsrt1()
{
  int array[6] = { 1, 50, -10, 11, 42, 19 };
  stable_sort(array, array + 6);
//-10 1 11 19 42 50 
  CPPUNIT_ASSERT(array[0]==-10);
  CPPUNIT_ASSERT(array[1]==1);
  CPPUNIT_ASSERT(array[2]==11);
  CPPUNIT_ASSERT(array[3]==19);
  CPPUNIT_ASSERT(array[4]==42);
  CPPUNIT_ASSERT(array[5]==50);
}
void SortTest::stblsrt2()
{
  char* letters[6] = {"bb", "aa", "ll", "dd", "qq", "cc" };

  stable_sort(letters, letters + 6, string_less);
  // aa bb cc dd ll qq 
  CPPUNIT_ASSERT(letters[0]=="aa");
  CPPUNIT_ASSERT(letters[1]=="bb");
  CPPUNIT_ASSERT(letters[2]=="cc");
  CPPUNIT_ASSERT(letters[3]=="dd");
  CPPUNIT_ASSERT(letters[4]=="ll");
  CPPUNIT_ASSERT(letters[5]=="qq");
}
void SortTest::sort1()
{
  int array[6] = { 1, 50, -10, 11, 42, 19 };

  sort(array, array + 6);
  // -10 1 11 19 42 50  
  CPPUNIT_ASSERT(array[0]==-10);
  CPPUNIT_ASSERT(array[1]==1);
  CPPUNIT_ASSERT(array[2]==11);
  CPPUNIT_ASSERT(array[3]==19);
  CPPUNIT_ASSERT(array[4]==42);
  CPPUNIT_ASSERT(array[5]==50);
}
void SortTest::sort2()
{
  int array[] = { 1, 50, -10, 11, 42, 19 };

  int count = sizeof(array) / sizeof(array[0]);
  sort(array, array + count, greater<int>());

  //  50 42 19 11 1 -10 
  CPPUNIT_ASSERT(array[5]==-10);
  CPPUNIT_ASSERT(array[4]==1);
  CPPUNIT_ASSERT(array[3]==11);
  CPPUNIT_ASSERT(array[2]==19);
  CPPUNIT_ASSERT(array[1]==42);
  CPPUNIT_ASSERT(array[0]==50);
}

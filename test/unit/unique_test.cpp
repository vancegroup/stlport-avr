#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class UniqueTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(UniqueTest);
  CPPUNIT_TEST(uniqcpy1);
  CPPUNIT_TEST(uniqcpy2);
  CPPUNIT_TEST(unique1);
  CPPUNIT_TEST(unique2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void uniqcpy1();
  void uniqcpy2();
  void unique1();
  void unique2();
  
  static bool str_equal(const char* a_, const char* b_)
  {
    return strcmp(a_, b_) == 0 ? 1 : 0;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(UniqueTest);

//
// tests implementation
//
void UniqueTest::unique1()
{
  int numbers[8] = { 0, 1, 1, 2, 2, 2, 3, 4 };
  unique((int*)numbers, (int*)numbers + 8);
  // 0 1 2 3 4 2 3 4 
  CPPUNIT_ASSERT(numbers[0]==0);
  CPPUNIT_ASSERT(numbers[1]==1);
  CPPUNIT_ASSERT(numbers[2]==2);
  CPPUNIT_ASSERT(numbers[3]==3);
  CPPUNIT_ASSERT(numbers[4]==4);
  CPPUNIT_ASSERT(numbers[5]==2);
  CPPUNIT_ASSERT(numbers[6]==3);
  CPPUNIT_ASSERT(numbers[7]==4);
}
void UniqueTest::unique2()
{

  char* labels[] = { "Q","Q","W","W","E","E","R","T","T","Y","Y" };

  const unsigned count = sizeof(labels) / sizeof(labels[0]);

  unique((char**)labels, (char**)labels + count, str_equal);

  // QWERTYRTTYY
  CPPUNIT_ASSERT(!strcmp(labels[0], "Q"));
  CPPUNIT_ASSERT(!strcmp(labels[1], "W"));
  CPPUNIT_ASSERT(!strcmp(labels[2], "E"));
  CPPUNIT_ASSERT(!strcmp(labels[3], "R"));
  CPPUNIT_ASSERT(!strcmp(labels[4], "T"));
  CPPUNIT_ASSERT(!strcmp(labels[5], "Y"));

}
void UniqueTest::uniqcpy1()
{
  int numbers[8] = { 0, 1, 1, 2, 2, 2, 3, 4 };
  int result[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

  unique_copy((int*)numbers, (int*)numbers + 8, (int*)result);
  // 0 1 2 3 4 0 0 0 
  CPPUNIT_ASSERT(result[0]==0);
  CPPUNIT_ASSERT(result[1]==1);
  CPPUNIT_ASSERT(result[2]==2);
  CPPUNIT_ASSERT(result[3]==3);
  CPPUNIT_ASSERT(result[4]==4);
  CPPUNIT_ASSERT(result[5]==0);
  CPPUNIT_ASSERT(result[6]==0);
  CPPUNIT_ASSERT(result[7]==0);
}
void UniqueTest::uniqcpy2()
{
#ifndef UNDER_CE
  char* labels[] = { "Q","Q","W","W","E","E","R","T","T","Y","Y" };

  const unsigned count = sizeof(labels) / sizeof(labels[0]);
  char* uCopy[count];
  fill((char**)uCopy, (char**)uCopy + count, (char*)"");
  
  unique_copy((char**)labels, (char**)labels + count, (char**)uCopy, str_equal);

  CPPUNIT_ASSERT(!strcmp(uCopy[0], "Q"));
  CPPUNIT_ASSERT(!strcmp(uCopy[1], "W"));
  CPPUNIT_ASSERT(!strcmp(uCopy[2], "E"));
  CPPUNIT_ASSERT(!strcmp(uCopy[3], "R"));
  CPPUNIT_ASSERT(!strcmp(uCopy[4], "T"));
  CPPUNIT_ASSERT(!strcmp(uCopy[5], "Y"));
#endif
}

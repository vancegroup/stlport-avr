#include <vector>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class LogicTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(LogicTest);
  CPPUNIT_TEST(logicand);
  CPPUNIT_TEST(logicnot);
  CPPUNIT_TEST(logicor);
  CPPUNIT_TEST_SUITE_END();

protected:
  void logicand();
  void logicnot();
  void logicor();
};

CPPUNIT_TEST_SUITE_REGISTRATION(LogicTest);

//
// tests implementation
//
void LogicTest::logicand()
{
  int input1 [4] = { 1, 1, 0, 1 };
  int input2 [4] = { 0, 1, 0, 0 };

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, logical_and<bool>());

  CPPUNIT_ASSERT(output[0]==0);
  CPPUNIT_ASSERT(output[1]==1);
  CPPUNIT_ASSERT(output[2]==0);
  CPPUNIT_ASSERT(output[3]==0);
}
void LogicTest::logicnot()
{
  bool input [7] = { 1, 0, 0, 1, 1, 1, 1 };

  int n = 0;
  count_if(input, input + 7, logical_not<bool>(), n);
  CPPUNIT_ASSERT(n==2);
}
void LogicTest::logicor()
{
  int input1 [4] = { 1, 1, 0, 1 };
  int input2 [4] = { 0, 1, 0, 0 };

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, logical_or<bool>());

  CPPUNIT_ASSERT(output[0]==1);
  CPPUNIT_ASSERT(output[1]==1);
  CPPUNIT_ASSERT(output[2]==0);
  CPPUNIT_ASSERT(output[3]==1);
}

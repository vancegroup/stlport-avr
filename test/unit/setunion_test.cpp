#include <numeric>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class SetUnionTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(SetUnionTest);
  CPPUNIT_TEST(setunon0);
  CPPUNIT_TEST(setunon1);
  CPPUNIT_TEST(setunon2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void setunon0();
  void setunon1();
  void setunon2();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SetUnionTest);

//
// tests implementation
//
void SetUnionTest::setunon0()
{
  int v1[3] = { 13, 18, 23 };
  int v2[4] = { 10, 13, 17, 23 };
  int result[7] = { 0, 0, 0, 0, 0, 0, 0 };

  set_union((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);

  CPPUNIT_ASSERT(result[0]==10);
  CPPUNIT_ASSERT(result[1]==13);
  CPPUNIT_ASSERT(result[2]==17);
  CPPUNIT_ASSERT(result[3]==18);
  CPPUNIT_ASSERT(result[4]==23);
  CPPUNIT_ASSERT(result[5]==0);
  CPPUNIT_ASSERT(result[6]==0);
}
void SetUnionTest::setunon1()
{
  vector <int> v1(10);
  iota(v1.begin(), v1.end(), 0);
  vector <int> v2(10);
  iota(v2.begin(), v2.end(), 7);
  ostringstream os;
  ostream_iterator <int> iter(os, " ");

  set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), iter);

  stringbuf* buff=os.rdbuf();
  string result=buff->str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(), "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 "));
}
void SetUnionTest::setunon2()
{
  char* word1 = "ABCDEFGHIJKLMNO";
  char* word2 = "LMNOPQRSTUVWXYZ";
  ostringstream os;
  ostream_iterator <char> iter(os, " ");

  set_union(word1, word1 + ::strlen(word1), word2, word2 + ::strlen(word2), iter, less<char>());

  stringbuf* buff=os.rdbuf();
  string result=buff->str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(), "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z "));
}

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
class SetDifferenceTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(SetDifferenceTest);
  CPPUNIT_TEST(setdiff0);
  CPPUNIT_TEST(setdiff1);
  CPPUNIT_TEST(setdiff2);
  CPPUNIT_TEST(setsymd0);
  CPPUNIT_TEST(setsymd1);
  CPPUNIT_TEST(setsymd2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void setdiff0();
  void setdiff1();
  void setdiff2();
  void setsymd0();
  void setsymd1();
  void setsymd2();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SetDifferenceTest);

//
// tests implementation
//
void SetDifferenceTest::setsymd0()
{
  int v1[3] = { 13, 18, 23 };
  int v2[4] = { 10, 13, 17, 23 };
  int result[4] = { 0, 0, 0, 0 };

  set_symmetric_difference((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);
  CPPUNIT_ASSERT(result[0]==10);
  CPPUNIT_ASSERT(result[1]==17);
  CPPUNIT_ASSERT(result[2]==18);
  CPPUNIT_ASSERT(result[3]==0);
}
void SetDifferenceTest::setsymd1()
{
  vector <int> v1(10);
  iota(v1.begin(), v1.end(), 0);
  vector <int> v2(10);
  iota(v2.begin(), v2.end(), 7);
  ostringstream os;
  ostream_iterator <int> iter(os, " ");

  set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), iter);
  // 0 1 2 3 4 5 6 10 11 12 13 14 15 16 
  stringbuf* buff=os.rdbuf();
  string result=buff->str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(), "0 1 2 3 4 5 6 10 11 12 13 14 15 16 "));
}
void SetDifferenceTest::setsymd2()
{
  char* word1 = "ABCDEFGHIJKLMNO";
  char* word2 = "LMNOPQRSTUVWXYZ";

  ostringstream os;
  ostream_iterator <char> iter(os, " ");

  set_symmetric_difference(word1, word1 + ::strlen(word1), word2, word2 + ::strlen(word2), iter, less<char>());

  stringbuf* buff=os.rdbuf();
  string result=buff->str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(), "A B C D E F G H I J K P Q R S T U V W X Y Z "));
}
void SetDifferenceTest::setdiff0()
{
  int v1[3] = { 13, 18, 23 };
  int v2[4] = { 10, 13, 17, 23 };
  int result[4] = { 0, 0, 0, 0 };
  //18 0 0 0 
  //10 17 23 0

  set_difference((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);
  CPPUNIT_ASSERT(result[0]==18);
  CPPUNIT_ASSERT(result[1]==0);
  CPPUNIT_ASSERT(result[2]==0);
  CPPUNIT_ASSERT(result[3]==0);

  set_difference((int*)v2, (int*)v2 + 4, (int*)v1, (int*)v1 + 2, (int*)result);
  CPPUNIT_ASSERT(result[0]==10);
  CPPUNIT_ASSERT(result[1]==17);
  CPPUNIT_ASSERT(result[2]==23);
  CPPUNIT_ASSERT(result[3]==0);

}
void SetDifferenceTest::setdiff1()
{
  vector <int> v1(10);
  iota(v1.begin(), v1.end(), 0);
  vector <int> v2(10);
  iota(v2.begin(), v2.end(), 7);
  ostringstream os;
  ostream_iterator <int> iter(os, " ");

  set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), iter);

  stringbuf* buff=os.rdbuf();
  string result=buff->str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(), "0 1 2 3 4 5 6 "));
}
void SetDifferenceTest::setdiff2()
{
  char* word1 = "ABCDEFGHIJKLMNO";
  char* word2 = "LMNOPQRSTUVWXYZ";
  ostringstream os;
  ostream_iterator <char> iter(os, " ");

  set_difference(word1, word1 + ::strlen(word1), word2, word2 + ::strlen(word2), iter, less<char>());

  stringbuf* buff=os.rdbuf();
  string result=buff->str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(), "A B C D E F G H I J K "));
}

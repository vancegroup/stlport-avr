#include <slist>
#include <algorithm>
#include <sstream>
#include <iterator>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class SlistTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(SlistTest);
  CPPUNIT_TEST(slist1);
  CPPUNIT_TEST_SUITE_END();

protected:
  void slist1();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SlistTest);

//
// tests implementation
//
void SlistTest::slist1()
{
/*
original: xlxtss
reversed: sstxlx
removed: sstl
uniqued: stl
sorted: lst
*/
  
  char array [] = { 'x', 'l', 'x', 't', 's', 's' };
  ostringstream os;
  ostream_iterator<char> o(os,"");
  slist<char> str(array+0, array + 6);
  slist<char>::iterator i;
  //Check const_iterator construction from iterator
  slist<char>::const_iterator ci(i);
  slist<char>::const_iterator ci2(ci);
//  cout << "reversed: ";
  str.reverse();
  for(i = str.begin(); i != str.end(); i++)
    os << *i;
  stringbuf* buff=os.rdbuf();
  string result=buff->str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(),"sstxlx"));

  //cout << "removed: ";
  str.remove('x');
  ostringstream os2;
  for(i = str.begin(); i != str.end(); i++)
    os2 << *i;
  buff=os2.rdbuf();
  result=buff->str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(),"sstl"));


  //cout << "uniqued: ";
  str.unique();
  ostringstream os3;
  for(i = str.begin(); i != str.end(); i++)
    os3 << *i;
  buff=os3.rdbuf();
  result=buff->str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(),"stl"));
  
  //cout << "sorted: ";
  str.sort();
  ostringstream os4;
  for(i = str.begin(); i != str.end(); i++)
    os4 << *i;
  buff=os4.rdbuf();
  result=buff->str();
  CPPUNIT_ASSERT(!strcmp(result.c_str(),"lst"));
}

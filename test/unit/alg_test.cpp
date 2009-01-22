// -*- C++ -*- Time-stamp: <09/01/23 02:18:47 ptr>

/*
 * Copyright (c) 2004-2009
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#include "alg_test.h"

#include <algorithm>
#include <vector>

#include <list>
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
#  include <slist>
#endif
#include <queue>
#include <deque>
#include <functional>
#include <map>
#include <string>
#include <cstring>

#include "iota.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

static bool odd(int a_)
{
  return (a_ % 2) != 0;
}

int EXAM_IMPL(alg_test::reverse1)
{
  int numbers[6] = { 0, 1, 2, 3, 4, 5 };

  reverse(numbers, numbers + 6);
  EXAM_CHECK(numbers[0]==5);
  EXAM_CHECK(numbers[1]==4);
  EXAM_CHECK(numbers[2]==3);
  EXAM_CHECK(numbers[3]==2);
  EXAM_CHECK(numbers[4]==1);
  EXAM_CHECK(numbers[5]==0);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::revcopy1)
{
  int numbers[6] = { 0, 1, 2, 3, 4, 5 };

  int result[6];
  reverse_copy((int*)numbers, (int*)numbers + 6, (int*)result);
  // 5 4 3 2 1 0
  EXAM_CHECK(result[0]==5);
  EXAM_CHECK(result[1]==4);
  EXAM_CHECK(result[2]==3);
  EXAM_CHECK(result[3]==2);
  EXAM_CHECK(result[4]==1);
  EXAM_CHECK(result[5]==0);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::replif1)
{
  vector <int> v1(10);
  for (int i = 0; (size_t)i < v1.size(); ++i)
    v1[i] = i % 5;

  replace_if(v1.begin(), v1.end(), odd, 42);

  // 0 42 2 42 4 0 42 2 42 4
  EXAM_CHECK(v1[0]==0);
  EXAM_CHECK(v1[1]==42);
  EXAM_CHECK(v1[2]==2);
  EXAM_CHECK(v1[3]==42);
  EXAM_CHECK(v1[4]==4);
  EXAM_CHECK(v1[5]==0);
  EXAM_CHECK(v1[6]==42);
  EXAM_CHECK(v1[7]==2);
  EXAM_CHECK(v1[8]==42);
  EXAM_CHECK(v1[9]==4);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::replcpy1)
{
  int numbers[6] = { 0, 1, 2, 0, 1, 2 };
  int result[6] = { 0, 0, 0, 0, 0, 0 };

  replace_copy((int*)numbers, (int*)numbers + 6, (int*)result, 2, 42);
  EXAM_CHECK(result[0]==0);
  EXAM_CHECK(result[1]==1);
  EXAM_CHECK(result[2]==42);
  EXAM_CHECK(result[3]==0);
  EXAM_CHECK(result[4]==1);
  EXAM_CHECK(result[5]==42);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::replace0)
{
  int numbers[6] = { 0, 1, 2, 0, 1, 2 };

  replace(numbers, numbers + 6, 2, 42);

  // 0 1 42 0 1 42
  EXAM_CHECK(numbers[0]==0);
  EXAM_CHECK(numbers[1]==1);
  EXAM_CHECK(numbers[2]==42);
  EXAM_CHECK(numbers[3]==0);
  EXAM_CHECK(numbers[4]==1);
  EXAM_CHECK(numbers[5]==42);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::replace1)
{
  vector <int> v1(10);
  for (int i = 0; (size_t)i < v1.size(); ++i)
    v1[i] = i % 5;
  replace(v1.begin(), v1.end(), 2, 42);

  // 0 1 2 3 4 0 1 2 3 4
  // 0 1 42 3 4 0 1 42 3 4
  EXAM_CHECK(v1[0]==0);
  EXAM_CHECK(v1[1]==1);
  EXAM_CHECK(v1[2]==42);
  EXAM_CHECK(v1[3]==3);
  EXAM_CHECK(v1[4]==4);
  EXAM_CHECK(v1[5]==0);
  EXAM_CHECK(v1[6]==1);
  EXAM_CHECK(v1[7]==42);
  EXAM_CHECK(v1[8]==3);
  EXAM_CHECK(v1[9]==4);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::repcpif1)
{
  vector <int> v1(10);
  for (int i = 0; (size_t)i < v1.size(); ++i)
    v1[i] = i % 5;
  vector <int> v2(v1.size());

  // 0 1 2 3 4 0 1 2 3 4
  // 0 1 2 3 4 0 1 2 3 4
  // 0 42 2 42 4 0 42 2 42 4
  replace_copy_if(v1.begin(), v1.end(), v2.begin(), odd, 42);
  EXAM_CHECK(v1[0]==0);
  EXAM_CHECK(v1[1]==1);
  EXAM_CHECK(v1[2]==2);
  EXAM_CHECK(v1[3]==3);
  EXAM_CHECK(v1[4]==4);
  EXAM_CHECK(v1[5]==0);
  EXAM_CHECK(v1[6]==1);
  EXAM_CHECK(v1[7]==2);
  EXAM_CHECK(v1[8]==3);
  EXAM_CHECK(v1[9]==4);

  EXAM_CHECK(v2[0]==0);
  EXAM_CHECK(v2[1]==42);
  EXAM_CHECK(v2[2]==2);
  EXAM_CHECK(v2[3]==42);
  EXAM_CHECK(v2[4]==4);
  EXAM_CHECK(v2[5]==0);
  EXAM_CHECK(v2[6]==42);
  EXAM_CHECK(v2[7]==2);
  EXAM_CHECK(v2[8]==42);
  EXAM_CHECK(v2[9]==4);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::remove1)
{
  int numbers[6] = { 1, 2, 3, 1, 2, 3 };
  remove((int*)numbers, (int*)numbers + 6, 1);

  // 2 3 2 3 2 3
  EXAM_CHECK(numbers[0]==2);
  EXAM_CHECK(numbers[1]==3);
  EXAM_CHECK(numbers[2]==2);
  EXAM_CHECK(numbers[3]==3);
  EXAM_CHECK(numbers[4]==2);
  EXAM_CHECK(numbers[5]==3);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::remif1)
{
  int numbers[6] = { 0, 0, 1, 1, 2, 2 };

  remove_if((int*)numbers, (int*)numbers + 6, odd);

  // 0 0 2 2 2 2
  EXAM_CHECK(numbers[0]==0);
  EXAM_CHECK(numbers[1]==0);
  EXAM_CHECK(numbers[2]==2);
  EXAM_CHECK(numbers[3]==2);
  EXAM_CHECK(numbers[4]==2);
  EXAM_CHECK(numbers[5]==2);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::remcopy1)
{
  int numbers[6] = { 1, 2, 3, 1, 2, 3 };
  int result[6] = { 0, 0, 0, 0, 0, 0 };

  remove_copy((int*)numbers, (int*)numbers + 6, (int*)result, 2);

  EXAM_CHECK(result[0]==1);
  EXAM_CHECK(result[1]==3);
  EXAM_CHECK(result[2]==1);
  EXAM_CHECK(result[3]==3);
  EXAM_CHECK(result[4]==0);
  EXAM_CHECK(result[5]==0);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::remcpif1)
{
  int numbers[6] = { 1, 2, 3, 1, 2, 3 };
  int result[6] = { 0, 0, 0, 0, 0, 0 };

  remove_copy_if((int*)numbers, (int*)numbers + 6, (int*)result, odd);

  // 2 2 0 0 0 0
  EXAM_CHECK(result[0]==2);
  EXAM_CHECK(result[1]==2);
  EXAM_CHECK(result[2]==0);
  EXAM_CHECK(result[3]==0);
  EXAM_CHECK(result[4]==0);
  EXAM_CHECK(result[5]==0);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::min_max)
{
  int i = min(4, 7);
  EXAM_CHECK( i == 4 );
  char c = max('a', 'z');
  EXAM_CHECK( c == 'z' );

#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  c = min('a', 'z', greater<char>());
  EXAM_CHECK( c == 'z' );
  i = max(4, 7, greater<int>());
  EXAM_CHECK( i == 4 );
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::count_test)
{
  {
    int i[] = { 1, 4, 2, 8, 2, 2 };
    int n = count(i, i + 6, 2);
    EXAM_CHECK(n==3);
#if defined (STLPORT) && !defined (_STLP_NO_ANACHRONISMS)
    n = 0;
    count(i, i + 6, 2, n);
    EXAM_CHECK(n==3);
#endif
  }
  {
    vector<int> i;
    i.push_back(1);
    i.push_back(4);
    i.push_back(2);
    i.push_back(8);
    i.push_back(2);
    i.push_back(2);
    int n = count(i.begin(), i.end(), 2);
    EXAM_CHECK(n==3);
#if defined (STLPORT) && !defined (_STLP_NO_ANACHRONISMS)
    n = 0;
    count(i.begin(), i.end(), 2, n);
    EXAM_CHECK(n==3);
#endif
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::sort_test)
{
  {
    vector<int> years;
    years.push_back(1962);
    years.push_back(1992);
    years.push_back(2001);
    years.push_back(1999);
    sort(years.begin(), years.end());
    EXAM_CHECK(years[0]==1962);
    EXAM_CHECK(years[1]==1992);
    EXAM_CHECK(years[2]==1999);
    EXAM_CHECK(years[3]==2001);
  }
  {
    deque<int> years;
    years.push_back(1962);
    years.push_back(1992);
    years.push_back(2001);
    years.push_back(1999);
    sort(years.begin(), years.end()); // <-- changed!
    EXAM_CHECK(years[0]==1962);
    EXAM_CHECK(years[1]==1992);
    EXAM_CHECK(years[2]==1999);
    EXAM_CHECK(years[3]==2001);
  }

  return EXAM_RESULT;
}

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

int EXAM_IMPL(alg_test::search_n_test)
{
  int ints[] = {0, 1, 2, 3, 3, 4, 4, 4, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5};

#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  //search_n
  //Forward iterator
  {
    slist<int> slint(ints, ints + ARRAY_SIZE(ints));
    slist<int>::iterator slit = search_n(slint.begin(), slint.end(), 2, 2);
    EXAM_CHECK( slit != slint.end() );
    EXAM_CHECK( *(slit++) == 2 );
    EXAM_CHECK( *slit == 2 );
  }
#endif

  //Bidirectionnal iterator
  {
    list<int> lint(ints, ints + ARRAY_SIZE(ints));
    list<int>::iterator lit = search_n(lint.begin(), lint.end(), 3, 3);
    EXAM_CHECK( lit != lint.end() );
    EXAM_CHECK( *(lit++) == 3 );
    EXAM_CHECK( *(lit++) == 3 );
    EXAM_CHECK( *lit == 3 );
  }

  //Random access iterator
  {
    deque<int> dint(ints, ints + ARRAY_SIZE(ints));
    deque<int>::iterator dit = search_n(dint.begin(), dint.end(), 4, 4);
    EXAM_CHECK( dit != dint.end() );
    EXAM_CHECK( *(dit++) == 4 );
    EXAM_CHECK( *(dit++) == 4 );
    EXAM_CHECK( *(dit++) == 4 );
    EXAM_CHECK( *dit == 4 );
  }

#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  //search_n with predicate
  //Forward iterator
  {
    slist<int> slint(ints, ints + ARRAY_SIZE(ints));
    slist<int>::iterator slit = search_n(slint.begin(), slint.end(), 2, 1, greater<int>());
    EXAM_CHECK( slit != slint.end() );
    EXAM_CHECK( *(slit++) > 1 );
    EXAM_CHECK( *slit > 2 );
  }
#endif

  //Bidirectionnal iterator
  {
    list<int> lint(ints, ints + ARRAY_SIZE(ints));
    list<int>::iterator lit = search_n(lint.begin(), lint.end(), 3, 2, greater<int>());
    EXAM_CHECK( lit != lint.end() );
    EXAM_CHECK( *(lit++) > 2 );
    EXAM_CHECK( *(lit++) > 2 );
    EXAM_CHECK( *lit > 2 );
  }

  //Random access iterator
  {
    deque<int> dint(ints, ints + ARRAY_SIZE(ints));
    deque<int>::iterator dit = search_n(dint.begin(), dint.end(), 4, 3, greater<int>());
    EXAM_CHECK( dit != dint.end() );
    EXAM_CHECK( *(dit++) > 3 );
    EXAM_CHECK( *(dit++) > 3 );
    EXAM_CHECK( *(dit++) > 3 );
    EXAM_CHECK( *dit > 3 );
  }

  // test for bug reported by Jim Xochellis
  {
    int array[] = {0, 0, 1, 0, 1, 1};
    int* array_end = array + sizeof(array) / sizeof(*array);
    EXAM_CHECK(search_n(array, array_end, 3, 1) == array_end);
  }

  // test for bug with counter == 1, reported by Timmie Smith
  {
    int array[] = {0, 1, 2, 3, 4, 5};
    int* array_end = array + sizeof(array) / sizeof(*array);
    EXAM_CHECK( search_n(array, array_end, 1, 1, equal_to<int>() ) == &array[1] );
  }

  return EXAM_RESULT;
}

struct MyIntComparable {
  MyIntComparable(int val) : _val(val) {}
  bool operator == (const MyIntComparable& other) const
  { return _val == other._val; }

private:
  int _val;
};

int EXAM_IMPL(alg_test::find_first_of_test)
{
#if defined (STLPORT) && !defined (_STLP_NO_EXTENSIONS)
  slist<int> intsl;
  intsl.push_front(1);
  intsl.push_front(2);

  {
    vector<int> intv;
    intv.push_back(0);
    intv.push_back(1);
    intv.push_back(2);
    intv.push_back(3);

    vector<int>::iterator first;
    first = find_first_of(intv.begin(), intv.end(), intsl.begin(), intsl.end());
    EXAM_CHECK( first != intv.end() );
    EXAM_CHECK( *first == 1 );
  }
  {
    vector<int> intv;
    intv.push_back(3);
    intv.push_back(2);
    intv.push_back(1);
    intv.push_back(0);

    vector<int>::iterator first;
    first = find_first_of(intv.begin(), intv.end(), intsl.begin(), intsl.end());
    EXAM_CHECK( first != intv.end() );
    EXAM_CHECK( *first == 2 );
  }
#endif

  list<int> intl;
  intl.push_front(1);
  intl.push_front(2);

  {
    vector<int> intv;
    intv.push_back(0);
    intv.push_back(1);
    intv.push_back(2);
    intv.push_back(3);

    vector<int>::iterator first;
    first = find_first_of(intv.begin(), intv.end(), intl.begin(), intl.end());
    EXAM_CHECK( first != intv.end() );
    EXAM_CHECK( *first == 1 );
  }
  {
    vector<int> intv;
    intv.push_back(3);
    intv.push_back(2);
    intv.push_back(1);
    intv.push_back(0);

    vector<int>::iterator first;
    first = find_first_of(intv.begin(), intv.end(), intl.begin(), intl.end());
    EXAM_CHECK( first != intv.end() );
    EXAM_CHECK( *first == 2 );
  }
  {
    char chars[] = {1, 2};

    vector<int> intv;
    intv.push_back(0);
    intv.push_back(1);
    intv.push_back(2);
    intv.push_back(3);

    vector<int>::iterator first;
    first = find_first_of(intv.begin(), intv.end(), chars, chars + sizeof(chars));
    EXAM_CHECK( first != intv.end() );
    EXAM_CHECK( *first == 1 );
  }
  {
    unsigned char chars[] = {1, 2, 255};

    vector<int> intv;
    intv.push_back(-10);
    intv.push_back(1029);
    intv.push_back(255);
    intv.push_back(4);

    vector<int>::iterator first;
    first = find_first_of(intv.begin(), intv.end(), chars, chars + sizeof(chars));
    EXAM_CHECK( first != intv.end() );
    EXAM_CHECK( *first == 255 );
  }
  {
    signed char chars[] = {93, 2, -101, 13};

    vector<int> intv;
    intv.push_back(-10);
    intv.push_back(1029);
    intv.push_back(-2035);
    intv.push_back(-101);
    intv.push_back(4);

    vector<int>::iterator first;
    first = find_first_of(intv.begin(), intv.end(), chars, chars + sizeof(chars));
    EXAM_CHECK( first != intv.end() );
    EXAM_CHECK( *first == -101 );
  }
  {
    char chars[] = {1, 2};

    vector<MyIntComparable> intv;
    intv.push_back(0);
    intv.push_back(1);
    intv.push_back(2);
    intv.push_back(3);

    vector<MyIntComparable>::iterator first;
    first = find_first_of(intv.begin(), intv.end(), chars, chars + sizeof(chars));
    EXAM_CHECK( first != intv.end() );
    EXAM_CHECK( *first == 1 );
  }

  return EXAM_RESULT;
}

typedef pair<int, string> Pair;

struct ValueFinder :
    public binary_function<const Pair&, const string&, bool>
{
    bool operator () ( const Pair &p, const string& value ) const
      { return p.second == value; }
};

int EXAM_IMPL(alg_test::find_first_of_nsc_test)
{
  // Non-symmetrical comparator

  map<int, string> m;
  vector<string> values;

  m[1] = "one";
  m[4] = "four";
  m[10] = "ten";
  m[20] = "twenty";

  values.push_back( "four" );
  values.push_back( "ten" );

  map<int, string>::iterator i = find_first_of(m.begin(), m.end(), values.begin(), values.end(), ValueFinder());

  EXAM_CHECK( i != m.end() );
  EXAM_CHECK( i->first == 4 || i->first == 10 );
  EXAM_CHECK( i->second == "four" || i->second == "ten" );

  return EXAM_RESULT;
}

bool alg_test::str_compare( const char* a_, const char* b_ )
{
  return strcmp(a_, b_) < 0 ? 1 : 0;
}

int EXAM_IMPL(alg_test::max1)
{
  int r = max(42, 100);
  EXAM_CHECK( r == 100 );

  int t = max(++r, 0);
  EXAM_CHECK( t == 101 );

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::max2)
{
  const char* r = max((const char*)"shoe", (const char*)"shine", str_compare);
  EXAM_CHECK(!strcmp(r, "shoe"));

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::maxelem1)
{
  int numbers[6] = { 4, 10, 56, 11, -42, 19 };

  int* r = max_element((int*)numbers, (int*)numbers + 6);
  EXAM_CHECK(*r==56);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::maxelem2)
{
  const char* names[] = { "Brett", "Graham", "Jack", "Mike", "Todd" };

  const unsigned namesCt = sizeof(names) / sizeof(names[0]);
  const char** r = max_element((const char**)names, (const char**)names + namesCt, str_compare);
  EXAM_CHECK(!strcmp(*r, "Todd"));

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::min1)
{
  int r = min(42, 100);
  EXAM_CHECK( r == 42 );

  r = min(--r, r);
  EXAM_CHECK( r == 41 );

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::min2)
{
  const char* r = min((const char*)"shoe", (const char*)"shine", str_compare);
  EXAM_CHECK(!strcmp(r, "shine"));

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::minelem1)
{
  int numbers[6] = { -10, 15, -100, 36, -242, 42 };
  int* r = min_element((int*)numbers, (int*)numbers + 6);
  EXAM_CHECK(*r==-242);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::minelem2)
{
  const char* names[] = { "Brett", "Graham", "Jack", "Mike", "Todd" };

  const unsigned namesCt = sizeof(names) / sizeof(names[0]);
  const char** r = min_element((const char**)names, (const char**)names + namesCt, str_compare);
  EXAM_CHECK(!strcmp(*r, "Brett"));

  return EXAM_RESULT;
}


int EXAM_IMPL(alg_test::uprbnd1)
{
  int arr[20];
  for(int i = 0; i < 20; i++)
  {
    arr[i] = i/4;
  }
  int location = upper_bound((int*)arr, (int*)arr + 20, 3) - arr;
  EXAM_CHECK(location==16);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::uprbnd2)
{
  char const* str [] = { "a", "a", "b", "b", "q", "w", "z" };

  const unsigned strCt = sizeof(str)/sizeof(str[0]);

  int location = (upper_bound((char const**)str,  (char const**)str + strCt, (const char *)"d", str_compare) - str);
  EXAM_CHECK(location==4);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::lwrbnd1)
{
  vector <int> v1(20);
  for (int i = 0; (size_t)i < v1.size(); ++i)
  {
    v1[i] = i/4;
  }
  // 0 0 0 0 1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4
  vector<int>::iterator location = lower_bound(v1.begin(), v1.end(), 3);

  EXAM_CHECK((location - v1.begin())==12);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::lwrbnd2)
{
  char const* str [] = { "a", "a", "b", "b", "q", "w", "z" };

  const unsigned strCt = sizeof(str)/sizeof(str[0]);
  char const** location = lower_bound((char const**)str,  (char const**)str + strCt, (const char *)"d", str_compare);

  EXAM_CHECK((location - str) == 4);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::equal_range0)
{
  int numbers[10] = { 0, 0, 1, 1, 2, 2, 2, 2, 3, 3 };
  pair<int*, int*> range = equal_range((int*)numbers, (int*)numbers + 10, 2);
  EXAM_CHECK( (range.first - numbers) == 4 );
  EXAM_CHECK( (range.second - numbers) == 8 );

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::equal_range1)
{
  typedef vector <int> IntVec;
  IntVec v(10);
  for (int i = 0; (size_t)i < v.size(); ++i)
    v[i] = i / 3;

  pair<IntVec::iterator, IntVec::iterator> range = equal_range(v.begin(), v.end(), 2);
  EXAM_CHECK( (range.first - v.begin()) == 6 );
  EXAM_CHECK( (range.second - v.begin()) == 9 );
  for (; range.first != range.second; ++range.first)
    EXAM_CHECK( *range.first == 2 );

  range = equal_range(v.begin(), v.end(), 4);
  EXAM_CHECK( range.first == range.second );
  EXAM_CHECK( range.first == v.end() );

  return EXAM_RESULT;
}

struct Test {
  Test(int val) : value(val) {}
  int value;

  bool operator == (int i) const
  { return value == i; }
};

bool operator < (const Test& v1, int v2)
{ return v1.value < v2; }

bool operator < (int v1, const Test& v2)
{ return v1 < v2.value; }

#if defined (_MSC_VER) && !defined (STLPORT)
bool operator < (const Test& v1, const Test& v2)
{ return v1.value < v2.value; }
#endif

int EXAM_IMPL(alg_test::equal_range2)
{
  char chars[] = "aabbccddggghhklllmqqqqssyyzz";

  const unsigned count = sizeof(chars) - 1;
  pair<char*, char*> range = equal_range((char*)chars, (char*)chars + count, 'q', less<char>());
  EXAM_CHECK( (range.first - chars) == 18 );
  EXAM_CHECK( (range.second - chars) == 22 );
  for (; range.first != range.second; ++range.first)
    EXAM_CHECK( *range.first == 'q' );

  range = equal_range((char*)chars, (char*)chars + count, 'm', less<char>());
  EXAM_CHECK( (range.second - range.first) == 1 );
  EXAM_CHECK( *range.first == 'm' );

  vector<Test> tv;
  vector<Test>::iterator it;
  pair<vector<Test>::iterator, vector<Test>::iterator> p;

  for (int i = 0; i < 10; ++i) {
    tv.push_back(i);
  }

  it = upper_bound(tv.begin(), tv.end(), 5);
  EXAM_CHECK( it != tv.end() );
  EXAM_CHECK( *it == 6 );

  it = lower_bound(tv.begin(), tv.end(), 5);
  EXAM_CHECK( it != tv.end() );
  EXAM_CHECK( *it == 5 );

  p = equal_range(tv.begin(), tv.end(), 5);
  EXAM_CHECK( p.first != p.second );
  EXAM_CHECK( p.first != tv.end() );
  EXAM_CHECK( p.second != tv.end() );
  EXAM_CHECK( *p.first == 5 );
  EXAM_CHECK( *p.second == 6 );

  return EXAM_RESULT;
}


// used as adaptor's return/argument type,
// to allow binders/composers usage
struct __void_tag {};

#if !defined (STLPORT) || defined (_STLP_USE_NAMESPACES)
using std::unary_function;
#endif

template <class Result>
class pointer_to_void_function
{
  protected:
    Result (*ptr)();

  public:
    explicit pointer_to_void_function(Result (*x)()) :
        ptr(x)
      { }

    Result operator()() const
      { return ptr(); }

    Result operator()(__void_tag) const
      { return ptr(); }
};

// to feed composers
template <class Arg1>
struct projectvoid :
    public unary_function<Arg1,__void_tag>
{
    __void_tag operator()(const Arg1& x) const
      { return __void_tag(); }
};

#if !defined (_STLP_MEMBER_POINTER_PARAM_BUG)

template <class Result>
pointer_to_void_function<Result> ptr_fun(Result (*x)())
{ return pointer_to_void_function<Result>(x); }

// alternate name
template <class Result>
pointer_to_void_function<Result> ptr_gen(Result (*x)()) {
  return pointer_to_void_function<Result>(x);
}

#endif /*  !defined (_STLP_MEMBER_POINTER_PARAM_BUG) */

template <class Arg>
class pointer_to_unary_procedure /* :public unary_function<Arg, __void_tag> */
{
  protected:
    typedef void (*fun_type)(Arg);

    fun_type ptr;

  public:
    typedef Arg argument_type;

    pointer_to_unary_procedure()
      { }
    pointer_to_unary_procedure(fun_type x) :
        ptr(x)
      { }

    void operator() (Arg x) const
      { ptr(x); }
};

template <class Arg>
inline pointer_to_unary_procedure<Arg> ptr_proc(void (*x)(Arg))
{ return pointer_to_unary_procedure<Arg>(x); }

template <class Arg1, class Arg2>
class pointer_to_binary_procedure /* : public unary_function<Arg1, Arg2, __void_tag> */
{
  protected:
    typedef void (*fun_type)(Arg1, Arg2);

    fun_type ptr;

  public:
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;

    pointer_to_binary_procedure()
      { }
    pointer_to_binary_procedure(fun_type x) :
        ptr(x)
      { }

    void operator() (Arg1 x, Arg2 y) const
      { ptr(x, y); }
};

template <class Arg1, class Arg2>
inline pointer_to_binary_procedure<Arg1, Arg2> ptr_proc(void (*x)(Arg1, Arg2))
{ return pointer_to_binary_procedure<Arg1, Arg2>(x); }

void alg_test::increase( int& a_ )
{
  a_ += 1;
}

int EXAM_IMPL(alg_test::foreach0)
{
  int numbers[10] = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };

  for_each(numbers, numbers + 10, ptr_fun(increase));

  EXAM_CHECK(numbers[0]==2);
  EXAM_CHECK(numbers[1]==2);
  EXAM_CHECK(numbers[2]==3);
  EXAM_CHECK(numbers[3]==4);
  EXAM_CHECK(numbers[4]==6);
  EXAM_CHECK(numbers[5]==9);
  EXAM_CHECK(numbers[6]==14);
  EXAM_CHECK(numbers[7]==22);
  EXAM_CHECK(numbers[8]==35);
  EXAM_CHECK(numbers[9]==56);

  return EXAM_RESULT;
}

void alg_test::sqr(int& a_)
{
  a_ = a_ * a_;
}

int EXAM_IMPL(alg_test::foreach1)
{
  vector<int> v1(10);
  for (int i = 0; (size_t)i < v1.size(); ++i)
    v1[i] = i;
  for_each(v1.begin(), v1.end(), ptr_fun(sqr) );

  EXAM_CHECK(v1[0]==0);
  EXAM_CHECK(v1[1]==1);
  EXAM_CHECK(v1[2]==4);
  EXAM_CHECK(v1[3]==9);
  EXAM_CHECK(v1[4]==16);
  EXAM_CHECK(v1[5]==25);
  EXAM_CHECK(v1[6]==36);
  EXAM_CHECK(v1[7]==49);
  EXAM_CHECK(v1[8]==64);
  EXAM_CHECK(v1[9]==81);

  return EXAM_RESULT;
}

class Fibonacci
{
  public:
    Fibonacci() : v1(0), v2(1) {}
    int operator()()
      { int r = v1 + v2; v1 = v2; v2 = r; return v1; }

  private:
    int v1;
    int v2;
};

static int cxxrand() { return rand();}

int EXAM_IMPL(alg_test::gener1)
{
  int numbers[10];
#if defined(__MVS__)
  generate(numbers, numbers + 10, ptr_gen(cxxrand));
#else
  generate(numbers, numbers + 10, cxxrand);
#endif
  // any suggestions?

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::gener2)
{
  vector <int> v1(10);
  Fibonacci generator;
  generate(v1.begin(), v1.end(), generator);

  EXAM_CHECK(v1[0]==1);
  EXAM_CHECK(v1[1]==1);
  EXAM_CHECK(v1[2]==2);
  EXAM_CHECK(v1[3]==3);
  EXAM_CHECK(v1[4]==5);
  EXAM_CHECK(v1[5]==8);
  EXAM_CHECK(v1[6]==13);
  EXAM_CHECK(v1[7]==21);
  EXAM_CHECK(v1[8]==34);
  EXAM_CHECK(v1[9]==55);

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::genern1)
{
#if !defined (_STLP_MEMBER_POINTER_PARAM_BUG)
  //*TY 07/18/98 - added conditional
  // since ptr_gen() is not defined under this condition
  // (see xfunction.h)
  vector <int> v1(10);
  generate_n(v1.begin(), v1.size(), ptr_gen(cxxrand));
#endif  //_STLP_MEMBER_POINTER_PARAM_BUG  //*TY 07/18/98 - added

  return EXAM_RESULT;
}

int EXAM_IMPL(alg_test::genern2)
{
  vector <int> v1(10);
  Fibonacci generator;
  generate_n(v1.begin(), v1.size(), generator);

  EXAM_CHECK(v1[0]==1);
  EXAM_CHECK(v1[1]==1);
  EXAM_CHECK(v1[2]==2);
  EXAM_CHECK(v1[3]==3);
  EXAM_CHECK(v1[4]==5);
  EXAM_CHECK(v1[5]==8);
  EXAM_CHECK(v1[6]==13);
  EXAM_CHECK(v1[7]==21);
  EXAM_CHECK(v1[8]==34);
  EXAM_CHECK(v1[9]==55);

  return EXAM_RESULT;
}

int EXAM_IMPL(count_test::count0)
{
  int numbers[10] = { 1, 2, 4, 1, 2, 4, 1, 2, 4, 1 };

  int result = count(numbers, numbers + 10, 1);
  EXAM_CHECK(result==4);
#if defined (STLPORT) && !defined (_STLP_NO_ANACHRONISMS)
  result = 0;
  count(numbers, numbers + 10, 1, result);
  EXAM_CHECK(result==4);
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(count_test::count1)
{
  vector <int> numbers(100);
  for(int i = 0; i < 100; i++)
  numbers[i] = i % 3;
  int elements = count(numbers.begin(), numbers.end(), 2);
  EXAM_CHECK(elements==33);
#if defined (STLPORT) && !defined (_STLP_NO_ANACHRONISMS)
  elements = 0;
  count(numbers.begin(), numbers.end(), 2, elements);
  EXAM_CHECK(elements==33);
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(count_test::countif1)
{
  vector <int> numbers(100);
  for(int i = 0; i < 100; i++)
    numbers[i] = i % 3;
  int elements = count_if(numbers.begin(), numbers.end(), odd);
  EXAM_CHECK(elements==33);
#if defined (STLPORT) && !defined (_STLP_NO_ANACHRONISMS)
  elements = 0;
  count_if(numbers.begin(), numbers.end(), odd, elements);
  EXAM_CHECK(elements==33);
#endif

  return EXAM_RESULT;
}

int count_test::odd(int a_)
{
  return a_ % 2;
}

static int negate_int( int a_ )
{ return -a_; }

static char map_char( char a_, int b_ )
{ return char(a_ + b_); }

static char shift( char c )
{ return char(((int)c + 1) % 256); }

int EXAM_IMPL(transform_test::trnsfrm1)
{
  int numbers[6] = { -5, -1, 0, 1, 6, 11 };

  int result[6];
  transform((int*)numbers, (int*)numbers + 6, (int*)result, negate_int);

  EXAM_CHECK(result[0]==5);
  EXAM_CHECK(result[1]==1);
  EXAM_CHECK(result[2]==0);
  EXAM_CHECK(result[3]==-1);
  EXAM_CHECK(result[4]==-6);
  EXAM_CHECK(result[5]==-11);

  return EXAM_RESULT;
}

int EXAM_IMPL(transform_test::trnsfrm2)
{
#if defined (__MVS__)
  int trans[] = {-11, 4, -6, -6, -18, 0, 18, -14, 6, 0, -1, -59};
#else
  int trans[] = {-4, 4, -6, -6, -10, 0, 10, -6, 6, 0, -1, -77};
#endif
  char n[] = "Larry Mullen";
  const size_t count = ::strlen(n);

  string res;
  transform(n, n + count, trans, back_inserter(res), map_char);
  EXAM_CHECK( res == "Hello World!" );

  return EXAM_RESULT;
}

int EXAM_IMPL(transform_test::self_str)
{
  string s( "0123456789abcdefg" );
  string r( "123456789:bcdefgh" );
  transform( s.begin(), s.end(), s.begin(), shift );
  EXAM_CHECK( s == r );

  return EXAM_RESULT;
}

int EXAM_IMPL(neq_test::negate0)
{
  int input [3] = { 1, 2, 3 };

  int output[3];
  transform((int*)input, (int*)input + 3, (int*)output, negate<int>());

  EXAM_CHECK(output[0]==-1);
  EXAM_CHECK(output[1]==-2);
  EXAM_CHECK(output[2]==-3);

  return EXAM_RESULT;
}

int EXAM_IMPL(neq_test::nequal0)
{
  int input1 [4] = { 1, 7, 2, 2 };
  int input2 [4] = { 1, 6, 2, 3 };

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, not_equal_to<int>());

  EXAM_CHECK(output[0]==0);
  EXAM_CHECK(output[1]==1);
  EXAM_CHECK(output[2]==0);
  EXAM_CHECK(output[3]==1);

  return EXAM_RESULT;
}

int EXAM_IMPL(modulus_test::modulus0)
{
  int input1 [4] = { 6, 8, 10, 2 };
  int input2 [4] = { 4, 2, 11, 3 };

  int output [4];

  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, modulus<int>());
  EXAM_CHECK(output[0]==2);
  EXAM_CHECK(output[1]==0);
  EXAM_CHECK(output[2]==10);
  EXAM_CHECK(output[3]==2);

  return EXAM_RESULT;
}

int EXAM_IMPL(copy_test::copy_array)
{
  char string[23] = "A string to be copied.";
  char result[23];
  copy(string, string + 23, result);
  EXAM_CHECK(!strncmp(string, result, 23));

  return EXAM_RESULT;
}

int EXAM_IMPL(copy_test::copy_volatile)
{
  {
    int a[] = {0, 1, 2, 3, 4, 5};
    const size_t size = sizeof(a) / sizeof(a[0]);
    volatile int va[size]; 
    copy(a, a + size, va);
    for ( size_t i = 0; i != size; ++i ) {
      EXAM_CHECK( a[i] == va[i] );
    }
  }

  {
    const int a[] = {0, 1, 2, 3, 4, 5};
    const size_t size = sizeof(a) / sizeof(a[0]);
    volatile int va[size]; 
    copy(a, a + size, va);
    for ( size_t i = 0; i != size; ++i ) {
      EXAM_CHECK( a[i] == va[i] );
    }
  }

  // Following code can be activated to check that it doesn't compiled
#if 0
  {
    int a[] = {0, 1, 2, 3, 4, 5};
    const size_t size = sizeof(a) / sizeof(a[0]);
    const volatile int va[size] = {5, 4, 3, 2, 1, 0}; 
    copy(a, a + size, va);
    for (size_t i = 0; i != size; ++i) {
      EXAM_CHECK( a[i] == va[i] );
    }
  }
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(copy_test::copy_vector)
{
  vector<int> v1(10);

  for ( int i = 0; (size_t)i < v1.size(); ++i ) {
    v1[i] = i;
  }

  vector<int> v2(v1.size());
  copy(v1.begin(), v1.end(), v2.begin());

  EXAM_CHECK( v2 == v1 );

  return EXAM_RESULT;
}

int EXAM_IMPL(copy_test::copy_insert)
{
  vector<int> v1(10);
  for ( int loc = 0; (size_t)loc < v1.size(); ++loc ) {
    v1[loc] = loc;
  }
  vector<int> v2;
  insert_iterator<vector<int> > i(v2, v2.begin());
  copy(v1.begin(), v1.end(), i);

  EXAM_CHECK( v2 == v1 );

  return EXAM_RESULT;
}

int EXAM_IMPL(copy_test::copy_back)
{
  vector<int> v1(10);
  for ( int i = 0; (size_t)i < v1.size(); ++i ) {
    v1[i] = i;
  }
  vector<int> v2(v1.size());
  copy_backward(v1.begin(), v1.end(), v2.end());

  EXAM_CHECK( v2 == v1 );

  return EXAM_RESULT;
}

int EXAM_IMPL(copy_test::copy_back_array)
{
  int numbers[5] = { 1, 2, 3, 4, 5 };

  int result[5];
  copy_backward(numbers, numbers + 5, (int*)result + 5);
  EXAM_CHECK(result[0]==numbers[0]);
  EXAM_CHECK(result[1]==numbers[1]);
  EXAM_CHECK(result[2]==numbers[2]);
  EXAM_CHECK(result[3]==numbers[3]);
  EXAM_CHECK(result[4]==numbers[4]);

  return EXAM_RESULT;
}

int EXAM_IMPL(fill_test::fill1)
{
  vector<int> v(10);
  fill(v.begin(), v.end(), 42);

  EXAM_CHECK(v[0]==42);
  EXAM_CHECK(v[1]==42);
  EXAM_CHECK(v[2]==42);
  EXAM_CHECK(v[3]==42);
  EXAM_CHECK(v[4]==42);
  EXAM_CHECK(v[5]==42);
  EXAM_CHECK(v[6]==42);
  EXAM_CHECK(v[7]==42);
  EXAM_CHECK(v[8]==42);
  EXAM_CHECK(v[9]==42);

  return EXAM_RESULT;
}

int EXAM_IMPL(fill_test::filln1)
{
  vector<int> v(10);
  fill_n(v.begin(), v.size(), 42);

  EXAM_CHECK(v[0]==42);
  EXAM_CHECK(v[1]==42);
  EXAM_CHECK(v[2]==42);
  EXAM_CHECK(v[3]==42);
  EXAM_CHECK(v[4]==42);
  EXAM_CHECK(v[5]==42);
  EXAM_CHECK(v[6]==42);
  EXAM_CHECK(v[7]==42);
  EXAM_CHECK(v[8]==42);
  EXAM_CHECK(v[9]==42);

  return EXAM_RESULT;
}

int EXAM_IMPL(search_test::search0)
{
  int v1[6] = { 1, 1, 2, 3, 5, 8 };
  int v2[6] = { 0, 1, 2, 3, 4, 5 };
  int v3[2] = { 3, 4 };

  int* location;
  location = search((int*)v1, (int*)v1 + 6, (int*)v3, (int*)v3 + 2);
  EXAM_CHECK(location == v1 + 6);

  location = search((int*)v2, (int*)v2 + 6, (int*)v3, (int*)v3 + 2);
  EXAM_CHECK(location != v2 + 6);
  EXAM_CHECK(location - v2 == 3);

  return EXAM_RESULT;
}

int EXAM_IMPL(search_test::search1)
{
  typedef vector <int> IntVec;
  IntVec v1(10);
  __iota(v1.begin(), v1.end(), 0);
  IntVec v2(3);
  __iota(v2.begin(), v2.end(), 50);

  IntVec::iterator location;
  location = search(v1.begin(), v1.end(), v2.begin(), v2.end());

  EXAM_CHECK(location == v1.end());

  __iota(v2.begin(), v2.end(), 4);

  location = search(v1.begin(), v1.end(), v2.begin(), v2.end());

  EXAM_CHECK(location != v1.end());
  EXAM_CHECK(location - v1.begin() == 4);

  return EXAM_RESULT;
}

int EXAM_IMPL(search_test::search2)
{
  char const* grades[] = { "A", "B", "C", "D", "F" };
  char const* letters[] = { "Q", "E", "D" };
  const unsigned gradeCount = sizeof(grades) / sizeof(grades[0]);
  const unsigned letterCount = sizeof(letters) / sizeof(letters[0]);
  char const** location = search((char const**)grades, (char const**)grades + gradeCount, (char const**)letters, (char const**)letters + letterCount, str_equal);

  EXAM_CHECK(location == grades + gradeCount);

  copy((char const**)grades + 1, (char const**)grades + 1 + letterCount, (char const**)letters);
  location = search((char const**)grades, (char const**)grades + gradeCount, (char const**)letters, (char const**)letters + letterCount, str_equal);

  EXAM_CHECK(location != grades + gradeCount);
  EXAM_CHECK(location - grades == 1);

  return EXAM_RESULT;
}

bool str_equal(const char* a_, const char* b_)
{
  return strcmp(a_, b_) == 0 ? 1 : 0;
}

int EXAM_IMPL(mismatch_test::mismatch0)
{
  int n1[5] = { 1, 2, 3, 4, 5 };
  int n2[5] = { 1, 2, 3, 4, 5 };
  int n3[5] = { 1, 2, 3, 2, 1 };

  pair <int*, int*> result = mismatch((int*)n1, (int*)n1 + 5, (int*)n2);
  EXAM_CHECK(result.first ==(n1 + 5) && result.second ==(n2 + 5));

  result = mismatch((int*)n1, (int*)n1 + 5, (int*)n3);
  EXAM_CHECK(!(result.first ==(n1 + 5) && result.second ==(n3 + 5)));
  EXAM_CHECK((result.first - n1)==3);

  return EXAM_RESULT;
}

int EXAM_IMPL(mismatch_test::mismatch1)
{
  typedef vector<int> IntVec;
  IntVec v1(10);
  __iota(v1.begin(), v1.end(), 0);
  IntVec v2(v1);

  pair <IntVec::iterator, IntVec::iterator> result = mismatch(v1.begin(), v1.end(), v2.begin());

  EXAM_CHECK(result.first == v1.end() && result.second == v2.end());

  v2[v2.size()/2] = 42;
  result = mismatch(v1.begin(), v1.end(), v2.begin());
  EXAM_CHECK(!(result.first == v1.end() && result.second == v2.end()));
  EXAM_CHECK((result.first - v1.begin())==5);

  return EXAM_RESULT;
}

int EXAM_IMPL(mismatch_test::mismatch2)
{
  const unsigned size = 5;
  char const* n1[size] = { "Brett", "Graham", "Jack", "Mike", "Todd" };

  char const* n2[size];
  copy(n1, n1 + 5, (char const**)n2);
  pair <char const**, char const**> result = mismatch((char const**)n1, (char const**)n1 + size, (char const**)n2, str_equal);

  EXAM_CHECK(result.first == n1 + size && result.second == n2 + size);

  n2[2] = "QED";
  result = mismatch((char const**)n1, (char const**)n1 + size, (char const**)n2, str_equal);
  EXAM_CHECK(!(result.first == n2 + size && result.second == n2 + size));
  EXAM_CHECK((result.first - n1)==2);

  return EXAM_RESULT;
}

int EXAM_IMPL(adj_test::adjfind0)
{
  int numbers1 [5] = { 1, 2, 4, 8, 16 };
  int numbers2 [5] = { 5, 3, 2, 1, 1 };

  int* location = adjacent_find((int*)numbers1, (int*)numbers1 + 5);
  EXAM_CHECK(location == numbers1 + 5); // no adj so loc should be _last

  location = adjacent_find((int*)numbers2, (int*)numbers2 + 5);
  EXAM_CHECK(location != numbers2 + 5); // adj location off should be 3 (first 1)
  EXAM_CHECK((location - numbers2)==3);

  return EXAM_RESULT;
}

int EXAM_IMPL(adj_test::adjfind1)
{
  typedef vector<int> IntVector;
  IntVector v(10);

  for ( int i = 0; (size_t)i < v.size(); ++i ) {
    v[i] = i;
  }

  IntVector::iterator location;
  location = adjacent_find(v.begin(), v.end());
  EXAM_CHECK(location == v.end());
  v[6] = 7;
  location = adjacent_find(v.begin(), v.end());
  EXAM_CHECK(location != v.end());

  return EXAM_RESULT;
}

int EXAM_IMPL(adj_test::adjfind2)
{
  typedef vector <const char*> CStrVector;

  const char* names[] = { "Brett", "Graham", "Jack", "Mike", "Todd" };

  const int nameCount = sizeof(names)/sizeof(names[0]);
  CStrVector v(nameCount);

  for( int i = 0; i < nameCount; i++ ) {
    v[i] = names[i];
  }

  CStrVector::iterator location;
  location = adjacent_find(v.begin(), v.end(), equal_length);

  EXAM_CHECK(location != v.end());

  return EXAM_RESULT;
}

int adj_test::equal_length(const char* v1_, const char* v2_)
{
  return ::strlen(v1_) == ::strlen(v2_);
}

int EXAM_IMPL(adj_test::adjdiff0)
{
  int numbers[5] = { 1, 2, 4, 8, 16 };
  int difference[5];

  adjacent_difference(numbers, numbers + 5, (int*)difference);

  EXAM_CHECK(difference[0]==1);
  EXAM_CHECK(difference[1]==1);
  EXAM_CHECK(difference[2]==2);
  EXAM_CHECK(difference[3]==4);
  EXAM_CHECK(difference[4]==8);

  return EXAM_RESULT;
}

int EXAM_IMPL(adj_test::adjdiff1)
{
  vector<int> v(10);

  for( int i = 0; (size_t)i < v.size(); ++i ) {
    v[i] = i * i;
  }

  vector<int> result(v.size());

  adjacent_difference(v.begin(), v.end(), result.begin());
  EXAM_CHECK(result[0]==0);
  EXAM_CHECK(result[1]==1);
  EXAM_CHECK(result[2]==3);
  EXAM_CHECK(result[3]==5);
  EXAM_CHECK(result[4]==7);
  EXAM_CHECK(result[5]==9);
  EXAM_CHECK(result[6]==11);
  EXAM_CHECK(result[7]==13);
  EXAM_CHECK(result[8]==15);
  EXAM_CHECK(result[9]==17);

  return EXAM_RESULT;
}

int EXAM_IMPL(adj_test::adjdiff2)
{
  vector <int> v(10);
  for ( int i = 0; (size_t)i < v.size(); ++i ) {
    v[i] = i + 1;
  }

  vector<int> result(v.size());

  adjacent_difference(v.begin(), v.end(), result.begin(), mult);

  EXAM_CHECK(result[0]==1);
  EXAM_CHECK(result[1]==2);
  EXAM_CHECK(result[2]==6);
  EXAM_CHECK(result[3]==12);
  EXAM_CHECK(result[4]==20);
  EXAM_CHECK(result[5]==30);
  EXAM_CHECK(result[6]==42);
  EXAM_CHECK(result[7]==56);
  EXAM_CHECK(result[8]==72);
  EXAM_CHECK(result[9]==90);

  return EXAM_RESULT;
}

int adj_test::mult(int a_, int b_)
{
  return a_ * b_;
}

int EXAM_IMPL(find_test::find0)
{
  int numbers[10] = { 0, 1, 4, 9, 16, 25, 36, 49, 64 };

  int *location = find((int*)numbers, (int*)numbers + 10, 25);

  EXAM_CHECK((location - numbers)==5);

  int *out_range = find((int*)numbers, (int*)numbers + 10, 128);

  EXAM_CHECK( out_range == (int *)(numbers + 10) );

  return EXAM_RESULT;
}

struct Key
{
  int data;

  /* This operator should rather be global and commutative
     but implementing it this way show that STLport used to
     ask too much from the user code. */
  bool operator == (int d) const
  {
    return data == d;
  }
};

int EXAM_IMPL(find_test::find1)
{
  int years[] = { 1942, 1952, 1962, 1972, 1982, 1992 };

  const unsigned yearCount = sizeof(years) / sizeof(years[0]);
  int* location = find((int*)years, (int*)years + yearCount, 1972);

  EXAM_CHECK((location - years)==3);

  return EXAM_RESULT;
}

int EXAM_IMPL(find_test::findif0)
{
  {
    int numbers[6] = { 2, 4, 8, 15, 32, 64 };
    int *location = find_if((int*)numbers, (int*)numbers + 6, odd);

    EXAM_CHECK((location - numbers)==3);

    int numbers_even[6] = { 2, 4, 8, 16, 32, 64 };

    int *out_range = find_if((int*)numbers_even, (int*)numbers_even + 6, odd);

    EXAM_CHECK( out_range == (int *)(numbers_even + 6) );
  }

  {
    Key keys[10] = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} };
    Key const* k = find(keys + 0, keys + 10, 5);
    EXAM_CHECK( k == keys + 10 );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(find_test::findif1)
{
  typedef vector <int> IntVec;
  IntVec v(10);

  for( int i = 0; (size_t)i < v.size(); ++i ) {
    v[i] = (i + 1) * (i + 1);
  }

  IntVec::iterator iter = find_if(v.begin(), v.end(), div_3);

  EXAM_CHECK((iter - v.begin())==2);

  return EXAM_RESULT;
}

bool find_test::odd(int a_)
{
  return (a_ % 2) != 0;
}

bool find_test::div_3(int a_)
{
  return a_ % 3 ? 0 : 1;
}

int EXAM_IMPL(find_test::find_char)
{
  char str[] = "abcdefghij";
  char *pstr = (char*)str;
  const char* cpstr = (const char*)str;
  size_t str_size = sizeof(str) / sizeof(char);

  char *d = find(pstr, pstr + str_size, 'd');
  EXAM_CHECK( *d == 'd' );

  const char *e = find(cpstr, cpstr + str_size, 'e');
  EXAM_CHECK( *e == 'e' );

  char *last = find(pstr, pstr + str_size, 'x');
  EXAM_CHECK( last == pstr + str_size );

  const char *clast = find(cpstr, cpstr + str_size, 'x');
  EXAM_CHECK( clast == cpstr + str_size );

  return EXAM_RESULT;
}

int EXAM_IMPL(advance_test::adv)
{
  typedef vector<int> IntVector;
  IntVector v(10);

  for ( int i = 0; (size_t)i < v.size(); ++i ) {
    v[i] = i;
  }
  IntVector::iterator location = v.begin();

  EXAM_CHECK(*location==0);
  advance(location, 5);
  EXAM_CHECK(*location==5);

  return EXAM_RESULT;
}

int EXAM_IMPL(swap_test::swap1)
{
  int a = 42;
  int b = 19;

  swap(a, b);

  EXAM_CHECK(a==19);
  EXAM_CHECK(b==42);

  return EXAM_RESULT;
}

int EXAM_IMPL(swap_test::swprnge1)
{
  char word1[] = "World";
  char word2[] = "Hello";

  swap_ranges((char*)word1, (char*)word1 + ::strlen(word1), (char*)word2);

  EXAM_CHECK(!strcmp(word1, "Hello"));
  EXAM_CHECK(!strcmp(word2, "World"));

  return EXAM_RESULT;
}

class Obj
{
  public:
    Obj() :
        v( 0 )
      { }
    Obj( const Obj& ) :
        v( 1 )
      { }

    Obj& operator =( const Obj& )
      { v = 2; return *this; }

    int v;
};

/*
 * Following two tests check the corectness of specialization of swap():
 * for containers with container::swap method swap( a, b ) should
 * use a.swap( b ), but don't try to do this substitution for container
 * without swap method (in this case swap should be made via explicit members
 * exchange; this assume usage of temporary object)
 *
 */
int EXAM_IMPL(swap_test::swap_container_non_spec)
{
  queue<Obj> v1;
  queue<Obj> v2;

  v1.push( Obj() );
  v1.back().v = -1;
  v1.push( Obj() );
  v1.back().v = -2;

  v2.push( Obj() );
  v2.back().v = 10;  
  v2.push( Obj() );
  v2.back().v = 11;
  v2.push( Obj() );
  v2.back().v = 12;

  EXAM_CHECK( v1.size() == 2 );
  EXAM_CHECK( v2.size() == 3 );

  swap( v1, v2 ); // this shouldn't try make it as v1.swap( v2 ), no queue::swap method!

  EXAM_CHECK( v1.size() == 3 );
  EXAM_CHECK( v2.size() == 2 );

  // either copy constructor or assignment operator
  EXAM_CHECK( v1.front().v == 1 || v1.front().v == 2 );
  EXAM_CHECK( v1.back().v == 1 || v1.back().v == 2 );
  EXAM_CHECK( v2.front().v == 1 || v2.front().v == 2 );
  EXAM_CHECK( v2.back().v == 1 || v2.back().v == 2 );

  return EXAM_RESULT;
}

int EXAM_IMPL(swap_test::swap_container_spec)
{
#if 0 /* temporary: investigation of problem with swap */
  if ( typeid(/* _STLP_PRIV */ _SwapImplemented<vector<Obj> >::_Ret) == typeid(_STLP_PRIV __false_type) ) {
    cerr << "false type" << endl;
  } else if ( typeid(/* _STLP_PRIV */ _SwapImplemented<vector<Obj> >::_Ret) == typeid(_STLP_PRIV __true_type) ) {
    cerr << "true type" << endl;
  } else {
    cerr << "unknown type" << endl;
  }
#endif /* end of temporary */
#if !defined (STLPORT) || \
     defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER) || defined (_STLP_USE_PARTIAL_SPEC_WORKAROUND)
  vector<Obj> v1;
  vector<Obj> v2;

  v1.push_back( Obj() );
  v1.push_back( Obj() );

  v1[0].v = -1;
  v1[1].v = -2;

  v2.push_back( Obj() );
  v2.push_back( Obj() );
  v2.push_back( Obj() );

  v2[0].v = 10;
  v2[1].v = 11;
  v2[2].v = 12;

  EXAM_CHECK( v1.size() == 2 );
  EXAM_CHECK( v2.size() == 3 );

  swap( v1, v2 ); // this should has effect v1.swap( v2 )

  EXAM_CHECK( v1.size() == 3 );
  EXAM_CHECK( v2.size() == 2 );

  EXAM_CHECK( v1[0].v == 10 );
  EXAM_CHECK( v1[1].v == 11 );
  EXAM_CHECK( v1[2].v == 12 );

  EXAM_CHECK( v2[0].v == -1 );
  EXAM_CHECK( v2[1].v == -2 );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

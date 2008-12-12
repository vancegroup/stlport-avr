// -*- C++ -*- Time-stamp: <08/12/12 22:23:14 ptr>

/*
 * Copyright (c) 2004-2008
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
#include <deque>
#include <functional>
#include <map>
#include <string>

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

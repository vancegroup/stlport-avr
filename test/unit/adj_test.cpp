#include "adj_test.h"

#include <vector>
#include <numeric>
#include <algorithm>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

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
  for (int i = 0; (size_t)i < v.size(); ++i)
    v[i] = i;
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
  for(int i = 0; i < nameCount; i++)
    v[i] = names[i];
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
  vector <int> v(10);
  for(int i = 0; (size_t)i < v.size(); ++i)
    v[i] = i * i;
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
  for (int i = 0; (size_t)i < v.size(); ++i)
    v[i] = i + 1;
  vector <int> result(v.size());
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

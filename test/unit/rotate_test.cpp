#include "rotate_test.h"

#include <numeric>
#include <vector>
#include <algorithm>

#include "iota.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(rotate_test::rotate0)
{
  int numbers[6] = { 0, 1, 2, 3, 4, 5 };
  // 3 4 5 0 1 2
  rotate((int*)numbers, numbers + 3, numbers + 6);
  EXAM_CHECK(numbers[0]==3);
  EXAM_CHECK(numbers[1]==4);
  EXAM_CHECK(numbers[2]==5);
  EXAM_CHECK(numbers[3]==0);
  EXAM_CHECK(numbers[4]==1);
  EXAM_CHECK(numbers[5]==2);

  return EXAM_RESULT;
}

int EXAM_IMPL(rotate_test::rotate1)
{
  vector <int> v1(10);
  __iota(v1.begin(), v1.end(), 0);

  rotate(v1.begin(), v1.begin()+1, v1.end());
  EXAM_CHECK(v1[0]==1);
  EXAM_CHECK(v1[1]==2);
  EXAM_CHECK(v1[2]==3);
  EXAM_CHECK(v1[3]==4);
  EXAM_CHECK(v1[4]==5);
  EXAM_CHECK(v1[5]==6);
  EXAM_CHECK(v1[6]==7);
  EXAM_CHECK(v1[7]==8);
  EXAM_CHECK(v1[8]==9);
  EXAM_CHECK(v1[9]==0);

  rotate(v1.begin(), v1.begin()+2, v1.end());
  EXAM_CHECK(v1[0]==3);
  EXAM_CHECK(v1[1]==4);
  EXAM_CHECK(v1[2]==5);
  EXAM_CHECK(v1[3]==6);
  EXAM_CHECK(v1[4]==7);
  EXAM_CHECK(v1[5]==8);
  EXAM_CHECK(v1[6]==9);
  EXAM_CHECK(v1[7]==0);
  EXAM_CHECK(v1[8]==1);
  EXAM_CHECK(v1[9]==2);

  rotate(v1.begin(), v1.begin()+7, v1.end());
  EXAM_CHECK(v1[0]==0);
  EXAM_CHECK(v1[1]==1);
  EXAM_CHECK(v1[2]==2);
  EXAM_CHECK(v1[3]==3);
  EXAM_CHECK(v1[4]==4);
  EXAM_CHECK(v1[5]==5);
  EXAM_CHECK(v1[6]==6);
  EXAM_CHECK(v1[7]==7);
  EXAM_CHECK(v1[8]==8);
  EXAM_CHECK(v1[9]==9);

  return EXAM_RESULT;
}

int EXAM_IMPL(rotate_test::rotcopy0)
{
  int numbers[6] = { 0, 1, 2, 3, 4, 5 };

  int result[6];
  rotate_copy((int*)numbers, (int*)numbers + 3, (int*)numbers + 6, (int*)result);
  // 3 4 5 0 1 2
  EXAM_CHECK(result[0]==3);
  EXAM_CHECK(result[1]==4);
  EXAM_CHECK(result[2]==5);
  EXAM_CHECK(result[3]==0);
  EXAM_CHECK(result[4]==1);
  EXAM_CHECK(result[5]==2);

  return EXAM_RESULT;
}

int EXAM_IMPL(rotate_test::rotcopy1)
{
  vector <int> v1(10);
  __iota(v1.begin(), v1.end(), 0);
  vector <int> v2(v1.size());

  rotate_copy(v1.begin(), v1.begin()+1, v1.end(), v2.begin());
  EXAM_CHECK(v2[0]==1);
  EXAM_CHECK(v2[1]==2);
  EXAM_CHECK(v2[2]==3);
  EXAM_CHECK(v2[3]==4);
  EXAM_CHECK(v2[4]==5);
  EXAM_CHECK(v2[5]==6);
  EXAM_CHECK(v2[6]==7);
  EXAM_CHECK(v2[7]==8);
  EXAM_CHECK(v2[8]==9);
  EXAM_CHECK(v2[9]==0);

  rotate_copy(v1.begin(), v1.begin()+3, v1.end(), v2.begin());
  EXAM_CHECK(v2[0]==3);
  EXAM_CHECK(v2[1]==4);
  EXAM_CHECK(v2[2]==5);
  EXAM_CHECK(v2[3]==6);
  EXAM_CHECK(v2[4]==7);
  EXAM_CHECK(v2[5]==8);
  EXAM_CHECK(v2[6]==9);
  EXAM_CHECK(v2[7]==0);
  EXAM_CHECK(v2[8]==1);
  EXAM_CHECK(v2[9]==2);

  return EXAM_RESULT;
}

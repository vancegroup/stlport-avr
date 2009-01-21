#include "partition_test.h"

#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iterator>
#include <functional>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(partition_test::stblptn0)
{
  int numbers[6] = { 10, 5, 11, 20, 6, -2 };

  size_t nb_pred_calls = 0;
  stable_partition((int*)numbers, (int*)numbers + 6, less_n(10, nb_pred_calls));
  // 5 6 -2 10 11 20
  EXAM_CHECK(numbers[0]==5);
  EXAM_CHECK(numbers[1]==6);
  EXAM_CHECK(numbers[2]==-2);
  EXAM_CHECK(numbers[3]==10);
  EXAM_CHECK(numbers[4]==11);
  EXAM_CHECK(numbers[5]==20);

  //Complexity check:
  EXAM_CHECK( nb_pred_calls == sizeof(numbers) / sizeof(numbers[0]) );

  return EXAM_RESULT;
}

int EXAM_IMPL(partition_test::stblptn1)
{
  //5 5 2 10 0 12 5 0 0 19
  //5 5 2 10 0 5 0 0 12 19
  int numbers[] = { 5, 5, 2, 10, 0, 12, 5, 0, 0, 19 };
  vector <int> v1(numbers, numbers+10);

  size_t nb_pred_calls = 0;
  stable_partition(v1.begin(), v1.end(), less_n(11, nb_pred_calls));

  EXAM_CHECK(v1[0]==5);
  EXAM_CHECK(v1[1]==5);
  EXAM_CHECK(v1[2]==2);
  EXAM_CHECK(v1[3]==10);
  EXAM_CHECK(v1[4]==0);
  EXAM_CHECK(v1[5]==5);
  EXAM_CHECK(v1[6]==0);
  EXAM_CHECK(v1[7]==0);
  EXAM_CHECK(v1[8]==12);
  EXAM_CHECK(v1[9]==19);
  EXAM_CHECK( nb_pred_calls == v1.size() );

  return EXAM_RESULT;
}

int EXAM_IMPL(partition_test::ptition0)
{
  int numbers[6] = { 6, 12, 3, 10, 1, 20 };
  size_t nb_pred_calls = 0;
  // 6 1 3 10 12 20
  partition((int*)numbers, (int*)numbers + 6, less_n(10, nb_pred_calls));
  EXAM_CHECK(numbers[0]==6);
  EXAM_CHECK(numbers[1]==1);
  EXAM_CHECK(numbers[2]==3);
  EXAM_CHECK(numbers[3]==10);
  EXAM_CHECK(numbers[4]==12);
  EXAM_CHECK(numbers[5]==20);

  EXAM_CHECK( nb_pred_calls == sizeof(numbers) / sizeof(numbers[0]) );

  return EXAM_RESULT;
}

int EXAM_IMPL(partition_test::ptition1)
{
  // 19 3 11 14 10 19 8 17 9 6
  // 6 3 9 8 10 19 14 17 11 19

  int numbers[10] ={ 19, 3, 11, 14, 10, 19, 8, 17, 9, 6 };

  vector <int> v1(numbers, numbers+10);
  size_t nb_pred_calls = 0;
  partition(v1.begin(), v1.end(), less_n(11, nb_pred_calls));

  EXAM_CHECK(v1[0]==6);
  EXAM_CHECK(v1[1]==3);
  EXAM_CHECK(v1[2]==9);
  EXAM_CHECK(v1[3]==8);
  EXAM_CHECK(v1[4]==10);
  EXAM_CHECK(v1[5]==19);
  EXAM_CHECK(v1[6]==14);
  EXAM_CHECK(v1[7]==17);
  EXAM_CHECK(v1[8]==11);
  EXAM_CHECK(v1[9]==19);
  EXAM_CHECK( nb_pred_calls == v1.size() );

  return EXAM_RESULT;
}

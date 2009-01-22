#include "unique_test.h"

#include <algorithm>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

static bool str_equal(const char* a_, const char* b_)
{ return *a_ == *b_; }

int EXAM_IMPL(unique_test::unique1)
{
  int numbers[8] = { 0, 1, 1, 2, 2, 2, 3, 4 };
  unique((int*)numbers, (int*)numbers + 8);
  // 0 1 2 3 4 2 3 4
  EXAM_CHECK(numbers[0]==0);
  EXAM_CHECK(numbers[1]==1);
  EXAM_CHECK(numbers[2]==2);
  EXAM_CHECK(numbers[3]==3);
  EXAM_CHECK(numbers[4]==4);
  EXAM_CHECK(numbers[5]==2);
  EXAM_CHECK(numbers[6]==3);
  EXAM_CHECK(numbers[7]==4);

  return EXAM_RESULT;
}

int EXAM_IMPL(unique_test::unique2)
{
  const char* labels[] = {"Q", "Q", "W", "W", "E", "E", "R", "T", "T", "Y", "Y"};

  const unsigned count = sizeof(labels) / sizeof(labels[0]);

  unique((const char**)labels, (const char**)labels + count, str_equal);

  // QWERTY
  EXAM_CHECK(*labels[0] == 'Q');
  EXAM_CHECK(*labels[1] == 'W');
  EXAM_CHECK(*labels[2] == 'E');
  EXAM_CHECK(*labels[3] == 'R');
  EXAM_CHECK(*labels[4] == 'T');
  EXAM_CHECK(*labels[5] == 'Y');

  return EXAM_RESULT;
}

int EXAM_IMPL(unique_test::uniqcpy1)
{
  int numbers[8] = { 0, 1, 1, 2, 2, 2, 3, 4 };
  int result[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

  unique_copy((int*)numbers, (int*)numbers + 8, (int*)result);

  // 0 1 2 3 4 0 0 0
  EXAM_CHECK(result[0]==0);
  EXAM_CHECK(result[1]==1);
  EXAM_CHECK(result[2]==2);
  EXAM_CHECK(result[3]==3);
  EXAM_CHECK(result[4]==4);
  EXAM_CHECK(result[5]==0);
  EXAM_CHECK(result[6]==0);
  EXAM_CHECK(result[7]==0);

  return EXAM_RESULT;
}

int EXAM_IMPL(unique_test::uniqcpy2)
{
  const char* labels[] = {"Q", "Q", "W", "W", "E", "E", "R", "T", "T", "Y", "Y"};
  const char **plabels = (const char**)labels;

  const size_t count = sizeof(labels) / sizeof(labels[0]);
  const char* uCopy[count];
  const char **puCopy = &uCopy[0];
  fill(puCopy, puCopy + count, "");

  unique_copy(plabels, plabels + count, puCopy, str_equal);

  //QWERTY
  EXAM_CHECK(*uCopy[0] == 'Q');
  EXAM_CHECK(*uCopy[1] == 'W');
  EXAM_CHECK(*uCopy[2] == 'E');
  EXAM_CHECK(*uCopy[3] == 'R');
  EXAM_CHECK(*uCopy[4] == 'T');
  EXAM_CHECK(*uCopy[5] == 'Y');

  return EXAM_RESULT;
}

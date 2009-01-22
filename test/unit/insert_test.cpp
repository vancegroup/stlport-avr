#include "iter_test.h"

#include <deque>
#include <vector>
#include <algorithm>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(insert_iter_test::insert1)
{
  char const* array1 [] = { "laurie", "jennifer", "leisa" };
  char const* array2 [] = { "amanda", "saskia", "carrie" };

  deque<char const*> names(array1, array1 + 3);
  deque<char const*>::iterator i = names.begin() + 2;

  insert_iterator<deque <char const*> > itd(names, i);
  itd = copy(array2, array2 + 3, insert_iterator<deque <char const*> >(names, i));

  EXAM_CHECK( !strcmp(names[0], "laurie") );
  EXAM_CHECK( !strcmp(names[1], "jennifer") );
  EXAM_CHECK( !strcmp(names[2], "amanda") );
  EXAM_CHECK( !strcmp(names[3], "saskia") );
  EXAM_CHECK( !strcmp(names[4], "carrie") );
  EXAM_CHECK( !strcmp(names[5], "leisa") );

  copy(array1, array1 + 3, itd);
  EXAM_CHECK( !strcmp(names[5], "laurie") );
  EXAM_CHECK( !strcmp(names[6], "jennifer") );
  EXAM_CHECK( !strcmp(names[7], "leisa") );
  EXAM_CHECK( !strcmp(names[8], "leisa") );

  return EXAM_RESULT;
}

int EXAM_IMPL(insert_iter_test::insert2)
{
  char const* array1 [] = { "laurie", "jennifer", "leisa" };
  char const* array2 [] = { "amanda", "saskia", "carrie" };

  deque<char const*> names(array1, array1 + 3);
  deque<char const*>::iterator i = names.begin() + 2;
  copy(array2, array2 + 3, inserter(names, i));

  EXAM_CHECK( !strcmp(names[0], "laurie") );
  EXAM_CHECK( !strcmp(names[1], "jennifer") );
  EXAM_CHECK( !strcmp(names[2], "amanda") );
  EXAM_CHECK( !strcmp(names[3], "saskia") );
  EXAM_CHECK( !strcmp(names[4], "carrie") );
  EXAM_CHECK( !strcmp(names[5], "leisa") );

  return EXAM_RESULT;
}

int EXAM_IMPL(binsert_iter_test::binsert1)
{
  const char* array [] = { "laurie", "jennifer", "leisa" };
  vector<const char*> names;
  back_insert_iterator<vector<const char*> > bit(names);
  bit = copy(array, array + 3, bit);

  EXAM_CHECK(!strcmp(names[0],array[0]));
  EXAM_CHECK(!strcmp(names[1],array[1]));
  EXAM_CHECK(!strcmp(names[2],array[2]));

  copy(array, array + 3, bit);
  EXAM_CHECK(!strcmp(names[3],array[0]));
  EXAM_CHECK(!strcmp(names[4],array[1]));
  EXAM_CHECK(!strcmp(names[5],array[2]));

  return EXAM_RESULT;
}

int EXAM_IMPL(binsert_iter_test::binsert2)
{
  const char* array [] = { "laurie", "jennifer", "leisa" };
  vector<const char*> names;
  copy(array, array + 3, back_inserter(names));
  EXAM_CHECK(!strcmp(names[0],array[0]));
  EXAM_CHECK(!strcmp(names[1],array[1]));
  EXAM_CHECK(!strcmp(names[2],array[2]));

  return EXAM_RESULT;
}

int EXAM_IMPL(finsert_iter_test::finsert1)
{
  char const* array [] = { "laurie", "jennifer", "leisa" };
  deque<char const*> names;
  front_insert_iterator<deque<char const*> > fit(names);
  fit = copy(array, array + 3, front_insert_iterator<deque <char const*> >(names));

  EXAM_CHECK(names[0]==array[2]);
  EXAM_CHECK(names[1]==array[1]);
  EXAM_CHECK(names[2]==array[0]);

  copy(array, array + 3, fit);
  EXAM_CHECK(names[3]==array[2]);
  EXAM_CHECK(names[4]==array[1]);
  EXAM_CHECK(names[5]==array[0]);

  return EXAM_RESULT;
}

int EXAM_IMPL(finsert_iter_test::finsert2)
{
  char const* array [] = { "laurie", "jennifer", "leisa" };

  deque<char const*> names;
  copy(array, array + 3, front_inserter(names));

  EXAM_CHECK(names[0]==array[2]);
  EXAM_CHECK(names[1]==array[1]);
  EXAM_CHECK(names[2]==array[0]);

  return EXAM_RESULT;
}

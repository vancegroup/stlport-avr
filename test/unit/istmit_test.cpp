#include "iter_test.h"

#include <algorithm>
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <sstream>
#  include <functional>
#  include <iterator>
#  include <vector>
#  include <string>
#endif

using namespace std;

typedef istream_iterator<char> istream_char_ite;
typedef istream_iterator<int> istream_int_ite;
typedef istream_iterator<string> istream_string_ite;

int EXAM_IMPL(istream_iterator_test::istmit1)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
  const char* buff = "MyString";
  istringstream istr(buff);

  char buffer[100];
  size_t i = 0;
  istr.unsetf(ios::skipws); // Disable white-space skipping.
  istream_char_ite s(istr), meos;
  while (!(s == meos)  &&
  //*TY 01/10/1999 - added end of stream check
  // NOTE operator!= should not be used here ifndef _STLP_FUNCTION_TMPL_PARTIAL_ORDER
         (*s != '\n') &&
         (i < sizeof(buffer) / sizeof(buffer[0]))) {  //*TY 07/28/98 - added index check
    buffer[i++] = *s++;
  }
  buffer[i] = '\0'; // Null terminate buffer.

  EXAM_CHECK(!strcmp(buffer, buff));

  {
    istringstream empty_istr;
    EXAM_CHECK( istream_char_ite(empty_istr) == istream_char_ite() );
  }

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(istream_iterator_test::copy_n_test)
{
  //This test check that no character is lost while reading the istream
  //through a istream_iterator.
  {
    istringstream istr("aabbcd");
    string chars;
    back_insert_iterator<string> ite = copy_n(istream_char_ite(istr), 2, back_inserter(chars));
    ite = copy_n(istream_char_ite(istr), 2, ite);
    EXAM_CHECK( chars == "aabb" );
    copy_n(istream_char_ite(istr), 2, ite);
    EXAM_CHECK( chars == "aabbcd" );
  }

  {
    istringstream istr("11 22 AA BB 33 44 CC DD");
    vector<int> ints;
    vector<string> strings;

    copy_n(istream_int_ite(istr), 2, back_inserter(ints));
    EXAM_CHECK( ints.size() == 2 );
    EXAM_CHECK( ints[0] == 11 );
    EXAM_CHECK( ints[1] == 22 );
    ints.clear();
    istr.clear();
    copy_n(istream_string_ite(istr), 2, back_inserter(strings));
    EXAM_CHECK( strings.size() == 2 );
    EXAM_CHECK( strings[0] == "AA" );
    EXAM_CHECK( strings[1] == "BB" );
    strings.clear();
    istr.clear();
    /* The following code cannot work, '33' is extracted as a string
     * in the previous copy_n call, this value is returned in the pair
     * returned by copy_n but is lost as this istream_iterator is not used.
     * copy_n and istream_iterator can only be combined safely if:
     * - you always extract the same type of istream_iterator and you always reuse
     * the istream_iterator returned by copy_n (see previous test with "aabbcd")
     * - you extract different type of object and no object is convertible to an other
     * as in this current test when you extract int and string (when you extract ints
     * again it fails as int can be converted to strings.
     *
    copy_n(istream_int_ite(istr), 2, back_inserter(ints));
    EXAM_CHECK( ints.size() == 2 );
    EXAM_CHECK( ints[0] == 33 );
    EXAM_CHECK( ints[1] == 44 );
    istr.clear();
    copy_n(istream_string_ite(istr), 2, back_inserter(strings));
    EXAM_CHECK( strings.size() == 2 );
    EXAM_CHECK( strings[0] == "CC" );
    EXAM_CHECK( strings[1] == "DD" );
    */
  }

  {
    istringstream is("1 2 3 4 5 6 7 8 9 10");
    vector<int> ints;
    istream_iterator<int> itr(is);
    copy_n(itr, 0, back_inserter(ints));
    EXAM_CHECK( ints.empty() );
    copy_n(itr, -1, back_inserter(ints));
    EXAM_CHECK( ints.empty() );
    copy_n(itr, 2, back_inserter(ints));
    EXAM_CHECK( ints.size() == 2 );
    EXAM_CHECK( ints[0] == 1 );
    EXAM_CHECK( ints[1] == 2 );
    copy_n(itr, 2, back_inserter(ints));
    EXAM_CHECK( ints.size() == 4 );
    EXAM_CHECK( ints[2] == 3 );
    EXAM_CHECK( ints[3] == 4 );
    copy_n(itr, 2, back_inserter(ints));
    EXAM_CHECK( ints.size() == 6 );
    EXAM_CHECK( ints[4] == 5 );
    EXAM_CHECK( ints[5] == 6 );
  }

  return EXAM_RESULT;
}

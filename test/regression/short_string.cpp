// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <string>
#include <vector>
#include <iostream>

#ifdef MAIN 
#define short_string_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

char const* test (bool res) {
  return res?"success\n":"failure\n";
}

int short_string_test(int, char**)
{
  cout<<"Results of short_string_test:"<<endl;

  /*
   * Writing this test case, the short string size within STLport is 8 chars.
   * So we are going to use in this test 4 chars string as the short string
   * and 64 chars as the long one.
   */
  string const ref_short_str1("str1"), ref_short_str2("str2");
  string short_str1(ref_short_str1), short_str2(ref_short_str2);
  string const ref_long_str1("str                                                  1");
  string const ref_long_str2("str                                                  2");
  string long_str1(ref_long_str1), long_str2(ref_long_str2);

  {
    cout << "Copy constructor with short string: " << test(short_str1 == ref_short_str1);
    cout << "Copy constructor with long string: " << test(long_str1 == ref_long_str1);
  }

  {
    string str1(short_str1);
    str1 = long_str1;
    cout << "Assignment from long string to short: " << test(str1 == ref_long_str1);
  }

  {
    string str1(long_str1);
    str1 = short_str1;
    cout << "Assignment from short string to short: " << test(str1 == ref_short_str1);
  }

  {
    short_str1.swap(short_str2);
    cout << "Swap between short string: " << test((short_str1 == ref_short_str2) && (short_str2 == ref_short_str1));
    short_str1.swap(short_str2);
  }

  {
    long_str1.swap(long_str2);
    cout << "Swap between long string: " << test((long_str1 == ref_long_str2) && (long_str2 == ref_long_str1));
    long_str1.swap(long_str2);
  }

  {
    short_str1.swap(long_str1);
    cout << "Swap between short and long string: " << test((short_str1 == ref_long_str1) && (long_str1 == ref_short_str1));
    short_str1.swap(long_str1);
  }

  {
    long_str1.swap(short_str1);
    cout << "Swap between long and short string: " << test((short_str1 == ref_long_str1) && (long_str1 == ref_short_str1));
    long_str1.swap(short_str1);
  }

  {
    //This is to test move constructor
    vector<string> str_vect;
    str_vect.push_back(short_str1);
    str_vect.push_back(long_str1);
    str_vect.push_back(short_str2);
    str_vect.push_back(long_str2);
    cout << "Insertion within a vector: " << test((str_vect[0] == ref_short_str1) &&
                                                  (str_vect[1] == ref_long_str1) &&
                                                  (str_vect[2] == ref_short_str2) &&
                                                  (str_vect[3] == ref_long_str2));
  }

  {
    cout << "string display test: \n" << short_str1 << '\n' << long_str1 << '\n';
  }

  cout << endl;

  return 0;
}

// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <string>
#include <iostream>

#include "stl_test.h"

#ifdef MAIN 
#define string1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int string1_test(int, char**)
{
  cout<<"Results of string1_test:"<<endl;
  char* array = "Hello, World!";
  std::string v(array);
  size_t i;
  cout << v << endl;
  v.erase(v.begin() + 1, v.end() - 1); // Erase all but first and last.
  for(i = 0; i < v.size(); i++)
    cout << "v[" << i << "] = " << v[i] << endl;
  v.insert(1, (char*)array);
  v.erase(v.begin()); // Erase first element.
  v.erase(v.end() - 1); // Erase last element.
  cout << v << endl;
  v.clear(); // Erase all.

  const char* strorg = "This is test string for string calls";
  string str;
  //size it correctly to avoid reallocation
  str.reserve(100);
  str = strorg;

  //test self insertion:
  str.insert(10, str.c_str() + 5, 15);
  //Should be: This is teis test string st string for string calls
  cout << str;
  stlp_test(str == "This is teis test string st string for string calls");

  //An other one using an other implementation
  str = strorg;
  str.insert(15, str.c_str() + 5, 25);
  //Should be: This is test stis test string for stringring for string calls
  cout << str;
  stlp_test(str == "This is test stis test string for stringring for string calls");

  str = strorg;
  str.insert(0, str.c_str() + str.size() - 4, 4);
  //Should be: allsThis is test string for string calls
  cout << str;
  stlp_test(str == "allsThis is test string for string calls");

  str = strorg;
  str.insert(0, str.c_str() + str.size() / 2 - 1, str.size() / 2 + 1);
  //Should be: ng for string callsThis is test string for string calls
  cout << str;
  stlp_test(str == "ng for string callsThis is test string for string calls");

  str = strorg;
  str.replace(5, 15, str.c_str(), 10);
  //Should be: This This is tefor string calls
  cout << str;
  stlp_test(str == "This This is tefor string calls");

  str = strorg;
  str.replace(5, 5, str.c_str(), 10);
  //Should be: This This is test string for string calls
  cout << str;
  stlp_test(str == "This This is test string for string calls");
  
  cout << endl;

  return 0;
}

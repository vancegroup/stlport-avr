// STLport regression testsuite component.

#include "stlp_test.h"

#include <limits>
#include <iomanip>
#include <string>
#include <sstream>

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

bool check_float (float val, float ref) {
  float epsilon = numeric_limits<float>::epsilon();
  return val <= ref + epsilon && val >= ref - epsilon;
}

int float_input_test()
{
  float in_val;
  
  istringstream istr;

  istr.str("1.2345");
  istr >> in_val;
  STLP_CHECK(istr);
  STLP_CHECK(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("-1.2345");
  istr >> in_val;
  STLP_CHECK(istr);
  STLP_CHECK(check_float(in_val, -1.2345f));
  istr.clear();

  istr.str("+1.2345");
  istr >> in_val;
  STLP_CHECK(istr);
  STLP_CHECK(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("000000000000001.234500000000");
  istr >> in_val;
  STLP_CHECK(istr);
  STLP_CHECK(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("1.2345e+04");
  istr >> in_val;
  cout << endl << in_val << endl;
  STLP_CHECK(istr);
  STLP_CHECK(check_float(in_val, 12345.0f));
  istr.clear();

  return 0;
}

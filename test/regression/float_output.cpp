// STLport regression testsuite component.

#include "stlp_test.h"

#include <iomanip>
#include <sstream>

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

string reset_stream (ostringstream &ostr) {
  string tmp = ostr.str();
  ostr.str("");
  return tmp;
}

int float_output_test()
{
  ostringstream ostr;
  
  float test_val = 1.23457e+17;
  
  ostr << test_val;
  STLP_CHECK(reset_stream(ostr) == "1.23457e+17");

  ostr << fixed << test_val;
  STLP_CHECK(reset_stream(ostr) == "123456996677517312.000000");

  ostr << showpos << test_val;
  STLP_CHECK(reset_stream(ostr) == "+123456996677517312.000000");

  ostr << setprecision(500) << test_val;
  STLP_CHECK(reset_stream(ostr) == "+123456996677517312.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
  
  ostr << noshowpos << scientific;

  test_val = 0.12345678f;
  ostr << setprecision(8) << test_val;
  STLP_CHECK(reset_stream(ostr) == "1.23456784e-01");
  
  ostr << setw(30) << fixed << setfill('0') << test_val;
  STLP_CHECK(reset_stream(ostr) == "000000000000000000000.12345678");
  
  ostr << setw(30) << showpos << test_val;
  STLP_CHECK(reset_stream(ostr) == "0000000000000000000+0.12345678");
  
  ostr << setw(30) << left << test_val;
  STLP_CHECK(reset_stream(ostr) == "+0.123456780000000000000000000");

  ostr << setw(30) << internal << test_val;
  STLP_CHECK(reset_stream(ostr) == "+00000000000000000000.12345678");

  return 0;
}

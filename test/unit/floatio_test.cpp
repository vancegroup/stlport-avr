#include <limits>
#include <iomanip>
#include <string>
#include <sstream>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class FloatIOTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(FloatIOTest);
  CPPUNIT_TEST(float_input_test);
  CPPUNIT_TEST(float_output_test);
  CPPUNIT_TEST_SUITE_END();

protected:
  void float_input_test();
  void float_output_test();

  static bool check_float (float val, float ref) {
    float epsilon = numeric_limits<float>::epsilon();
    return val <= ref + epsilon && val >= ref - epsilon;
  }
  static string reset_stream (ostringstream &ostr) {
    string tmp = ostr.str();
    ostr.str("");
    return tmp;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(FloatIOTest);

//
// tests implementation
//
void FloatIOTest::float_output_test()
{
  ostringstream ostr;
  string output;
  
  ostr.precision(6);
  float test_val = (float)1.23457e+17;
  
  ostr << test_val;
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "1.23457e+17");

  ostr << fixed << test_val;
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output.size() == 25);
  CPPUNIT_ASSERT(output.substr(0, 5) == "12345");
  CPPUNIT_ASSERT(output.substr(18) == ".000000");

  ostr << showpos << test_val;
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output.size() == 26);
  CPPUNIT_ASSERT(output.substr(0, 6) == "+12345");
  CPPUNIT_ASSERT(output.substr(19) == ".000000");

  ostr << setprecision(500) << test_val;
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output.size() == 520);
  CPPUNIT_ASSERT(output.substr(0, 6) == "+12345");
  CPPUNIT_ASSERT(output.substr(19) == ".0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
  
  ostr << noshowpos << scientific;

  test_val = 0.12345678f;
  ostr << setprecision(8) << test_val;
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "1.23456784e-01");
  
  ostr << setw(30) << fixed << setfill('0') << test_val;
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "000000000000000000000.12345678");
  
  ostr << setw(30) << showpos << test_val;
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "0000000000000000000+0.12345678");
  
  ostr << setw(30) << left << test_val;
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "+0.123456780000000000000000000");

  ostr << setw(30) << internal << test_val;
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "+00000000000000000000.12345678");
}

void FloatIOTest::float_input_test()
{
  float in_val;
  
  istringstream istr;

  istr.str("1.2345");
  istr >> in_val;
  CPPUNIT_ASSERT(istr);
  CPPUNIT_ASSERT(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("-1.2345");
  istr >> in_val;
  CPPUNIT_ASSERT(istr);
  CPPUNIT_ASSERT(check_float(in_val, -1.2345f));
  istr.clear();

  istr.str("+1.2345");
  istr >> in_val;
  CPPUNIT_ASSERT(istr);
  CPPUNIT_ASSERT(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("000000000000001.234500000000");
  istr >> in_val;
  CPPUNIT_ASSERT(istr);
  CPPUNIT_ASSERT(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("1.2345e+04");
  istr >> in_val;
  CPPUNIT_ASSERT(istr);
  CPPUNIT_ASSERT(check_float(in_val, 12345.0f));
  istr.clear();
}

/*
int main (int argc, char *argv[]) {
  FloatIOTest test;
  test.float_output_test();
  test.float_input_test();
  return 0;
}
*/

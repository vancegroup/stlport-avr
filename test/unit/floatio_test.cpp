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
  
  float test_val = (float)1.23457e+17;
  
  ostr << test_val;
  CPPUNIT_ASSERT(reset_stream(ostr) == "1.23457e+17");

  ostr << fixed << test_val;
  CPPUNIT_ASSERT(reset_stream(ostr) == "123456996677517312.000000");

  ostr << showpos << test_val;
  CPPUNIT_ASSERT(reset_stream(ostr) == "+123456996677517312.000000");

  ostr << setprecision(500) << test_val;
  CPPUNIT_ASSERT(reset_stream(ostr) == "+123456996677517312.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                                                       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
  
  ostr << noshowpos << scientific;

  test_val = 0.12345678f;
  ostr << setprecision(8) << test_val;
  CPPUNIT_ASSERT(reset_stream(ostr) == "1.23456784e-01");
  
  ostr << setw(30) << fixed << setfill('0') << test_val;
  CPPUNIT_ASSERT(reset_stream(ostr) == "000000000000000000000.12345678");
  
  ostr << setw(30) << showpos << test_val;
  CPPUNIT_ASSERT(reset_stream(ostr) == "0000000000000000000+0.12345678");
  
  ostr << setw(30) << left << test_val;
  CPPUNIT_ASSERT(reset_stream(ostr) == "+0.123456780000000000000000000");

  ostr << setw(30) << internal << test_val;
  CPPUNIT_ASSERT(reset_stream(ostr) == "+00000000000000000000.12345678");
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

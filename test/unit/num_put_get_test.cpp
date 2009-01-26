#include "num_put_get_test.h"

#include <limits>

#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <iomanip>
#  include <string>
#  include <sstream>
#  include <cstdio>
/*
#  include <iostream>
#  include <ieee754.h>
*/
#  include "complete_digits.h"
#endif


#  if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#  endif

static bool check_float(float val, float ref)
{
  float epsilon = numeric_limits<float>::epsilon();
  return val <= ref + epsilon && val >= ref - epsilon;
}

static bool check_double(double val, double ref)
{
  double epsilon = numeric_limits<double>::epsilon();
  return val <= ref + epsilon && val >= ref - epsilon;
}

static string reset_stream(ostringstream &ostr)
{
  string tmp = ostr.str();
  ostr.str("");
  return tmp;
}

template <class F>
void check_get_float( F v )
{
  F in_val_d = v;
  typedef numeric_limits<F> limits;
  {
    stringstream str;

    str << "1E+" << limits::max_exponent10;

    str >> in_val_d;
    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( in_val_d == in_val_d );
    EXAM_CHECK( in_val_d != limits::infinity() );
  }
  {
    stringstream str;

    str << "-1E+" << limits::max_exponent10;

    str >> in_val_d;
    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( in_val_d == in_val_d );
    EXAM_CHECK( in_val_d != -limits::infinity() );
  }
  {
    stringstream str;

    str << "1E" << limits::min_exponent10;

    str >> in_val_d;
    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( in_val_d == in_val_d );
    EXAM_CHECK( in_val_d != F(0.0) );
  }
  {
    stringstream str;

    str << "1E+" << (limits::max_exponent10 + 1);

    str >> in_val_d;
    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( in_val_d == in_val_d );
    EXAM_CHECK( in_val_d == limits::infinity() );
  }
  {
    stringstream str;

    str << "-1E+" << (limits::max_exponent10 + 1);

    str >> in_val_d;
    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( in_val_d == in_val_d );
    EXAM_CHECK( in_val_d == -limits::infinity() );
  }
  {
    stringstream str;

    str << "1E" << (limits::min_exponent10 - 1);

    str >> in_val_d;
    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( in_val_d == in_val_d );
    EXAM_CHECK( in_val_d >= F(0.0) && in_val_d <= limits::min() );
  }
#if !defined (__MINGW32__)
  {
    stringstream str;

    str << limits::max();

    EXAM_CHECK(!str.fail());
    EXAM_CHECK( str.str() != "inf" );
    EXAM_CHECK( str.str() != "-inf" );
    EXAM_CHECK( str.str() != "nan" );
    EXAM_CHECK( str.str() != "-nan" );
    //EXAM_MESSAGE( str.str().c_str() );

    //str.str("");
    //str << limits::max_exponent10;
    //EXAM_MESSAGE( str.str().c_str() );

    str >> in_val_d;

    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( in_val_d == in_val_d );
    EXAM_CHECK( in_val_d != limits::infinity() );
  }
  {
    stringstream str;

    str << fixed << limits::max();

    EXAM_CHECK(!str.fail());
    EXAM_CHECK( str.str() != "inf" );
    EXAM_CHECK( str.str() != "-inf" );
    EXAM_CHECK( str.str() != "nan" );
    EXAM_CHECK( str.str() != "-nan" );
    //EXAM_MESSAGE( str.str().c_str() );

    //str.str("");
    //str << limits::max_exponent10;
    //EXAM_MESSAGE( str.str().c_str() );

    str >> in_val_d;

    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( in_val_d == in_val_d );
    EXAM_CHECK( in_val_d != limits::infinity() );
  }
  {
    stringstream str;

    str << scientific << setprecision(50) << limits::max();

    EXAM_CHECK(!str.fail());
    EXAM_CHECK( str.str() != "inf" );
    EXAM_CHECK( str.str() != "-inf" );
    EXAM_CHECK( str.str() != "nan" );
    EXAM_CHECK( str.str() != "-nan" );
    //EXAM_MESSAGE( str.str().c_str() );

    //str.str("");
    //str << limits::max_exponent10;
    //EXAM_MESSAGE( str.str().c_str() );

    str >> in_val_d;

    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( in_val_d == in_val_d );
    EXAM_CHECK( in_val_d != limits::infinity() );
  }
#endif
  {
    stringstream str;

    str << limits::infinity();

    EXAM_CHECK( !str.fail() );
    EXAM_CHECK( !limits::has_infinity || str.str() == "inf" );
  }
  {
    stringstream str;

    str << -limits::infinity();

    EXAM_CHECK( !str.fail() );
    EXAM_CHECK( !limits::has_infinity || str.str() == "-inf" );
  }
  {
    stringstream str;

    str << limits::quiet_NaN();

    EXAM_CHECK( !str.fail() );
    EXAM_CHECK( !limits::has_quiet_NaN || str.str() == "nan" );
  }
  {
    stringstream str;

    str << -limits::quiet_NaN();

    EXAM_CHECK( !str.fail() );
    EXAM_CHECK( !limits::has_quiet_NaN || str.str() == "-nan" );
  }
  {
    stringstream str;

    str << "0." << string(limits::max_exponent10, '0') << "1e" << (limits::max_exponent10 + 1);
    EXAM_CHECK( !str.fail() );

    str >> in_val_d;
    EXAM_CHECK( !str.fail() );
    EXAM_CHECK( str.eof() );
    EXAM_CHECK( in_val_d == 1 );
  }
  {
    stringstream str;

    str << "1" << string(-(limits::min_exponent10 - 1), '0') << "e" << (limits::min_exponent10 - 1);
    EXAM_CHECK( !str.fail() );

    str >> in_val_d;
    EXAM_CHECK( !str.fail() );
    EXAM_CHECK( str.eof() );
    EXAM_CHECK( in_val_d == 1 );
  }
#  if defined (_STLPORT_VERSION) && (_STLPORT_VERSION >= 0x530)
  // The following tests are showing that simply changing stream
  // precision lead to different result. Do not seems to be a real
  // problem, simply rounding approximation but additional study should
  // be done after 5.2 release.
  {
    stringstream str;
    str << setprecision(limits::digits10 + 2) << limits::max();

    //EXAM_MESSAGE(str.str().c_str());
    EXAM_CHECK( !str.fail() );

    F val;
    str >> val;

    EXAM_CHECK( !str.fail() );
    EXAM_CHECK( limits::infinity() > val );
  }
  {
    stringstream str;
    str << setprecision(limits::digits10 + 1) << limits::max();

    //EXAM_MESSAGE(str.str().c_str());
    EXAM_CHECK( !str.fail() );

    F val;
    str >> val;

    EXAM_CHECK( !str.fail() );
    EXAM_CHECK( limits::infinity() > val );
  }
#  endif
}

#if defined (_MSC_VER)
#  pragma warning (disable : 4056)
#  pragma warning (disable : 4756)
#endif

int EXAM_IMPL(num_put_get_test::num_put_float)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)

#  if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#  endif
  {
    string output, digits;

    {
      ostringstream ostr;
      ostr << 1.23457e+17f;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      digits = "17";
      complete_digits(digits);
      EXAM_CHECK(output == string("1.23457e+") + digits );
    }
    
    {
      ostringstream ostr;
      ostr << setprecision(200) << 1.23457e+17f;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK( output.size() < 200 );
    }
    
    {
      ostringstream ostr;
      ostr << setprecision(200) << numeric_limits<float>::min();
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK( output.size() < 200 );
    }
    
    {
      ostringstream ostr;
      ostr << fixed << 1.23457e+17f;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK(output.size() == 25);
      EXAM_CHECK(output.substr(0, 5) == "12345");
      EXAM_CHECK(output.substr(18) == ".000000");
    }

    {
      ostringstream ostr;
      ostr << fixed << showpos << 1.23457e+17f;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK(output.size() == 26);
      EXAM_CHECK(output.substr(0, 6) == "+12345");
      EXAM_CHECK(output.substr(19) == ".000000");
    }

    {
      ostringstream ostr;
      ostr << fixed << showpos << setprecision(100) << 1.23457e+17f;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK(output.size() == 120);
      EXAM_CHECK(output.substr(0, 6) == "+12345");
      EXAM_CHECK(output.substr(19) == ".0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" );
    }

    {
      ostringstream ostr;
      ostr << scientific << setprecision(8) << 0.12345678f;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      digits = "1";
      complete_digits(digits);
      EXAM_CHECK(output == string("1.23456780e-") + digits );
    }

    {
      ostringstream ostr;
      ostr << fixed << setprecision(8) << setw(30) << setfill('0') << 0.12345678f;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK(output == "000000000000000000000.12345678");
    }

    {
      ostringstream ostr;
      ostr << fixed << showpos << setprecision(8) << setw(30) << setfill('0') << 0.12345678f;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK(output == "0000000000000000000+0.12345678");
    }

    {
      ostringstream ostr;
      ostr << fixed << showpos << setprecision(8) << setw(30) << left << setfill('0') << 0.12345678f;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK(output == "+0.123456780000000000000000000");
    }

    {
      ostringstream ostr;
      ostr << fixed << showpos << setprecision(8) << setw(30) << internal << setfill('0') << 0.12345678f;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK(output == "+00000000000000000000.12345678");
    }

    {
      ostringstream ostr;
      ostr << fixed << showpos << setprecision(100) << 1.234567e+17;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK(output.size() == 120);
      EXAM_CHECK(output.substr(0, 6) == "+12345");
      EXAM_CHECK(output.substr(19) == ".0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" );
    }

#if !defined (STLPORT) || !defined (_STLP_NO_LONG_DOUBLE)
    {
      ostringstream ostr;
      ostr << fixed << showpos << setprecision(100) << 1.234567e+17l;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK(output.size() == 120);
      EXAM_CHECK(output.substr(0, 6) == "+12345");
      EXAM_CHECK(output.substr(19) == ".0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" );
    }
#endif

    {
      ostringstream ostr;
      ostr << scientific << setprecision(50) << 0.0;
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      EXAM_CHECK( output == "0.00000000000000000000000000000000000000000000000000e+00" );
    }
    {
      ostringstream ostr;
      ostr << fixed << setprecision(100) << numeric_limits<float>::max();
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      //EXAM_MESSAGE( output.c_str() );
    }

    {
      ostringstream ostr;
      ostr << setprecision(100) << numeric_limits<double>::max();
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      //EXAM_MESSAGE( output.c_str() );
    }

#if !defined (STLPORT) || !defined (_STLP_NO_LONG_DOUBLE)
    {
      ostringstream ostr;
      ostr << setprecision(100) << numeric_limits<long double>::max();
      EXAM_CHECK(ostr.good());
      output = reset_stream(ostr);
      //EXAM_MESSAGE( output.c_str() );
    }
#endif

    //{
    //  ostringstream ostr;
    //  ostr << setprecision(-numeric_limits<float>::min_exponent10 + numeric_limits<float>::digits10 + 9) << numeric_limits<float>::min();
    //  EXAM_CHECK(ostr.good());
    //  output = reset_stream(ostr);
    //  //EXAM_MESSAGE( output.c_str() );
    //}

    //{
    //  ostringstream ostr;
    //  ostr << setprecision(-numeric_limits<double>::min_exponent10 + numeric_limits<double>::digits10) << numeric_limits<double>::min();
    //  EXAM_CHECK(ostr.good());
    //  output = reset_stream(ostr);
    //  //EXAM_MESSAGE( output.c_str() );
    //}

//#if !defined (STLPORT) || !defined (_STLP_NO_LONG_DOUBLE)
//    {
//      ostringstream ostr;
//      ostr << setprecision(-numeric_limits<long double>::min_exponent10 + numeric_limits<long double>::digits10) << numeric_limits<long double>::min();
//      EXAM_CHECK(ostr.good());
//      output = reset_stream(ostr);
//      EXAM_MESSAGE( output.c_str() );
//    }
//#endif
  }

  {
    ostringstream str;

    str.setf(ios::fixed, ios::floatfield);
    str << 1.0e+5;
    // cerr << str.str() << endl;
    EXAM_CHECK( str.str() == "100000.000000" );

    reset_stream(str);
    str.precision(0);
    str << 1.0e+5;
    EXAM_CHECK( str.str() == "100000" );

    reset_stream(str);
    str.precision(4);
    str << 1.0e+5;
    EXAM_CHECK( str.str() == "100000.0000" );

    reset_stream(str);
    str.precision(0);
    str << 1.0e+83;
    EXAM_CHECK( str.str().size() == 84 );
    //printf("\nC result: %.0f\n", 1.0e+83);
    //EXAM_MESSAGE( str.str().c_str() );
    //EXAM_CHECK( str.str() == "100000000000000000000000000000000000000000000000000000000000000000000000000000000000" );

    // cerr.setf(ios::fixed, ios::floatfield);
    // cerr << DBL_MAX << endl;
    // cerr << 1.0e+37 << endl;
  }
#  if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#  endif

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

#define CHECK_COMPLETE(type, val, base, showbase, showpos, casing, width, adjust, expected) \
{ \
  type tmp = val; \
  ostringstream ostr; \
  ostr << base << showbase << showpos << casing << setw(width) << adjust << tmp; \
  EXAM_CHECK( ostr.str() == expected ); \
}

#define CHECK(type, val, base, expected) \
  CHECK_COMPLETE(type, val, base, noshowbase, noshowpos, nouppercase, 0, right, expected)

int EXAM_IMPL(num_put_get_test::num_put_integer)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)

#  if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#  endif
  //octal outputs
  {
    CHECK(short, 0, oct, "0")
    CHECK(short, 1, oct, "1")
    CHECK(short, 12345, oct, "30071")
    if (sizeof(short) == 2) {
      CHECK(short, -1, oct, "177777")
      CHECK(short, -12345, oct, "147707")
    }

    CHECK(unsigned short, 0, oct, "0")
    CHECK(unsigned short, 12345, oct, "30071")

    CHECK(int, 0, oct, "0")
    CHECK(int, 12345678, oct, "57060516")
    if (sizeof(int) == 4) {
      CHECK(int, -1, oct, "37777777777")
      CHECK(int, -12345678, oct, "37720717262")
    }

    CHECK(unsigned int, 0, oct, "0")
    CHECK(unsigned int, 12345678, oct, "57060516")

    CHECK(long, 0, oct, "0")
    CHECK(long, 12345678, oct, "57060516")
    if (sizeof(long) == 4) {
      CHECK(long, -1, oct, "37777777777")
      CHECK(long, -12345678, oct, "37720717262")
    }

    CHECK(unsigned long, 0, oct, "0")
    CHECK(unsigned long, 12345678, oct, "57060516")

#if defined (STLPORT) && defined (_STLP_LONG_LONG)
    CHECK(_STLP_LONG_LONG, 0, oct, "0")
    CHECK(_STLP_LONG_LONG, 12345678, oct, "57060516")
    if (sizeof(_STLP_LONG_LONG) == 8) {
      CHECK(_STLP_LONG_LONG, -1, oct, "1777777777777777777777")
      CHECK(_STLP_LONG_LONG, -12345678, oct, "1777777777777720717262")
    }

    CHECK(unsigned _STLP_LONG_LONG, 0, oct, "0")
    CHECK(unsigned _STLP_LONG_LONG, 12345678, oct, "57060516")
#endif

    //Even with showbase, 0 value gives "0" (see printf documentation)
    CHECK_COMPLETE(short, 0, oct, showbase, noshowpos, nouppercase, 0, right, "0")
    CHECK_COMPLETE(short, 0, oct, showbase, showpos, nouppercase, 6, right, "     0")

    CHECK_COMPLETE(short, 1, oct, showbase, noshowpos, nouppercase, 6, right, "    01")
    CHECK_COMPLETE(short, 1, oct, showbase, noshowpos, nouppercase, 6, left, "01    ")
    CHECK_COMPLETE(short, 1, oct, showbase, showpos, nouppercase, 6, internal, "    01")
  }

  //decimal outputs
  {
    CHECK(short, 0, dec, "0")
    CHECK(short, -1, dec, "-1")
    CHECK(short, 12345, dec, "12345")
    CHECK(short, -12345, dec, "-12345")

    CHECK(unsigned short, 0, dec, "0")
    CHECK(unsigned short, 12345, dec, "12345")

    CHECK(int, 0, dec, "0")
    CHECK(int, -1, dec, "-1")
    CHECK(int, 12345678, dec, "12345678")
    CHECK(int, -12345678, dec, "-12345678")

    CHECK(unsigned int, 0, dec, "0")
    CHECK(unsigned int, 12345678, dec, "12345678")

    CHECK(long, 0, dec, "0")
    CHECK(long, -1, dec, "-1")
    CHECK(long, 12345678, dec, "12345678")
    CHECK(long, -12345678, dec, "-12345678")

    CHECK(unsigned long, 0, dec, "0")
    CHECK(unsigned long, 12345678, dec, "12345678")
#if defined (STLPORT) && defined (_STLP_LONG_LONG)
    CHECK(_STLP_LONG_LONG, 0, dec, "0")
    CHECK(_STLP_LONG_LONG, -1, dec, "-1")
    CHECK(_STLP_LONG_LONG, 12345678, dec, "12345678")
    CHECK(_STLP_LONG_LONG, -12345678, dec, "-12345678")

    CHECK(unsigned _STLP_LONG_LONG, 0, dec, "0")
    CHECK(unsigned _STLP_LONG_LONG, 12345678, dec, "12345678")
#endif

    CHECK_COMPLETE(short, 0, dec, showbase, showpos, nouppercase, 0, right, "+0")
    CHECK_COMPLETE(short, 0, dec, showbase, showpos, nouppercase, 6, right, "    +0")
    CHECK_COMPLETE(short, 1, dec, showbase, showpos, nouppercase, 6, right, "    +1")
    CHECK_COMPLETE(short, 1, dec, showbase, showpos, nouppercase, 6, left, "+1    ")
    CHECK_COMPLETE(short, 1, dec, showbase, showpos, nouppercase, 6, internal, "+    1")
  }

  //hexadecimal outputs
  {
    CHECK(short, 0, hex, "0")
    CHECK(short, 12345, hex, "3039")
    if (sizeof(short) == 2) {
      CHECK(short, -1, hex, "ffff")
      CHECK(short, -12345, hex, "cfc7")
    }

    CHECK(unsigned short, 0, hex, "0")
    CHECK(unsigned short, 12345, hex, "3039")

    CHECK(int, 0, hex, "0")
    CHECK(int, 12345678, hex, "bc614e")
    if (sizeof(int) == 4) {
      CHECK(int, -1, hex, "ffffffff")
      CHECK(int, -12345678, hex, "ff439eb2")
    }

    CHECK(unsigned int, 0, hex, "0")
    CHECK(unsigned int, 12345678, hex, "bc614e")

    CHECK(long, 0, hex, "0")
    CHECK(long, 12345678, hex, "bc614e")
    if (sizeof(long) == 4) {
      CHECK(long, -1, hex, "ffffffff")
      CHECK(long, -12345678, hex, "ff439eb2")
    }

    CHECK(unsigned long, 0, hex, "0")
    CHECK(unsigned long, 12345678, hex, "bc614e")
#if defined (STLPORT) && defined (_STLP_LONG_LONG)
    CHECK(_STLP_LONG_LONG, 0, hex, "0")
    CHECK(_STLP_LONG_LONG, 12345678, hex, "bc614e")
    if (sizeof(_STLP_LONG_LONG) == 8) {
      CHECK(_STLP_LONG_LONG, -1, hex, "ffffffffffffffff")
      CHECK(_STLP_LONG_LONG, -12345678, hex, "ffffffffff439eb2")
    }

    CHECK(unsigned _STLP_LONG_LONG, 0, hex, "0")
    CHECK(unsigned _STLP_LONG_LONG, 12345678, hex, "bc614e")
#endif

    //Even with showbase, 0 value gives "0" output (see printf documentation)
    CHECK_COMPLETE(short, 0, hex, showbase, showpos, nouppercase, 0, right, "0")
    CHECK_COMPLETE(short, 0, hex, showbase, noshowpos, nouppercase, 6, right, "     0")
    CHECK_COMPLETE(short, 0, hex, showbase, noshowpos, nouppercase, 6, internal, "     0")

    CHECK_COMPLETE(short, 1, hex, showbase, noshowpos, nouppercase, 6, right, "   0x1")
    CHECK_COMPLETE(short, 1, hex, showbase, noshowpos, nouppercase, 6, left, "0x1   ")
    CHECK_COMPLETE(short, 1, hex, showbase, noshowpos, nouppercase, 6, internal, "0x   1")
    CHECK_COMPLETE(short, 1, hex, showbase, noshowpos, uppercase, 6, left, "0X1   ")
    CHECK_COMPLETE(short, 1, hex, showbase, showpos, uppercase, 6, internal, "0X   1")
  }
#  if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#  endif

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(num_put_get_test::num_get_float)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)

#  if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#  endif
  float in_val;

  istringstream istr;

  istr.str("1.2345");
  istr >> in_val;
  EXAM_CHECK(!istr.fail());
  EXAM_CHECK(istr.eof());
  EXAM_CHECK(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("-1.2345");
  istr >> in_val;
  EXAM_CHECK(!istr.fail());
  EXAM_CHECK(istr.eof());
  EXAM_CHECK(check_float(in_val, -1.2345f));
  istr.clear();

  istr.str("+1.2345");
  istr >> in_val;
  EXAM_CHECK(!istr.fail());
  EXAM_CHECK(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("000000000000001.234500000000");
  istr >> in_val;
  EXAM_CHECK(!istr.fail());
  EXAM_CHECK(istr.eof());
  EXAM_CHECK(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("1.2345e+04");
  istr >> in_val;
  EXAM_CHECK(!istr.fail());
  EXAM_CHECK(istr.eof());
  EXAM_CHECK(check_float(in_val, 12345.0f));
  istr.clear();

  EXAM_MESSAGE( "float" );
  check_get_float( 0.0F );
  EXAM_MESSAGE( "double" );
  check_get_float( 0.0 );
#if !defined (STLPORT) || !defined (_STLP_NO_LONG_DOUBLE)
  EXAM_MESSAGE( "long double" );
  check_get_float( 0.0L );
#endif
  {
    stringstream str;

    str << "1e" << numeric_limits<double>::max_exponent10;
    EXAM_CHECK(!str.fail());

    float val;
    str >> val;
    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( numeric_limits<double>::max_exponent10 <= numeric_limits<float>::max_exponent10 ||
                    val == numeric_limits<float>::infinity() );
  }
  {
    stringstream str;

    str << "1e" << numeric_limits<double>::min_exponent10;
    EXAM_CHECK(!str.fail());

    float val;
    str >> val;
    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( numeric_limits<double>::min_exponent10 >= numeric_limits<float>::min_exponent10 ||
                    val == 0.0f );
  }
#if !defined (STLPORT) || !defined (_STLP_NO_LONG_DOUBLE)
  {
    stringstream str;

    str << "1e" << numeric_limits<long double>::max_exponent10;
    EXAM_CHECK(!str.fail());

    double val;
    str >> val;
    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( numeric_limits<long double>::max_exponent10 <= numeric_limits<double>::max_exponent10 ||
                    val == numeric_limits<double>::infinity() );
  }
  {
    stringstream str;

    str << "1e" << numeric_limits<long double>::min_exponent10;
    EXAM_CHECK(!str.fail());

    double val;
    str >> val;
    EXAM_CHECK(!str.fail());
    EXAM_CHECK(str.eof());
    EXAM_CHECK( numeric_limits<long double>::min_exponent10 >= numeric_limits<double>::min_exponent10 ||
                    val == 0.0 );
  }
  {
    const char* p = "2.718281828459045235360287471352662497757247093e0";
    std::stringstream s;
    s << p;
    long double x;
    s >> x;
    EXAM_CHECK( x > 2.70l && x < 2.72l );
  }
#endif
#  if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#  endif

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(num_put_get_test::num_get_integer)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)

#  if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#  endif
  //octal input
  {
    istringstream istr;
    istr.str("30071");
    short val;
    istr >> oct >> val;
    EXAM_CHECK( !istr.fail() );
    EXAM_CHECK( istr.eof() );
    EXAM_CHECK( val == 12345 );
    istr.clear();

    if (sizeof(short) == 2) {
      istr.str("177777");
      istr >> oct >> val;
      EXAM_CHECK( !istr.fail() );
      EXAM_CHECK( istr.eof() );
      EXAM_CHECK( val == -1 );
      istr.clear();
    }
  }

  //decimal input
  {
    istringstream istr;
    istr.str("10000");
    short val = -1;
    istr >> val;
    EXAM_CHECK( !istr.fail() );
    EXAM_CHECK( istr.eof() );
    EXAM_CHECK( val == 10000 );
    istr.clear();

    istr.str("+10000");
    val = -1;
    istr >> val;
    EXAM_CHECK( !istr.fail() );
    EXAM_CHECK( istr.eof() );
    EXAM_CHECK( val == 10000 );
    istr.clear();

    if (sizeof(short) == 2) {
      val = -1;
      istr.str("10000000");
      istr >> val;
      EXAM_CHECK( istr.fail() );
      EXAM_CHECK( istr.eof() );
      EXAM_CHECK( val == -1 );
      istr.clear();
    }

    val = -1;
    istr.str("0x0");
    istr >> val;
    EXAM_CHECK( !istr.fail() );
    EXAM_CHECK( !istr.eof() );
    EXAM_CHECK( val == 0 );
    istr.clear();

    val = -1;
    istr.str("000001");
    istr >> val;
    EXAM_CHECK( !istr.fail() );
    EXAM_CHECK( istr.eof() );
    EXAM_CHECK( val == 1 );
    istr.clear();
  }

  //hexadecimal input
  {
    istringstream istr;
    istr.str("3039");
    short val = -1;
    istr >> hex >> val;
    EXAM_CHECK( !istr.fail() );
    EXAM_CHECK( istr.eof() );
    EXAM_CHECK( val == 12345 );
    istr.clear();

    istr.str("x3039");
    val = -1;
    istr >> hex >> val;
    EXAM_CHECK( istr.fail() );
    EXAM_CHECK( !istr.eof() );
    EXAM_CHECK( val == -1 );
    istr.clear();

    istr.str("03039");
    val = -1;
    istr >> hex >> val;
    EXAM_CHECK( !istr.fail() );
    EXAM_CHECK( istr.eof() );
    EXAM_CHECK( val == 12345 );
    istr.clear();

    istr.str("0x3039");
    istr >> hex >> val;
    EXAM_CHECK( !istr.fail() );
    EXAM_CHECK( istr.eof() );
    EXAM_CHECK( val == 12345 );
    istr.clear();

    if (sizeof(short) == 2) {
      val = -1;
      istr.str("cfc7");
      istr >> hex >> val;
      EXAM_CHECK( !istr.fail() );
      EXAM_CHECK( istr.eof() );
      EXAM_CHECK( val == -12345 );
      istr.clear();
    }
  }
#  if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#  endif

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(num_put_get_test::inhex)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)

#  if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#  endif
  {
    ostringstream s;
    s << hex << 0;
    EXAM_CHECK( s.str() == "0" );
  }
  {
    ostringstream s;
    s << hex << 0xff;
    EXAM_CHECK( s.str() == "ff" );
  }
  {
    ostringstream s;
    s << hex << setw( 4 ) << 0xff;
    EXAM_CHECK( s.str() == "  ff" );
  }
  {
    ostringstream s;
    s << hex << setw( 4 ) << 0;
    EXAM_CHECK( s.str() == "   0" );
  }
  {
    ostringstream s;
    s << hex << showbase << 0;
    EXAM_CHECK( s.str() == "0" );
  }
  {
    ostringstream s;
    s << hex << showbase << 0xff;
    EXAM_CHECK( s.str() == "0xff" );
  }
  {
    ostringstream s;
    s << hex << showbase << setw( 4 ) << 0xff;
    EXAM_CHECK( s.str() == "0xff" );
  }
  { // special case for regression (partially duplicate CHECK_COMPLETE above):
    ostringstream s;
    s.setf( ios_base::internal, ios_base::adjustfield );
    s << hex << showbase << setw(8+2) << 0;
    EXAM_CHECK( s.str() == "         0" );
  }
#  if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#  endif

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(num_put_get_test::pointer)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)

#  if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#  endif
  // Problem with printing pointer to null

  /*
   * Really C's formatting not help here, due to:
   *
   * p  The argument shall be a pointer to void. The value of
   *    the pointer is converted to a sequence of printable characters,
   *    in an implementation-defined manner.
   */
  {
    /*
    char buf[128];
    void *p = (void *)0xff00;
    sprintf( buf, "%p", p );
    // cerr << buf << endl;
    // Hmmm, I see 0xff00 on box with 32-bits address; pointer like 'unsigned hex'? 
    if ( sizeof( p ) == 2 ) {
      EXAM_CHECK( strcmp( buf, "0xff00" ) == 0 );
    } else if ( sizeof( p ) == 4 ) {
      EXAM_CHECK( strcmp( buf, "0x0000ff00" ) == 0 );
    } else if ( sizeof( p ) == 8 ) {
      EXAM_CHECK( strcmp( buf, "0x000000000000ff00" ) == 0 );
    } else {
      EXAM_CHECK( sizeof( p ) == 2 || sizeof( p ) == 4 || sizeof( p ) == 8 );
    }
    */
  }
  {
    /*
    char buf[128];
    void *p = 0;
    */
    // sprintf( buf, "%p", p );
    /* Cool. "%p" print '(nil)'; "%#x" print '0' */
    // sprintf( buf, "%#x", (unsigned)p );
    // cerr << buf << endl;
  }
  {
    ostringstream s;
    void *p = (void *)0xff00;
    s << p;
    EXAM_CHECK( s.good() );
    if ( sizeof( p ) == 2 ) {
      EXAM_CHECK( s.str() == "0xff00" );
    } else if ( sizeof( p ) == 4 ) {
      EXAM_CHECK( s.str() == "0x0000ff00" ); // this pass
    } else if ( sizeof( p ) == 8 ) {
      EXAM_CHECK( s.str() == "0x000000000000ff00" );
    } else {
      EXAM_CHECK( sizeof( p ) == 2 || sizeof( p ) == 4 || sizeof( p ) == 8 );
    }
  }
  {
    ostringstream s;
    void *p = 0;
    s << p;
    EXAM_CHECK( s.good() );
    if ( sizeof( p ) == 2 ) {
      EXAM_CHECK( s.str() == "0x0000" );
    } else if ( sizeof( p ) == 4 ) {
      EXAM_CHECK( s.str() == "0x00000000" ); // but this will fail, if follow %p
    } else if ( sizeof( p ) == 8 ) {
      EXAM_CHECK( s.str() == "0x0000000000000000" );
    } else {
      EXAM_CHECK( sizeof( p ) == 2 || sizeof( p ) == 4 || sizeof( p ) == 8 );
    }
  }
#  if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#  endif

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(num_put_get_test::fix_float_long)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)

#  if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#  endif
  ostringstream str;

  str.setf(ios::fixed, ios::floatfield);
  str << 1.0e+5;
  EXAM_CHECK( str.str() == "100000.000000" );

  reset_stream(str);
  str.precision(0);
  str << 1.0e+5;
  EXAM_CHECK( str.str() == "100000" );

  reset_stream(str);
  str.precision(4);
  str << 1.0e+5;
  EXAM_CHECK( str.str() == "100000.0000" );

  reset_stream(str);
  str.precision(0);
  str << 1.0e+83;
  {
    istringstream istr( str.str() );
    double f;
    istr >> f;
    EXAM_CHECK( !istr.fail() );
    if ( int(numeric_limits<double>::digits10) < 83 ) {
      double delta = 1.0;
      for ( int ee = 83 - int(numeric_limits<double>::digits10); ee > 0; --ee ) {
        delta *= 10.0;
      }
      // we may loss some digits here, but not more than mantissa:
      EXAM_CHECK( (f > (1.0e+83 - delta)) && (f < (1.0e+83 + delta)) );
    } else {
      EXAM_CHECK( check_double(f, 1.0e+83) );
    }
  }

#if 0 // #ifndef _STLP_NO_LONG_DOUBLE
  reset_stream(str);
  str.precision(0);
  str << 1.0e+83l;
  {
    istringstream istr( str.str() );
    long double f;
    istr >> f;
    EXAM_CHECK( !istr.fail() );
    if ( int(numeric_limits<long double>::digits10) < 83 ) {
      long double delta = 1.0l;
      for ( int ee = 83 - int(numeric_limits<long double>::digits10); ee > 0; --ee ) {
        delta *= 10.0l;
      }
      // we may loss some digits here, but not more than mantissa:
      cerr << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789" << endl;
      cerr << str.str() << endl;
      cerr << delta << endl;
      cerr << f << endl;
      EXAM_CHECK( (f > (1.0e+83l - delta)) && (f < (1.0e+83l + delta)) );
    } else {
      EXAM_CHECK( check_double(f, 1.0e+83l) );
    }
  }
#endif

  reset_stream(str);
  str.precision(0);
  str << numeric_limits<double>::max();
  {
    istringstream istr( str.str() );
    double f;
    istr >> f;
    EXAM_CHECK( !istr.fail() );
    if ( int(numeric_limits<double>::digits10) < int(numeric_limits<double>::max_exponent10) ) {
      double delta = 9.0;
      for ( int ee = int(numeric_limits<double>::max_exponent10) - int(numeric_limits<double>::digits10); ee > 0; --ee ) {
        delta *= 10.0;
      }
      // we may loss some digits here, but not more than mantissa:
      EXAM_CHECK( (f > (numeric_limits<double>::max() - delta)) );
    }
  }

#if 0 // #ifndef _STLP_NO_LONG_DOUBLE
  reset_stream(str);
  str.precision(0);
  str << numeric_limits<long double>::max();
  {
    istringstream istr( str.str() );
    long double f;
    istr >> f;
    EXAM_CHECK( !istr.fail() );
    if ( int(numeric_limits<long double>::digits10) < int(numeric_limits<long double>::max_exponent10) ) {
      long double delta = 1.0l;
      for ( int ee = int(numeric_limits<long double>::max_exponent10) - int(numeric_limits<long double>::digits10); ee > 0; --ee ) {
        delta *= 10.0l;
      }
      // we may loss some digits here, but not more than mantissa:
      EXAM_CHECK( (f > (numeric_limits<long double>::max() - delta)) );
    }
  }
#endif
#  if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#  endif

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

class CommaSepNumPunct : public numpunct<char> {
  char do_thousands_sep() const { return ','; }
  string do_grouping() const { return string("\1\2\3") + (char)CHAR_MAX; }
};

#define CHECK2(val, expected) \
  os.str(""); os << fixed << setprecision(3) << showpos << val; \
  EXAM_CHECK( os.str() == expected )

int EXAM_IMPL(num_put_get_test::custom_numpunct)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)

#  if defined (__BORLANDC__)
  /* Ignore FPU exceptions, set FPU precision to 64 bits */
  unsigned int _float_control_word = _control87(0, 0);
  _control87(PC_64|MCW_EM|IC_AFFINE, MCW_PC|MCW_EM|MCW_IC);
#  endif
    ostringstream os;
    locale loc(os.getloc(), new CommaSepNumPunct());
    os.imbue(loc);

    CHECK2(1, "+1");
    CHECK2(10, "+1,0");
    CHECK2(100, "+10,0");
    CHECK2(1000, "+1,00,0");

    CHECK2(1.234, "+1.234");
    CHECK2(123.456, "+12,3.456");
    CHECK2(1234.567, "+1,23,4.567");
    CHECK2(12345.678, "+12,34,5.678");
    CHECK2(123456.789, "+123,45,6.789");
    CHECK2(1234567.891, "+1,234,56,7.891");
    CHECK2(123456789.123, "+123,456,78,9.123");
    //CHECK2(100000000000000000000000000000.0, "+100000000000000000000000,000,00,0.000");
    CHECK2(numeric_limits<double>::infinity(), "+inf");

    CHECK2(-1.234, "-1.234");
    CHECK2(-123.456, "-12,3.456");
    CHECK2(-1234.567, "-1,23,4.567");
    CHECK2(-12345.678, "-12,34,5.678");
    CHECK2(-123456.789, "-123,45,6.789");
    CHECK2(-1234567.891, "-1,234,56,7.891");
    CHECK2(-123456789.123, "-123,456,78,9.123");
    //CHECK2(-100000000000000000000000000000.0, "-100000000000000000000000,000,00,0.000");
    CHECK2(-numeric_limits<double>::infinity(), "-inf");
#  if defined (__BORLANDC__)
  /* Reset floating point control word */
  _clear87();
  _control87(_float_control_word, MCW_PC|MCW_EM|MCW_IC);
#  endif

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <limits>
#include <iostream>

#ifdef WIN32
#include <float.h>
#elif (__sun)
#include <signal.h>
#include <ieeefp.h>
#include <math.h>
#endif

#ifdef MAIN 
#define quiet_signal_nan_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif


using namespace std;

template <typename _Rational>
void quiet_signal_nan (_Rational refVal, const char* type_name) {

  cout << "Testing " << type_name << " type:" << endl;
  cout << "quiet NaN: ";

  _Rational a1 = refVal * numeric_limits<_Rational>::quiet_NaN();

  cout << "OK!" << endl ;

  try {
    cout << "signaling NaN: ";

    _Rational a2 = refVal * numeric_limits<_Rational>::signaling_NaN();

    cout << "NOT OK" << endl ;

    return;
  }
  catch (...){
    cout << "OK!" << endl ;
  }
}

int quiet_signal_nan_test(int, char**)
{
  cout << "Results of quiet_signal_nan_test:"<<endl;
#ifdef WIN32
  unsigned int former_val = _status87();
  _clear87();
  _control87( 0 , _MCW_EM );
#elif (__sun)
  fpsetmask(FP_X_DZ | FP_X_INV | FP_X_OFL);
#else
  cout << "To be ported for this platform";
  return 0;
#endif

  quiet_signal_nan<float>(20.67f, "float");
  quiet_signal_nan<double>(20.67, "double");

#ifndef _STLP_NO_LONG_DOUBLE
  quiet_signal_nan<long double>(20.67l, "long double");
#endif

#ifdef WIN32
  _control87(former_val, 0xffffffff);
#elif (__sun)
#endif

  return 0;
}

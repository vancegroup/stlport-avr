// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <limits>
#include <iomanip>
#include <iostream>

#include "stl_test.h"

#ifdef MAIN
#define float_output_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int float_output_test(int, char**)
{
#ifdef MAIN
  cout<<"Results of float_output_test:";
#endif
  cout << endl;

  cout << "numeric_limits<float>::min() : " << numeric_limits<float>::min() << endl;
  cout << "numeric_limits<float>::max() : " << numeric_limits<float>::max() << endl;
  cout << "numeric_limits<float>::epsilon() : " << numeric_limits<float>::epsilon() << endl;

  size_t def_precision = cout.precision();
  float test_val = numeric_limits<float>::max();
  cout << "tested value : " << test_val << endl;
  cout << "in fixed mode: " << fixed << test_val << endl;
  cout << "with showpos: " << showpos << test_val << endl;
  cout << "with 500 precision : " << setprecision(500) << test_val << endl;
  cout << noshowpos << scientific << setprecision(def_precision);

  test_val = 0.123456789f;
  cout << setprecision(9);
  cout << "tested value      :" << test_val << endl;
  cout << "width 30, fill 0  :" << setw(30) << setfill('0') << test_val << endl;
  cout << "in fixed mode     :" << setw(30) << fixed << test_val << endl;
  //cout << "with precision 30 :" << setw(30) << setprecision(30) << test_val << endl;
  cout << "with pos          :" << setw(30) << showpos << test_val << endl;
  cout << "align left        :" << setw(30) << left << test_val << endl;
  cout << "align internal    :" << setw(30) << internal << test_val << endl;

  //Restauration of the default state:
  cout << setprecision(def_precision) << noshowpos << right << scientific;

#ifdef MAIN
  cout << endl;
  cout << "succeed" << endl;
#endif
  return 0;
}

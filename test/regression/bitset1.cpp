// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.


#include <stdexcept>
#include <iostream>
#include <bitset>
#include <algorithm>

/*#if defined (_STLP_MSVC) && (_MSC_VER < 1300)
# define _STLP_NON_TYPE_TMPL_PARAM_BUG
# define _STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS
#endif*/

# ifdef _STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS
# define CHART
# else
# define CHART <char, char_traits<char>, allocator<char> >
# endif

#ifdef MAIN 
#define bitset1_test main
#endif

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

void disp_bitset(char const* pname, bitset<13U> const& bset) {
  // Boris : MSVC just cannot take it right
//# if ! (defined (_STLP_MSVC) && (_MSC_VER < 1300)) && ! (defined (__SUNPRO_CC) && (__SUNPRO_CC < 0x500))
# if !defined (_STLP_NON_TYPE_TMPL_PARAM_BUG)
  cout << pname << bset << endl;
# else
  cout << pname << bset.to_string CHART () << endl;
# endif
//# endif /* MSVC || SUNPRO*/
}

int bitset1_test(int, char**)
{
  cout<<"Results of bitset1_test:"<<endl;

  bitset<13U> b1(0xFFFF);
  bitset<13U> b2(0x1111);
  cout << "b1 size = " << b1.size() << endl;
  disp_bitset("b1 = ", b1);
  cout << "b2 size = " << b2.size() << endl;
  disp_bitset("b2 = ", b2);
  b1 = b1^(b2<<2);
  disp_bitset("b1 = ", b1);
  cout << "b1 nb bits set = " << b1.count() << endl;
  cout << "b2 nb bits set = " << b2.count() << endl;
  return 0;
}


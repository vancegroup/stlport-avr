
#include <iostream>

using std::cout;
using std::endl;

#ifndef STLP_PRINT
# define STLP_CHECK(v) if ( !(v) ) { \
                         cout << "(violation: " << #v << " is false, " << __FILE__ << ":" << __LINE__ << ")"; \
                         return -1; \
                       } void(0)
#else
# define STLP_CHECK(v) if ( !(v) ) { \
                         cout << "(violation: " << #v << " is false, " << __FILE__ << ":" << __LINE__ << ")"; \
                         return -1; \
                       } else { \
                         cout << "(condition: " << #v << " is true, " << __FILE__ << ":" << __LINE__ << ")"; \
                       } void(0)
#endif

// Local Variables:
// mode:C++
// End:

#if defined(UNDER_CE)

#include "stlport_prefix.h"

#if defined(_STLP_USE_WINCE_CRT_FUNCTIONS)

#include <stdlib.h>

// 
// No environment variables exist
//

char * environ[] = {NULL};

char * getenv(const char *)
{
	return NULL;
}

#endif  // _STLP_USE_WINCE_CRT_FUNCTIONS

#endif  //  UNDER_CE

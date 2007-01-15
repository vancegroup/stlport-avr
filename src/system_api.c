#if defined (__hpux) && defined (__GNUC__)
#include <math.h>

#include "system_api.h"

int stlp_isfinite(double value)
{
  return isfinite(value);
}

int stlp_isnan(double value)
{
  return isnan(value);
}

int stlp_isinf(double value)
{
  return isinf(value);
}
#endif

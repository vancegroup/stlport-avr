/* This test purpose is simply to check Standard header independancy that
 * is to say that the header can be included alone without any previous
 * include.
 * Additionnaly, for C Standard headers that STLport expose, it can also be
 * used to check that files included by those headers are compatible with
 * pure C compilers.
 */
#include <stdint.h>

static int f()
{
  std::int32_t v = 1;

  return static_cast<int>(v);
}

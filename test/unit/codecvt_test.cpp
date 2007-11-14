#include <string>

#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <fstream>
#  include <locale>
#  include <stdexcept>

#  include "cppunit/cppunit_proxy.h"

#  if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#  endif

//
// TestCase class
//
class CodecvtTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(CodecvtTest);
#if defined (STLPORT) && defined (_STLP_NO_MEMBER_TEMPLATES)
  CPPUNIT_IGNORE;
#endif
  CPPUNIT_TEST(variable_encoding);
  CPPUNIT_STOP_IGNORE;
#if defined (STLPORT) && (defined (_STLP_NO_WCHAR_T) || !defined (_STLP_USE_EXCEPTIONS))
  CPPUNIT_IGNORE;
#endif
  CPPUNIT_TEST(in_out_test);
  CPPUNIT_TEST(length_test);
  CPPUNIT_TEST_SUITE_END();

protected:
  void variable_encoding();
  void in_out_test();
  void length_test();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CodecvtTest);

#if defined (STLPORT)
#  define __NO_THROW _STLP_NOTHROW
#else
#  define __NO_THROW throw()
#endif


/* Codecvt facet eating some characters from the external buffer.
 * Transform '01' in 'a'
 */
struct eater_codecvt : public codecvt<char, char, mbstate_t> {
  typedef codecvt<char,char,mbstate_t> base;

  explicit eater_codecvt(size_t refs = 0) : base(refs) {}

  // primitive conversion
  virtual base::result
  do_in(mbstate_t& mb,
        const char* ebegin, const char* eend, const char*& ecur,
        char* ibegin, char* iend, char*& icur) const __NO_THROW {
      char *state = (char*)&mb;
      ecur = ebegin;
      icur = ibegin;

      while (ecur != eend) {
          if (icur == iend)
              return partial;
          if (*ecur == '0' || *state == 1) {
            if (*state != 1) {
              ++ecur;
            }
            if (ecur == eend) {
              *state = 1;
              return ok;
            }

            if (*ecur == '1') {
              *icur = 'a';
            }
            else {
              *(icur++) = '0';
              if (icur == iend) {
                if (*state != 1) {
                  --ecur;
                }
                return partial;
              }
              *icur = *ecur;
            }
          }
          else {
            *icur = *ecur;
          }

          *state = 0;
          ++icur;
          ++ecur;
      }

      return ok;
  }

  // claim it's not a null-conversion
  virtual bool do_always_noconv() const __NO_THROW
  { return false; }

  // claim it doesn't have a fixed-length encoding
  virtual int do_encoding() const __NO_THROW
  { return 0; }

  // implemented for consistency with do_in overload
  virtual int do_length(mbstate_t &state,
                        const char *efrom, const char *eend, size_t m) const {
    char *ibegin = new char[m];
    const char *ecur = efrom;
    char *icur = ibegin;
    mbstate_t tmp = state;
    do_in(tmp, efrom, eend, ecur, ibegin, ibegin + m, icur);
    delete[] ibegin;
    return ecur - efrom;
  }

  virtual int do_max_length() const __NO_THROW
  { return 2; }
};

/* Codecvt facet generating more characters than the ones read from the
 * external buffer, transform '01' in 'abc'
 * This kind of facet do not allow systematical positionning in the external
 * buffer (tellg -> -1), when you just read a 'a' you are at an undefined
 * external buffer position.
 */
struct generator_codecvt : public codecvt<char, char, mbstate_t> {
  typedef codecvt<char,char,mbstate_t> base;

  explicit generator_codecvt(size_t refs = 0) : base(refs) {}

  // primitive conversion
  virtual base::result
  do_in(mbstate_t& mb,
        const char* ebegin, const char* eend, const char*& ecur,
        char* ibegin, char* iend, char*& icur) const __NO_THROW {
      //Access the mbstate information in a portable way:
      char *state = (char*)&mb;
      ecur = ebegin;
      icur = ibegin;

      if (icur == iend) return ok;

      if (*state == 2) {
        *(icur++) = 'b';
        if (icur == iend) {
          *state = 3;
          return ok;
        }
        *(icur++) = 'c';
        *state = 0;
      }
      else if (*state == 3) {
        *(icur++) = 'c';
        *state = 0;
      }

      while (ecur != eend) {
          if (icur == iend)
              return ok;
          if (*ecur == '0' || *state == 1) {
            if (*state != 1) {
              ++ecur;
            }
            if (ecur == eend) {
              *state = 1;
              return partial;
            }

            if (*ecur == '1') {
              *(icur++) = 'a';
              if (icur == iend) {
                *state = 2;
                return ok;
              }
              *(icur++) = 'b';
              if (icur == iend) {
                *state = 3;
                return ok;
              }
              *icur = 'c';
            }
            else {
              *(icur++) = '0';
              if (icur == iend) {
                if (*state != 1) {
                  --ecur;
                }
                return ok;
              }
              *icur = *ecur;
            }
          }
          else {
            *icur = *ecur;
          }

          *state = 0;
          ++icur;
          ++ecur;
      }

      return ok;
  }

  // claim it's not a null-conversion
  virtual bool do_always_noconv() const __NO_THROW
  { return false; }

  // claim it doesn't have a fixed-length encoding
  virtual int do_encoding() const __NO_THROW
  { return 0; }

  // implemented for consistency with do_in overload
  virtual int do_length(mbstate_t &mb,
                        const char *efrom, const char *eend, size_t m) const {
    const char *state = (const char*)&mb;
    int offset = 0;
    if (*state == 2)
      offset = 2;
    else if (*state == 3)
      offset = 1;

    char *ibegin = new char[m + offset];
    const char *ecur = efrom;
    char *icur = ibegin;
    mbstate_t tmpState = mb;
    do_in(tmpState, efrom, eend, ecur, ibegin, ibegin + m + offset, icur);
    /*
    char *state = (char*)&tmpState;
    if (*state != 0) {
      if (*state == 1)
        --ecur;
      else if (*state == 2 || *state == 3) {
        //Undefined position, we return -1:
        ecur = efrom - 1;
      }
    }
    else {
      if (*((char*)&mb) != 0) {
        //We take into account the character that hasn't been counted yet in
        //the previous decoding step:
        ecur++;
      }
    }
    */
    delete[] ibegin;
    return (int)min((size_t)(ecur - efrom), m);
  }

  virtual int do_max_length() const __NO_THROW
  { return 0; }
};

//
// tests implementation
//
void CodecvtTest::variable_encoding()
{
#if !defined (STLPORT) || !defined (_STLP_NO_MEMBER_TEMPLATES)
  //We first generate the file used for test:
  const char* fileName = "test_file.txt";
  {
    ofstream ostr(fileName);
    //Maybe we simply do not have write access to repository
    CPPUNIT_ASSERT( ostr.good() );
    for (int i = 0; i < 2048; ++i) {
      ostr << "0123456789";
    }
    CPPUNIT_ASSERT( ostr.good() );
  }

  {
    ifstream istr(fileName);
    CPPUNIT_ASSERT( istr.good() );
    CPPUNIT_ASSERT( !istr.eof() );

    eater_codecvt codec(1);
    locale loc(locale::classic(), &codec);

    istr.imbue(loc);
    CPPUNIT_ASSERT( istr.good() );
    CPPUNIT_ASSERT( (int)istr.tellg() == 0 );

    int theoricalPos = 0;
    do {
      int c = istr.get();
      if (char_traits<char>::eq_int_type(c, char_traits<char>::eof())) {
        break;
      }
      ++theoricalPos;
      if (c == 'a') {
        ++theoricalPos;
      }

      CPPUNIT_ASSERT( (int)istr.tellg() == theoricalPos );
    }
    while (!istr.eof());

    CPPUNIT_ASSERT( istr.eof() );
  }

#  if 0
  /* This test is broken, not sure if it is really possible to get a position in
   * a locale having a codecvt such as generator_codecvt. Maybe generator_codecvt
   * is not a valid theorical example of codecvt implementation. */
  {
    ifstream istr(fileName);
    CPPUNIT_ASSERT( istr.good() );
    CPPUNIT_ASSERT( !istr.eof() );

    generator_codecvt codec(1);
    locale loc(locale::classic(), &codec);

    istr.imbue(loc);
    CPPUNIT_ASSERT( istr.good() );
    CPPUNIT_ASSERT( (int)istr.tellg() == 0 );

    int theoricalPos = 0;
    int theoricalTellg;
    do {
      char c = istr.get();
      if (c == char_traits<char>::eof()) {
        break;
      }
      switch (c) {
        case 'a':
        case 'b':
          theoricalTellg = -1;
          break;
        case 'c':
          ++theoricalPos;
        default:
          ++theoricalPos;
          theoricalTellg = theoricalPos;
          break;
      }

      if ((int)istr.tellg() != theoricalTellg) {
        CPPUNIT_ASSERT( (int)istr.tellg() == theoricalTellg );
      }
    }
    while (!istr.eof());

    CPPUNIT_ASSERT( istr.eof() );
  }
#  endif
#endif
}

void CodecvtTest::in_out_test()
{
#if !defined (STLPORT) || !(defined (_STLP_NO_WCHAR_T) || !defined (_STLP_USE_EXCEPTIONS))
  try {
    locale loc("");

    typedef codecvt<wchar_t, char, mbstate_t> cdecvt_type;
    if (has_facet<cdecvt_type>(loc)) {
      cdecvt_type const& cdect = use_facet<cdecvt_type>(loc);
      {
        cdecvt_type::state_type state;
        memset(&state, 0, sizeof(cdecvt_type::state_type));
        string from("abcdef");
        const char* next_from;
        wchar_t to[1];
        wchar_t *next_to;
        cdecvt_type::result res = cdect.in(state, from.data(), from.data() + from.size(), next_from,
                                           to, to + sizeof(to) / sizeof(wchar_t), next_to);
        CPPUNIT_ASSERT( res == cdecvt_type::ok );
        CPPUNIT_ASSERT( next_from == from.data() + 1 );
        CPPUNIT_ASSERT( next_to == &to[0] + 1 );
        CPPUNIT_ASSERT( to[0] == L'a');
      }
      {
        cdecvt_type::state_type state;
        memset(&state, 0, sizeof(cdecvt_type::state_type));
        wstring from(L"abcdef");
        const wchar_t* next_from;
        char to[1];
        char *next_to;
        cdecvt_type::result res = cdect.out(state, from.data(), from.data() + from.size(), next_from,
                                            to, to + sizeof(to) / sizeof(char), next_to);
        CPPUNIT_ASSERT( res == cdecvt_type::ok );
        CPPUNIT_ASSERT( next_from == from.data() + 1 );
        CPPUNIT_ASSERT( next_to == &to[0] + 1 );
        CPPUNIT_ASSERT( to[0] == 'a');
      }
    }
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }
#endif
}

void CodecvtTest::length_test()
{
#if !defined (STLPORT) || !(defined (_STLP_NO_WCHAR_T) || !defined (_STLP_USE_EXCEPTIONS))
  try {
    locale loc("");

    typedef codecvt<wchar_t, char, mbstate_t> cdecvt_type;
    if (has_facet<cdecvt_type>(loc)) {
      cdecvt_type const& cdect = use_facet<cdecvt_type>(loc);
      {
        cdecvt_type::state_type state;
        memset(&state, 0, sizeof(cdecvt_type::state_type));
        string from("abcdef");
        int res = cdect.length(state, from.data(), from.data() + from.size(), from.size());
        CPPUNIT_ASSERT( (size_t)res == from.size() );
      }
    }
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    CPPUNIT_ASSERT( false );
  }
#endif
}

#endif

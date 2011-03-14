#include "codecvt_test.h"

#include <string>

#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <fstream>
#  include <locale>
#  include <stdexcept>
#  include <cstdio> // for WEOF

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

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

#ifdef __DMC__
  static locale::id id;
#endif
};

#ifdef __DMC__
locale::id eater_codecvt::id;

locale::id& _GetFacetId(const eater_codecvt*)
{ return eater_codecvt::id; }
#endif

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
#ifdef __DMC__
  static locale::id id;
#endif
};

#ifdef __DMC__
locale::id generator_codecvt::id;

locale::id& _GetFacetId(const generator_codecvt*)
{ return generator_codecvt::id; }
#endif

#endif // !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)

int EXAM_IMPL(codecvt_test::variable_encoding)
{
#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
  //We first generate the file used for test:
  const char* fileName = "test_file.txt";
  {
    ofstream ostr(fileName);
    //Maybe we simply do not have write access to repository
    EXAM_CHECK( ostr.good() );
    for (int i = 0; i < 2048; ++i) {
      ostr << "0123456789";
    }
    EXAM_CHECK( ostr.good() );
  }

  {
    ifstream istr(fileName);
    EXAM_CHECK( istr.good() );
    EXAM_CHECK( !istr.eof() );

    eater_codecvt codec(1);
    locale loc(locale::classic(), &codec);

    istr.imbue(loc);
    EXAM_CHECK( istr.good() );
    EXAM_CHECK( (int)istr.tellg() == 0 );

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

      EXAM_CHECK( (int)istr.tellg() == theoricalPos );
    }
    while (!istr.eof());

    EXAM_CHECK( istr.eof() );
  }

#  if 0
  /* This test is broken, not sure if it is really possible to get a position in
   * a locale having a codecvt such as generator_codecvt. Maybe generator_codecvt
   * is not a valid theorical example of codecvt implementation. */
  {
    ifstream istr(fileName);
    EXAM_CHECK( istr.good() );
    EXAM_CHECK( !istr.eof() );

    generator_codecvt codec(1);
    locale loc(locale::classic(), &codec);

    istr.imbue(loc);
    EXAM_CHECK( istr.good() );
    EXAM_CHECK( (int)istr.tellg() == 0 );

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
        EXAM_CHECK( (int)istr.tellg() == theoricalTellg );
      }
    }
    while (!istr.eof());

    EXAM_CHECK( istr.eof() );
  }
#  endif

#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(codecvt_test::in_out_test)
{
#if !defined (STLPORT) || !(defined (_STLP_NO_WCHAR_T) || !defined (_STLP_USE_EXCEPTIONS)) \
                       || !defined (_STLP_USE_NO_IOSTREAMS)
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
        EXAM_CHECK( res == cdecvt_type::ok );
        EXAM_CHECK( next_from == from.data() + 1 );
        EXAM_CHECK( next_to == &to[0] + 1 );
        EXAM_CHECK( to[0] == L'a');
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
        EXAM_CHECK( res == cdecvt_type::ok );
        EXAM_CHECK( next_from == from.data() + 1 );
        EXAM_CHECK( next_to == &to[0] + 1 );
        EXAM_CHECK( to[0] == 'a');
      }
    }
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    EXAM_ERROR("Exception appeared");
  }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(codecvt_test::length_test)
{
#if !defined (STLPORT) || !(defined (_STLP_NO_WCHAR_T) || !defined (_STLP_USE_EXCEPTIONS)) \
                       || !defined (_STLP_USE_NO_IOSTREAMS)
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
        EXAM_CHECK( (size_t)res == from.size() );
      }
    }
  }
  catch (runtime_error const&) {
  }
  catch (...) {
    EXAM_ERROR("Exception appeared");
  }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

#if !defined (STLPORT) || !(defined (_STLP_NO_WCHAR_T) || !defined (_STLP_USE_EXCEPTIONS))
typedef std::codecvt<wchar_t, char, mbstate_t> my_codecvt_base;

class my_codecvt : public my_codecvt_base {
public:
  explicit my_codecvt(size_t r = 0)
   : my_codecvt_base(r) {}

protected:
  virtual result do_in(state_type& /*state*/, const extern_type* first1,
                       const extern_type* last1, const extern_type*& next1,
                       intern_type* first2, intern_type* last2,
                       intern_type*& next2) const {
    for ( next1 = first1, next2 = first2; next1 < last1; next1 += 2 ) {
      if ( (last1 - next1) < 2 || (last2 - next2) < 1 )
        return partial;
      *next2++ = (intern_type)((*(next1 + 1) << 8) | (*next1 & 255));
    }
    return ok;
  }
  virtual bool do_always_noconv() const __NO_THROW
  { return false; }
  virtual int do_max_length() const __NO_THROW
  { return 2; }
  virtual int do_encoding() const __NO_THROW
  { return 2; }
};
#endif

int EXAM_IMPL(codecvt_test::imbue_while_reading)
{
#if !defined (STLPORT) || !(defined (_STLP_NO_WCHAR_T) || !defined (_STLP_USE_EXCEPTIONS)) \
                       || !defined (_STLP_USE_NO_IOSTREAMS)
  {
    wofstream ofs( "test.txt" );
    const wchar_t buf[] = L" ";
    for ( int i = 0; i < 4098; ++i ) {
      ofs << buf[0];
    }
  }

  wifstream ifs("test.txt"); // a file containing 4098 wchars

  ifs.imbue( locale(locale(), new my_codecvt) );
  ifs.get();
  ifs.seekg(0);
  ifs.imbue( locale() );
  ifs.ignore(4096);
  int ch = ifs.get();
  EXAM_CHECK( ch != (int)WEOF );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(codecvt_test::eol)
{
#if !defined (STLPORT) || (!defined (_STLP_NO_WCHAR_T) && defined (_STLP_USE_EXCEPTIONS)) \
                       || !defined (_STLP_USE_NO_IOSTREAMS)
  locale loc(locale::classic(), new codecvt_byname<wchar_t, char, mbstate_t>("C"));
  codecvt<wchar_t, char, mbstate_t> const& cvt = use_facet<codecvt<wchar_t, char, mbstate_t> >(loc);
  mbstate_t state;
  memset(&state, 0, sizeof(mbstate_t));
  char c = '0';
  const char *from_next;
  wchar_t wc;
  wchar_t *to_next;
  EXAM_CHECK( cvt.in(state, &c, &c + 1, from_next, &wc, &wc, to_next) == codecvt_base::ok );
  EXAM_CHECK( to_next == &wc );
  EXAM_CHECK( cvt.in(state, &c, &c + 1, from_next, &wc, &wc + 1, to_next) == codecvt_base::ok );
  EXAM_CHECK( wc == L'0' );
  EXAM_CHECK( to_next == &wc + 1 );
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(codecvt_test::_936_to_wchar)
{
#if !defined (STLPORT) || (!defined (_STLP_NO_WCHAR_T) && defined (_STLP_USE_EXCEPTIONS)) \
                       || !defined (_STLP_USE_NO_IOSTREAMS)
  try {
    wstring cp936_wstr;
    const string cp936_str = "\xd6\xd0\xb9\xfa\xc9\xe7\xbb\xe1\xbf\xc6\xd1\xa7\xd4\xba\xb7\xa2\xb2\xbc\x32\x30\x30\x38\xc4\xea\xa1\xb6\xbe\xad\xbc\xc3\xc0\xb6\xc6\xa4\xca\xe9\xa1\xb7\xd6\xb8\xb3\xf6\xa3\xac\x32\x30\x30\x37\xc4\xea\xd6\xd0\xb9\xfa\xbe\xad\xbc\xc3\xd4\xf6\xb3\xa4\xd3\xc9\xc6\xab\xbf\xec\xd7\xaa\xcf\xf2\xb9\xfd\xc8\xc8\xb5\xc4\xc7\xf7\xca\xc6\xc3\xf7\xcf\xd4\xd4\xa4\xbc\xc6\xc8\xab\xc4\xea\x47\x44\x50\xd4\xf6\xcb\xd9\xbd\xab\xb4\xef\x31\x31\x2e\x36\x25\xa1\xa3";
    locale loc(locale::classic(), ".936", locale::ctype);
    codecvt<wchar_t, char, mbstate_t> const& cvt = use_facet<codecvt<wchar_t, char, mbstate_t> >(loc);
    mbstate_t state;
    memset(&state, 0, sizeof(mbstate_t));

    codecvt_base::result res;

    {
      wchar_t wbuf[4096];
      // Check we will have enough room for the generated wide string generated from the whole char buffer:
      int len = cvt.length(state, cp936_str.data(), cp936_str.data() + cp936_str.size(), sizeof(wbuf) / sizeof(wchar_t));
      EXAM_CHECK( cp936_str.size() == (size_t)len );

      const char *from_next;
      wchar_t *to_next;
      res = cvt.in(state, cp936_str.data(), cp936_str.data() + cp936_str.size(), from_next,
                          wbuf, wbuf + sizeof(wbuf) / sizeof(wchar_t), to_next);
      EXAM_CHECK( res == codecvt_base::ok );
      EXAM_CHECK( from_next == cp936_str.data() + cp936_str.size() );
      cp936_wstr.assign(wbuf, to_next);
    }

    {
      const wchar_t *from_next;
      char buf[4096];
      char *to_next;
      res = cvt.out(state, cp936_wstr.data(), cp936_wstr.data() + cp936_wstr.size(), from_next,
                           buf, buf + sizeof(buf), to_next);
      EXAM_CHECK( res == codecvt_base::ok );
      EXAM_CHECK( string(buf, to_next) == cp936_str );
    }
  }
  catch (const runtime_error&) {
    throw exam::skip_exception(); // Not enough platform localization support to check 936 code page encoding.
  }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(codecvt_test::utf8_to_wchar)
{
#if !defined (STLPORT) || (!defined (_STLP_NO_WCHAR_T) && defined (_STLP_USE_EXCEPTIONS)) \
                       || !defined (_STLP_USE_NO_IOSTREAMS)
  try {
    wstring utf8_wstr;
    const string utf8_str = "\xd0\x97\xd0\xb4\xd1\x80\xd0\xb0\xd0\xb2\xd1\x81\xd1\x82\xd0\xb2\xd1\x83\xd0\xb9\x2c\x20\xd0\xbc\xd0\xb8\xd1\x80\x21\x0a";
    locale loc(locale::classic(), "en_US.UTF-8", locale::ctype);
    codecvt<wchar_t, char, mbstate_t> const& cvt = use_facet<codecvt<wchar_t, char, mbstate_t> >(loc);
    mbstate_t state;
    memset(&state, 0, sizeof(mbstate_t));

    codecvt_base::result res;

    {
      wchar_t wbuf[4096];
      // Check we will have enough room for the generated wide string generated from the whole char buffer:
      int len = cvt.length(state, utf8_str.data(), utf8_str.data() + utf8_str.size(), sizeof(wbuf) / sizeof(wchar_t));
      EXAM_CHECK( utf8_str.size() == (size_t)len );

      const char *from_next;
      wchar_t *to_next;
      res = cvt.in(state, utf8_str.data(), utf8_str.data() + utf8_str.size(), from_next,
                          wbuf, wbuf + sizeof(wbuf) / sizeof(wchar_t), to_next);
      EXAM_CHECK( res == codecvt_base::ok );
      EXAM_CHECK( from_next == utf8_str.data() + utf8_str.size() );
      utf8_wstr.assign(wbuf, to_next);
    }

    {
      const wchar_t *from_next;
      char buf[4096];
      char *to_next;
      res = cvt.out(state, utf8_wstr.data(), utf8_wstr.data() + utf8_wstr.size(), from_next,
                           buf, buf + sizeof(buf), to_next);
      EXAM_CHECK( res == codecvt_base::ok );
      EXAM_CHECK( string(buf, to_next) == utf8_str );
    }
  }
  catch (const runtime_error&) {
    throw exam::skip_exception(); // Not enough platform localization support to check 936 code page encoding.
  }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(codecvt_test::partial_conversion)
{
#if !defined (STLPORT) || (!defined (_STLP_NO_WCHAR_T) && defined (_STLP_USE_EXCEPTIONS)) \
                       || !defined (_STLP_USE_NO_IOSTREAMS)
  try {
    const string utf8_str = "\xe4\xb8\xad\xe5\x9b\xbd\xe7\xa4\xbe\xe4\xbc\x9a\xe7\xa7\x91\xe5\xad\xa6\xe9\x99\xa2\xe5\x8f\x91\xe5\xb8\x83\x32\x30\x30\x38\xe5\xb9\xb4\xe3\x80\x8a\xe7\xbb\x8f\xe6\xb5\x8e\xe8\x93\x9d\xe7\x9a\xae\xe4\xb9\xa6\xe3\x80\x8b\xe6\x8c\x87\xe5\x87\xba\xef\xbc\x8c\x32\x30\x30\x37\xe5\xb9\xb4\xe4\xb8\xad\xe5\x9b\xbd\xe7\xbb\x8f\xe6\xb5\x8e\xe5\xa2\x9e\xe9\x95\xbf\xe7\x94\xb1\xe5\x81\x8f\xe5\xbf\xab\xe8\xbd\xac\xe5\x90\x91\xe8\xbf\x87\xe7\x83\xad\xe7\x9a\x84\xe8\xb6\x8b\xe5\x8a\xbf\xe6\x98\x8e\xe6\x98\xbe\xe9\xa2\x84\xe8\xae\xa1\xe5\x85\xa8\xe5\xb9\xb4\x47\x44\x50\xe5\xa2\x9e\xe9\x80\x9f\xe5\xb0\x86\xe8\xbe\xbe\x31\x31\x2e\x36\x25\xe3\x80\x82";
    wstring utf8_wstr;
    locale loc(locale::classic(), new codecvt_byname<wchar_t, char, mbstate_t>("en_US.UTF8"));
    codecvt<wchar_t, char, mbstate_t> const& cvt = use_facet<codecvt<wchar_t, char, mbstate_t> >(loc);
    mbstate_t state;
    memset(&state, 0, sizeof(mbstate_t));

    wchar_t wbuf[4096];
    // Check we will have enough room for the wide string generated from the whole char buffer:
    int len = cvt.length(state, utf8_str.data(), utf8_str.data() + utf8_str.size(), sizeof(wbuf) / sizeof(wchar_t));
    EXAM_CHECK( utf8_str.size() == (size_t)len );

    const char *from_next;
    wchar_t *to_next;
    codecvt_base::result res = cvt.in(state, utf8_str.data(), utf8_str.data() + utf8_str.size(), from_next,
                                      wbuf, wbuf + sizeof(wbuf) / sizeof(wchar_t), to_next);
    EXAM_CHECK( res == codecvt_base::ok );
    EXAM_CHECK( from_next == utf8_str.data() + utf8_str.size() );
    utf8_wstr.assign(wbuf, to_next);

    // Try to read one char after the other:
    wchar_t wc;
    const char* from = utf8_str.data();
    const char* from_end = from + utf8_str.size();
    from_next = utf8_str.data();
    size_t length = 1;
    size_t windex = 0;

    memset(&state, 0, sizeof(mbstate_t)); // reset state

    while ( (from + length) <= from_end ) {
      switch ( cvt.in(state, from, from + length, from_next, &wc, &wc + 1, to_next) ) {
        case codecvt_base::ok:
          // reset length:
          from = from_next;
          length = 1;
          EXAM_CHECK( wc == utf8_wstr[windex++] );
          wc = 0;
          break;
        case codecvt_base::partial:
          from += length; // continue, use state
          continue;
        case codecvt_base::error:
        case codecvt_base::noconv:
          EXAM_ERROR("codecvt_base error");
          return EXAM_RESULT;
      }
    }
    EXAM_CHECK( windex == utf8_wstr.size() );
  }
  catch (const runtime_error&) {
    throw exam::skip_exception(); // Not enough platform localization support to check UTF8 encoding
  }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

int EXAM_IMPL(codecvt_test::bad_utf8)
{
#if !defined (STLPORT) || (!defined (_STLP_NO_WCHAR_T) && defined (_STLP_USE_EXCEPTIONS)) \
                       || !defined (_STLP_USE_NO_IOSTREAMS)
  try {
    locale loc(locale::classic(), new codecvt_byname<wchar_t, char, mbstate_t>("en_US.UTF8"));
    codecvt<wchar_t, char, mbstate_t> const& cvt = use_facet<codecvt<wchar_t, char, mbstate_t> >(loc);
    mbstate_t state;
    memset(&state, 0, sizeof(mbstate_t));

    // Check that an obviously wrong UTF8 encoded string is correctly detected:
    const string bad_utf8_str("\xdf\xdf\xdf\xdf\xdf");
    wchar_t wc;
    const char *from_next;
    wchar_t *to_next;
    codecvt_base::result res = cvt.in(state, bad_utf8_str.data(), bad_utf8_str.data() + bad_utf8_str.size(), from_next,
                 &wc, &wc + 1, to_next);
    EXAM_CHECK( res == codecvt_base::error );
  }
  catch (const runtime_error&) {
    throw exam::skip_exception(); // Not enough platform localization support to check UTF8 encoding
  }
#else
  throw exam::skip_exception();
#endif
  return EXAM_RESULT;
}

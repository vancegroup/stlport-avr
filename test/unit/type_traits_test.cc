// -*- C++ -*- Time-stamp: <2011-04-29 17:30:57 ptr>

/*
 * Copyright (c) 2007, 2009-2011
 * Petr Ovtchenkov
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#include "type_traits_test.h"

#include <type_traits>

// #include <misc/ratio>

using namespace std;

class MyType
{
  public:

    virtual int abstract() = 0;

  private:
    int a;
    int n;
};

class MyTypeOther
{
  public:

  private:
    int a;
    int n;
};

class MyTypeF
{
  public:
    int f()
      { return 0; }
    virtual int g()
      { return 0; }
    static int h()
      { return 0; }

    int a;
    static int b;
};

int MyTypeF::b = 0;

int f()
{
  return 0;
}

#if defined(STLPORT) || (defined(__GNUC__) && (__GNUC__ < 4))
template <class T>
bool q( T v )
{
  return std::detail::__instance<T>::__value;
}
#endif

int EXAM_IMPL(type_traits_test::type_traits_internals)
{
#if defined(STLPORT) || (defined(__GNUC__) && (__GNUC__ < 4))
  EXAM_CHECK( std::detail::__instance<int []>::__value == true );
  EXAM_CHECK( std::detail::__instance<int *>::__value == true );
  EXAM_CHECK( std::detail::__instance<int&>::__value == false );
  EXAM_CHECK( std::detail::__instance<MyTypeOther>::__value == true );
  EXAM_CHECK( std::detail::__instance<int>::__value == true );
  EXAM_CHECK( std::detail::__instance<MyType>::__value == false );
  EXAM_CHECK( std::detail::__instance<int (*)()>::__value == true );
  EXAM_CHECK( std::detail::__instance<int (&)()>::__value == false );
  EXAM_CHECK( q(f) == true );
#else
  throw exam::skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_void)
{
  EXAM_CHECK( std::is_void<void>::value == true );
  EXAM_CHECK( std::is_void<int>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_integral)
{
  EXAM_CHECK( std::is_integral<bool>::value == true );
  EXAM_CHECK( std::is_integral<char>::value == true );
  EXAM_CHECK( std::is_integral<wchar_t>::value == true );
  EXAM_CHECK( std::is_integral<signed char>::value == true );
  EXAM_CHECK( std::is_integral<unsigned char>::value == true );
  EXAM_CHECK( std::is_integral<short>::value == true );
  EXAM_CHECK( std::is_integral<unsigned short>::value == true );
  EXAM_CHECK( std::is_integral<int>::value == true );
  EXAM_CHECK( std::is_integral<unsigned int>::value == true );
  EXAM_CHECK( std::is_integral<long>::value == true );
  EXAM_CHECK( std::is_integral<unsigned long>::value == true );
  EXAM_CHECK( std::is_integral<long long>::value == true );
  EXAM_CHECK( std::is_integral<unsigned long long>::value == true );

  EXAM_CHECK( std::is_integral<void>::value == false );
  EXAM_CHECK( std::is_integral<double>::value == false );
  EXAM_CHECK( std::is_integral<MyType>::value == false );
  EXAM_CHECK( std::is_integral<MyTypeOther>::value == false );

  EXAM_CHECK( std::is_integral<const bool>::value == true );
  EXAM_CHECK( std::is_integral<volatile bool>::value == true );
  EXAM_CHECK( std::is_integral<const volatile bool>::value == true );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_floating_point)
{
  EXAM_CHECK( std::is_floating_point<float>::value == true );
  EXAM_CHECK( std::is_floating_point<double>::value == true );
  EXAM_CHECK( std::is_floating_point<long double>::value == true );

  EXAM_CHECK( std::is_floating_point<int>::value == false );
  EXAM_CHECK( std::is_floating_point<MyType>::value == false );
  EXAM_CHECK( std::is_floating_point<MyTypeOther>::value == false );

  EXAM_CHECK( std::is_floating_point<const double>::value == true );
  EXAM_CHECK( std::is_floating_point<volatile double>::value == true );
  EXAM_CHECK( std::is_floating_point<const volatile double>::value == true );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_array)
{
  EXAM_CHECK( std::is_array<int [5]>::value == true );
  EXAM_CHECK( std::is_array<int []>::value == true );
  EXAM_CHECK( std::is_array<MyTypeOther []>::value == true );

  EXAM_CHECK( std::is_array<int>::value == false );
  EXAM_CHECK( std::is_array<int *>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_pointer)
{
  EXAM_CHECK( std::is_pointer<int *>::value == true );
  EXAM_CHECK( std::is_pointer<MyType *>::value == true );
  EXAM_CHECK( std::is_pointer<MyTypeOther *>::value == true );
  EXAM_CHECK( std::is_pointer<int (*)()>::value == true );

  EXAM_CHECK( std::is_pointer<int>::value == false );
  EXAM_CHECK( std::is_pointer<int []>::value == false );
  EXAM_CHECK( std::is_pointer<int (MyTypeF::*)()>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_lvalue_reference)
{
  EXAM_CHECK( std::is_lvalue_reference<int &>::value == true );
  EXAM_CHECK( std::is_lvalue_reference<int (&)(void)>::value == true );

  // EXAM_CHECK( std::is_lvalue_reference<int &&>::value == false );
  EXAM_CHECK( std::is_lvalue_reference<int>::value == false );
  EXAM_CHECK( std::is_lvalue_reference<int *>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_rvalue_reference)
{
#ifndef _STLP_RVR
  throw exam::skip_exception();
#else
  EXAM_CHECK( std::is_rvalue_reference<int&&>::value == true );
#endif // _STLP_RVR

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_rvalue_reference_neg)
{
  EXAM_CHECK( std::is_rvalue_reference<int&>::value == false );
  EXAM_CHECK( std::is_rvalue_reference<int>::value == false );
  EXAM_CHECK( std::is_rvalue_reference<int*>::value == false );
  EXAM_CHECK( std::is_rvalue_reference<int (&)()>::value == false );

  return EXAM_RESULT;
}


int EXAM_IMPL(type_traits_test::type_traits_is_member_object_pointer)
{
  EXAM_CHECK( std::is_member_object_pointer<int (MyTypeF::*)>::value == true );

  EXAM_CHECK( std::is_member_object_pointer<int (MyTypeF::*)()>::value == false );
  EXAM_CHECK( std::is_member_object_pointer<int *>::value == false );
  EXAM_CHECK( std::is_member_object_pointer<int (*)()>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_member_function_pointer)
{
  EXAM_CHECK( std::is_member_function_pointer<int (MyTypeF::*)()>::value == true );

  EXAM_CHECK( std::is_member_function_pointer<int (MyTypeF::*)>::value == false );
  EXAM_CHECK( std::is_member_function_pointer<int *>::value == false );
  EXAM_CHECK( std::is_member_function_pointer<int (*)()>::value == false );
  EXAM_CHECK( std::is_member_function_pointer<int (&)()>::value == false );

  return EXAM_RESULT;
}

enum enum_type { one, two, three };

int EXAM_IMPL(type_traits_test::type_traits_is_enum)
{
  EXAM_CHECK( std::is_enum<enum_type>::value == true );

  EXAM_CHECK( std::is_enum<int>::value == false );
  EXAM_CHECK( std::is_enum<char>::value == false );

  return EXAM_RESULT;
}

union union_type
{
    int a;
    char c;
};

struct structure_type
{
    int a;
    char c;
};

class class_type
{
    int a;
    char c;
};


int EXAM_IMPL(type_traits_test::type_traits_is_union)
{
  EXAM_CHECK( std::is_union<union_type>::value == true );

  EXAM_CHECK( std::is_union<structure_type>::value == false );
  EXAM_CHECK( std::is_union<class_type>::value == false );
  EXAM_CHECK( std::is_union<int>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_class)
{
  EXAM_CHECK( std::is_class<structure_type>::value == true );
  EXAM_CHECK( std::is_class<class_type>::value == true );

  EXAM_CHECK( std::is_class<union_type>::value == false );
  EXAM_CHECK( std::is_class<int>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_function)
{
  EXAM_CHECK( std::is_function<int (void)>::value == true );
  EXAM_CHECK( std::is_function<int (int)>::value == true );

  EXAM_CHECK( std::is_function<int (&)()>::value == false );
  EXAM_CHECK( std::is_function<int (*)()>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_reference)
{
  EXAM_CHECK( std::is_reference<int &>::value == true );
  EXAM_CHECK( std::is_reference<int (&)(void)>::value == true );
  // EXAM_CHECK( std::is_lvalue_reference<int &&>::value == true );

  EXAM_CHECK( std::is_reference<int>::value == false );
  EXAM_CHECK( std::is_reference<int *>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_arithmetic)
{
  EXAM_CHECK( std::is_arithmetic<bool>::value == true );
  EXAM_CHECK( std::is_arithmetic<char>::value == true );
  EXAM_CHECK( std::is_arithmetic<wchar_t>::value == true );
  EXAM_CHECK( std::is_arithmetic<signed char>::value == true );
  EXAM_CHECK( std::is_arithmetic<unsigned char>::value == true );
  EXAM_CHECK( std::is_arithmetic<short>::value == true );
  EXAM_CHECK( std::is_arithmetic<unsigned short>::value == true );
  EXAM_CHECK( std::is_arithmetic<int>::value == true );
  EXAM_CHECK( std::is_arithmetic<unsigned int>::value == true );
  EXAM_CHECK( std::is_arithmetic<long>::value == true );
  EXAM_CHECK( std::is_arithmetic<unsigned long>::value == true );
  EXAM_CHECK( std::is_arithmetic<long long>::value == true );
  EXAM_CHECK( std::is_arithmetic<unsigned long long>::value == true );
  EXAM_CHECK( std::is_arithmetic<float>::value == true );
  EXAM_CHECK( std::is_arithmetic<double>::value == true );
  EXAM_CHECK( std::is_arithmetic<long double>::value == true );

  EXAM_CHECK( std::is_arithmetic<enum_type>::value == false );
  EXAM_CHECK( std::is_arithmetic<int *>::value == false );
  EXAM_CHECK( std::is_arithmetic<MyTypeOther>::value == false );
  EXAM_CHECK( std::is_arithmetic<int &>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_fundamental)
{
  EXAM_CHECK( std::is_fundamental<bool>::value == true );
  EXAM_CHECK( std::is_fundamental<char>::value == true );
  EXAM_CHECK( std::is_fundamental<wchar_t>::value == true );
  EXAM_CHECK( std::is_fundamental<signed char>::value == true );
  EXAM_CHECK( std::is_fundamental<unsigned char>::value == true );
  EXAM_CHECK( std::is_fundamental<short>::value == true );
  EXAM_CHECK( std::is_fundamental<unsigned short>::value == true );
  EXAM_CHECK( std::is_fundamental<int>::value == true );
  EXAM_CHECK( std::is_fundamental<unsigned int>::value == true );
  EXAM_CHECK( std::is_fundamental<long>::value == true );
  EXAM_CHECK( std::is_fundamental<unsigned long>::value == true );
  EXAM_CHECK( std::is_fundamental<long long>::value == true );
  EXAM_CHECK( std::is_fundamental<unsigned long long>::value == true );
  EXAM_CHECK( std::is_fundamental<float>::value == true );
  EXAM_CHECK( std::is_fundamental<double>::value == true );
  EXAM_CHECK( std::is_fundamental<long double>::value == true );
  EXAM_CHECK( std::is_fundamental<void>::value == true );

  EXAM_CHECK( std::is_fundamental<enum_type>::value == false );
  EXAM_CHECK( std::is_fundamental<int *>::value == false );
  EXAM_CHECK( std::is_fundamental<MyTypeOther>::value == false );
  EXAM_CHECK( std::is_fundamental<int &>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_object)
{
  EXAM_CHECK( std::is_object<int>::value == true );
  EXAM_CHECK( std::is_object<MyTypeOther>::value == true );
  EXAM_CHECK( std::is_object<int*>::value == true );
  EXAM_CHECK( std::is_object<int (*)()>::value == true );
  EXAM_CHECK( std::is_object<int (MyTypeF::*)()>::value == true );
  EXAM_CHECK( std::is_object<int (MyTypeF::*)>::value == true );

  EXAM_CHECK( std::is_object<int (void)>::value == false );
  EXAM_CHECK( std::is_object<int&>::value == false );
  EXAM_CHECK( std::is_object<void>::value == false );
  EXAM_CHECK( std::is_object<enum_type>::value == false );
  EXAM_CHECK( std::is_object<int (&)()>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_scalar)
{
  EXAM_CHECK( std::is_scalar<int>::value == true );
  EXAM_CHECK( std::is_scalar<int*>::value == true );
  EXAM_CHECK( std::is_scalar<int (MyTypeF::*)()>::value == true );
  EXAM_CHECK( std::is_scalar<int (*)()>::value == true );
  EXAM_CHECK( std::is_scalar<enum_type>::value == true );

  EXAM_CHECK( std::is_scalar<MyTypeOther>::value == false );
  EXAM_CHECK( std::is_scalar<int (void)>::value == false );
  EXAM_CHECK( std::is_scalar<int&>::value == false );
  EXAM_CHECK( std::is_scalar<void>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_compound)
{
  EXAM_CHECK( std::is_compound<enum_type>::value == true );
  EXAM_CHECK( std::is_compound<int *>::value == true );
  EXAM_CHECK( std::is_compound<MyTypeOther>::value == true );
  EXAM_CHECK( std::is_compound<int &>::value == true );
  EXAM_CHECK( std::is_compound<int (*)()>::value == true );
  EXAM_CHECK( std::is_compound<int (&)()>::value == true );
  EXAM_CHECK( std::is_compound<int (MyTypeF::*)()>::value == true );
  EXAM_CHECK( std::is_compound<int (void)>::value == true );

  EXAM_CHECK( std::is_compound<bool>::value == false );
  EXAM_CHECK( std::is_compound<char>::value == false );
  EXAM_CHECK( std::is_compound<wchar_t>::value == false );
  EXAM_CHECK( std::is_compound<signed char>::value == false );
  EXAM_CHECK( std::is_compound<unsigned char>::value == false );
  EXAM_CHECK( std::is_compound<short>::value == false );
  EXAM_CHECK( std::is_compound<unsigned short>::value == false );
  EXAM_CHECK( std::is_compound<int>::value == false );
  EXAM_CHECK( std::is_compound<unsigned int>::value == false );
  EXAM_CHECK( std::is_compound<long>::value == false );
  EXAM_CHECK( std::is_compound<unsigned long>::value == false );
  EXAM_CHECK( std::is_compound<long long>::value == false );
  EXAM_CHECK( std::is_compound<unsigned long long>::value == false );
  EXAM_CHECK( std::is_compound<float>::value == false );
  EXAM_CHECK( std::is_compound<double>::value == false );
  EXAM_CHECK( std::is_compound<long double>::value == false );
  EXAM_CHECK( std::is_compound<void>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_member_pointer)
{
  EXAM_CHECK( std::is_member_pointer<int (MyTypeF::*)>::value == true );
  EXAM_CHECK( std::is_member_pointer<int (MyTypeF::*)()>::value == true );

  EXAM_CHECK( std::is_member_pointer<int>::value == false );
  EXAM_CHECK( std::is_member_pointer<int *>::value == false );
  EXAM_CHECK( std::is_member_pointer<int (*)()>::value == false );
  EXAM_CHECK( std::is_member_pointer<int (&)()>::value == false );
  EXAM_CHECK( std::is_member_pointer<int (void)>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_const)
{
  EXAM_CHECK( std::is_const<const int>::value == true );
  EXAM_CHECK( std::is_const<const volatile int>::value == true );
  EXAM_CHECK( std::is_const<int* const>::value == true );
  EXAM_CHECK( std::is_const<int* const volatile>::value == true );

  EXAM_CHECK( std::is_const<const int*>::value == false );
  EXAM_CHECK( std::is_const<int>::value == false );
  EXAM_CHECK( std::is_const<volatile int>::value == false );
  EXAM_CHECK( std::is_const<const int&>::value == false );
#ifdef _STLP_RVR
  EXAM_CHECK( std::is_const<const int&&>::value == false );
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_volatile)
{
  EXAM_CHECK( std::is_volatile<volatile int>::value == true );
  EXAM_CHECK( std::is_volatile<const volatile int>::value == true );
  EXAM_CHECK( std::is_volatile<int* volatile>::value == true );
  EXAM_CHECK( std::is_volatile<int* const volatile>::value == true );

  EXAM_CHECK( std::is_volatile<volatile int*>::value == false );
  EXAM_CHECK( std::is_volatile<int>::value == false );
  EXAM_CHECK( std::is_volatile<const int>::value == false );
  EXAM_CHECK( std::is_volatile<const volatile int&>::value == false );
  EXAM_CHECK( std::is_volatile<volatile int&>::value == false );
#ifdef _STLP_RVR
  EXAM_CHECK( std::is_volatile<volatile int&&>::value == false );
#endif

  return EXAM_RESULT;
}

struct N   // neither trivial nor standard-layout
{
    int i;
    int j;

    virtual ~N()
      { }
};

struct T   // trivial, but not standard-layout
{
    int i;

  private:
    int j;
};

struct SL  // standard-layout, but not trivial
{
    int i;
    int j;

    ~SL()
      { }
};

struct POD // both trivial and standard-layout, aka POD
{
    int i;
    int j;
};

struct NT  // standard-layout, but not trivial
{
    SL i;
    int j;
};

int EXAM_IMPL(type_traits_test::type_traits_is_trivial)
{
  EXAM_CHECK( std::is_trivial<const int>::value == true );
  EXAM_CHECK( std::is_trivial<int *>::value == true );
  EXAM_CHECK( std::is_trivial<T>::value == true );
  EXAM_CHECK( std::is_trivial<POD>::value == true );

  EXAM_CHECK( std::is_trivial<N>::value == false );
  EXAM_CHECK( std::is_trivial<SL>::value == false );
  EXAM_CHECK( std::is_trivial<NT>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_standard_layout)
{
  EXAM_CHECK( std::is_standard_layout<const int>::value == true );
  EXAM_CHECK( std::is_standard_layout<int *>::value == true );
  EXAM_CHECK( std::is_standard_layout<SL>::value == true );
  EXAM_CHECK( std::is_standard_layout<NT>::value == true );
  EXAM_CHECK( std::is_standard_layout<POD>::value == true );

  EXAM_CHECK( std::is_standard_layout<N>::value == false );
  EXAM_CHECK( std::is_standard_layout<T>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_pod)
{
  EXAM_CHECK( std::is_pod<const int>::value == true );
  EXAM_CHECK( std::is_pod<int *>::value == true );

  EXAM_CHECK( std::is_pod<SL>::value == false );
  EXAM_CHECK( std::is_pod<N>::value == false );
  EXAM_CHECK( std::is_pod<T>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::type_traits_is_pod_compiler_supp)
{
#if defined(__GNUC__) && ((__GNUC__ < 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ < 3)) )
  throw exam::skip_exception();
#endif

  EXAM_CHECK( std::is_pod<NT>::value == false );
  EXAM_CHECK( std::is_standard_layout<NT>::value == true );
  EXAM_CHECK( std::is_trivial<NT>::value == false );
  EXAM_CHECK( std::is_pod<POD>::value == true );

  return EXAM_RESULT;
}

class empty
{
};

class not_empty1
{
  private:
    int k;
};

class empty1
{
  private:
    int f() const
      { return 0; }
};

class not_empty3
{
  private:
    virtual int f() const
      { return 0; }
};

class empty2 :
    public empty1
{
};

class not_empty5 :
    public not_empty3
{
};

int EXAM_IMPL(type_traits_test::type_traits_is_empty)
{
  EXAM_CHECK( std::is_empty<empty>::value == true );
  EXAM_CHECK( std::is_empty<not_empty1>::value == false );
  EXAM_CHECK( std::is_empty<empty1>::value == true );
  EXAM_CHECK( std::is_empty<not_empty3>::value == false );
  EXAM_CHECK( std::is_empty<int>::value == false );
  // EXAM_CHECK( std::is_empty<int (&)()>::value == false );
  EXAM_CHECK( std::is_empty<empty2>::value == true );
  EXAM_CHECK( std::is_empty<not_empty5>::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::is_constructible)
{
  class MyOther
  {
    public:
      MyOther()
        { }
      MyOther( int )
        { }
  };

  class MyFrom
  {
    public:
      MyFrom()
        { }
  };

  class MyTo
  {
    public:
      MyTo( const MyFrom& )
        { }
  };

  // This trick is because problem with comma (',') in macro:

  typedef std::is_constructible<MyTo,MyFrom> T1;
  typedef std::is_constructible<MyTo,MyOther> T2;
  typedef std::is_constructible<MyTo,int> T3;
  typedef std::is_constructible<MyOther,int> T4;
  typedef std::is_constructible<int,double> T5;

  EXAM_CHECK( T1::value == true );
  EXAM_CHECK( T2::value == false );
  EXAM_CHECK( T3::value == false );
  EXAM_CHECK( T4::value == true );
  EXAM_CHECK( T5::value == true );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::is_assignable)
{
  struct MyOne
  {
      MyOne& operator =(int)
        { return *this; }
  };

  struct MyTwo
  {
      MyTwo(int)
        { }
  };

  typedef std::is_assignable<int,double> T1;
  typedef std::is_assignable<double,int> T2;
  typedef std::is_assignable<MyOne,int> T3;
  typedef std::is_assignable<MyTwo,int> T4;
  typedef std::is_assignable<int,MyOne> T5;
  typedef std::is_assignable<int,MyTwo> T6;

  EXAM_CHECK( T1::value == true );
  EXAM_CHECK( T2::value == true );
  EXAM_CHECK( T3::value == true );
  EXAM_CHECK( T4::value == true );

  EXAM_CHECK( T5::value == false );
  EXAM_CHECK( T6::value == false );

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::is_destructible)
{
  struct My
  {
  };

  struct Other
  {
      ~Other() = delete;
  };

  class YetAnother
  {
    private:
      ~YetAnother();
      // { }
  };

  typedef std::is_destructible<My> T1;
  typedef std::is_destructible<Other> T2;
  typedef std::is_destructible<YetAnother> T3;
  typedef std::is_destructible<int> T4;

  EXAM_CHECK( T1::value == true );
  EXAM_CHECK( T2::value == false );
  EXAM_CHECK( T3::value == false );
  EXAM_CHECK( T4::value == true );

  // Other x;
  // YetAnother y;

  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::is_trivially_copyable)
{
  struct Base
  {
      int x;
  };

  struct Derive :
    public Base
  {
      Derive() :
          flag( false )
        { }

      Derive( const Derive& ) :
          flag( true )
        { }
          
      bool flag;
  };

  struct DeriveA :
    public Base
  {
      DeriveA() :
          flag( false )
        { }

      DeriveA( const Base& ) :
          flag( true )
        { }
          
      bool flag;
  };

  typedef std::is_trivially_copyable<Base> T1;
  typedef std::is_trivially_copyable<Derive> T2;
  typedef std::is_trivially_copyable<DeriveA> T3;

  EXAM_CHECK( T1::value == true );
  EXAM_CHECK( T2::value == false ); // non-trivial copy ctor
  EXAM_CHECK( T3::value == true );  // trivial copy ctor

  Base b;
  DeriveA a0;
  DeriveA a1( a0 );
  DeriveA a2( b );

  EXAM_CHECK( a1.flag == false ); // trivial copy ctor
  EXAM_CHECK( a2.flag == true );  // non-trivial copy ctor

  return EXAM_RESULT;
}

struct X
{
};

struct Y
{
    Y()
      { }
    Y( const X& )
      { }
};

#if defined(STLPORT) || (defined(__GNUC__) && (__GNUC__ < 4))
template <class T>
struct __ctor_aux : // union or class
    public std::detail::__select_types
{
  private:
    template <class _Up>
    static __t1 __test( int (_Up::*)() );

    template <class>
    static __t2 __test(...);
    
  public:
#ifdef __FIT_NO_INLINE_TEMPLATE_STATIC_INITIALISATION
    static const bool __value;
#else
    static const bool __value = sizeof(__test<T>(0)) == sizeof(std::detail::__select_types::__t1);
#endif
};

#ifdef __FIT_NO_INLINE_TEMPLATE_STATIC_INITIALISATION
template <class T>
const bool __ctor_aux<T>::__value = sizeof(__ctor_aux<T>::__test<T>(0)) == sizeof(std::detail::__select_types::__t1);
#endif

#endif // used misc/type_traits.h or STLport's implementation (it's same)

#if 0

int EXAM_IMPL(type_traits_has_x_ctor)
{
  return EXAM_RESULT;
}

int EXAM_IMPL(type_traits_test::ratio)
{
  EXAM_CHECK( (std::ratio<1,1>::num == 1LL) && (std::ratio<1,1>::den == 1LL) );
  EXAM_CHECK( (std::ratio<2,1>::num == 2LL) && (std::ratio<2,1>::den == 1LL) );
  EXAM_CHECK( (std::ratio<1,2>::num == 1LL) && (std::ratio<1,2>::den == 2LL) );
  EXAM_CHECK( (std::ratio<2,2>::num == 1LL) && (std::ratio<2,2>::den == 1LL) );
  EXAM_CHECK( (std::ratio<100,5>::num == 20LL) && (std::ratio<100,5>::den == 1LL) );
  EXAM_CHECK( (std::ratio<-10,100>::num == -1LL) && (std::ratio<-10,100>::den == 10LL) );
  EXAM_CHECK( (std::ratio<3,-5>::num == -3LL) && (std::ratio<3,-5>::den == 5LL) );
  EXAM_CHECK( (std::ratio<7>::num == 7LL) && (std::ratio<7>::den == 1LL) );

  typedef std::ratio<3,5> three_five;
  typedef std::ratio<2,7> two_seven;

  EXAM_CHECK( (std::ratio_add<three_five,two_seven>::type::num == 31LL) && (std::ratio_add<three_five,two_seven>::type::den == 35LL) );

  EXAM_CHECK( (std::ratio_add<std::atto,std::atto>::type::num == 1LL) && (std::ratio_add<std::atto,std::atto>::type::den == 500000000000000000LL) );

  EXAM_CHECK( (std::ratio_subtract<std::femto,std::atto>::type::num == 999LL) && (std::ratio_subtract<std::femto,std::atto>::type::den == 1000000000000000000LL) );

  EXAM_CHECK( (std::ratio_multiply<std::femto,std::peta>::type::num == 1LL) && (std::ratio_multiply<std::femto,std::peta>::type::den == 1LL) );

  EXAM_CHECK( (std::ratio_divide<std::micro,std::nano>::type::num == 1000LL) && (std::ratio_divide<std::micro,std::nano>::type::den == 1LL) );

  EXAM_CHECK( (std::ratio_equal<std::milli,std::milli>::value) );

  EXAM_CHECK( (!std::ratio_equal<std::milli,std::kilo>::value) );

  EXAM_CHECK( (std::ratio_not_equal<std::milli,std::kilo>::value) );

  EXAM_CHECK( (std::ratio_less<std::mega,std::giga>::value) );

  return EXAM_RESULT;
}

#endif // 0

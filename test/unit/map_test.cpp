// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2004-2008
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
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

#include "map_test.h"

//Has to be first for StackAllocator swap overload to be taken
//into account (at least using GCC 4.0.1)
#include "stack_allocator.h"

#include <map>
#include <algorithm>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

int EXAM_IMPL(map_test::map1)
{
  typedef map<char, int, less<char> > maptype;
  maptype m;
  // Store mappings between roman numerals and decimals.
  m['l'] = 50;
  m['x'] = 20; // Deliberate mistake.
  m['v'] = 5;
  m['i'] = 1;
//  cout << "m['x'] = " << m['x'] << endl;
  EXAM_CHECK( m['x']== 20 );
  m['x'] = 10; // Correct mistake.
  EXAM_CHECK( m['x']== 10 );
  EXAM_CHECK( m['z']== 0 );
  //cout << "m['z'] = " << m['z'] << endl; // Note default value is added.
  EXAM_CHECK( m.count('z') == 1 );
  //cout << "m.count('z') = " << m.count('z') << endl;
  pair<maptype::iterator, bool> p = m.insert(pair<const char, int>('c', 100));
  EXAM_CHECK( p.second );
  EXAM_CHECK( p.first != m.end() );
  EXAM_CHECK( (*p.first).first == 'c' );
  EXAM_CHECK( (*p.first).second == 100 );

  p = m.insert(pair<const char, int>('c', 100));
  EXAM_CHECK( !p.second ); // already existing pair
  EXAM_CHECK( p.first != m.end() );
  EXAM_CHECK( (*p.first).first == 'c' );
  EXAM_CHECK( (*p.first).second == 100 );

  return EXAM_RESULT;
}

int EXAM_IMPL(map_test::mmap1)
{
  typedef multimap<char, int, less<char> > mmap;
  mmap m;
  EXAM_CHECK(m.count('X')==0);

  m.insert(pair<const char, int>('X', 10)); // Standard way.
  EXAM_CHECK(m.count('X')==1);

  m.insert(pair<const char, int>('X', 20)); // jbuck: standard way
  EXAM_CHECK(m.count('X')==2);

  m.insert(pair<const char, int>('Y', 32)); // jbuck: standard way
  mmap::iterator i = m.find('X'); // Find first match.
#ifndef _STLP_CONST
#  define _STLP_CONST const
#endif
  pair<_STLP_CONST char, int> p('X', 10);
  EXAM_CHECK(*i == p);
  EXAM_CHECK((*i).first == 'X');
  EXAM_CHECK((*i).second == 10);
  i++;
  EXAM_CHECK((*i).first == 'X');
  EXAM_CHECK((*i).second == 20);
  i++;
  EXAM_CHECK((*i).first == 'Y');
  EXAM_CHECK((*i).second == 32);
  i++;
  EXAM_CHECK(i == m.end());

  size_t count = m.erase('X');
  EXAM_CHECK(count==2);

  return EXAM_RESULT;
}

int EXAM_IMPL(map_test::mmap2)
{
  typedef pair<const int, char> pair_type;

  pair_type p1(3, 'c');
  pair_type p2(6, 'f');
  pair_type p3(1, 'a');
  pair_type p4(2, 'b');
  pair_type p5(3, 'x');
  pair_type p6(6, 'f');

  typedef multimap<int, char, less<int> > mmap;

  pair_type array [] = {
    p1,
    p2,
    p3,
    p4,
    p5,
    p6
  };

  mmap m(array + 0, array + 6);
  mmap::iterator i;
  i = m.lower_bound(3);
  EXAM_CHECK((*i).first==3);
  EXAM_CHECK((*i).second=='c');

  i = m.upper_bound(3);
  EXAM_CHECK((*i).first==6);
  EXAM_CHECK((*i).second=='f');

  return EXAM_RESULT;
}


int EXAM_IMPL(map_test::iterators)
{
  typedef map<int, char, less<int> > int_map;
  int_map imap;
  {
    int_map::iterator ite(imap.begin());
    int_map::const_iterator cite(imap.begin());
    EXAM_CHECK( ite == cite );
    EXAM_CHECK( !(ite != cite) );
    EXAM_CHECK( cite == ite );
    EXAM_CHECK( !(cite != ite) );
  }

  typedef multimap<int, char, less<int> > mmap;
  typedef mmap::value_type pair_type;

  pair_type p1(3, 'c');
  pair_type p2(6, 'f');
  pair_type p3(1, 'a');
  pair_type p4(2, 'b');
  pair_type p5(3, 'x');
  pair_type p6(6, 'f');

  pair_type array [] = {
    p1,
    p2,
    p3,
    p4,
    p5,
    p6
  };

  mmap m(array+0, array + 6);

  {
    mmap::iterator ite(m.begin());
    mmap::const_iterator cite(m.begin());
    //test compare between const_iterator and iterator
    EXAM_CHECK( ite == cite );
    EXAM_CHECK( !(ite != cite) );
    EXAM_CHECK( cite == ite );
    EXAM_CHECK( !(cite != ite) );
  }

#if 0
  /*
   * A check that map and multimap iterators are NOT comparable
   * the following code should generate a compile time error
   */
  {
    int_map::iterator mite(imap.begin());
    int_map::const_iterator mcite(imap.begin());
    mmap::iterator mmite(m.begin());
    mmap::const_iterator mmcite(m.begin());
    EXAM_CHECK( !(mite == mmite) );
    EXAM_CHECK( !(mcite == mmcite) );
    EXAM_CHECK( mite != mmite );
    EXAM_CHECK( mcite != mmcite );
    EXAM_CHECK( !(mite == mmcite) );
    EXAM_CHECK( !(mite == mmcite) );
    EXAM_CHECK( mite != mmcite );
    EXAM_CHECK( mite != mmcite );
  }

#endif

  mmap::reverse_iterator ri = m.rbegin();
  EXAM_CHECK( ri != m.rend() );
  EXAM_CHECK( ri == m.rbegin() );
  EXAM_CHECK( (*ri).first == 6 );
  EXAM_CHECK( (*ri++).second == 'f' );
  EXAM_CHECK( (*ri).first == 6 );
  EXAM_CHECK( (*ri).second == 'f' );

  mmap const& cm = m;
  mmap::const_reverse_iterator rci = cm.rbegin();
  EXAM_CHECK( rci != cm.rend() );
  EXAM_CHECK( (*rci).first == 6 );
  EXAM_CHECK( (*rci++).second == 'f' );
  EXAM_CHECK( (*rci).first == 6 );
  EXAM_CHECK( (*rci).second == 'f' );

  return EXAM_RESULT;
}

int EXAM_IMPL(map_test::equal_range)
{
  typedef map<char, int, less<char> > maptype;
  {
    maptype m;
    m['x'] = 10;

    pair<maptype::iterator, maptype::iterator> ret;
    ret = m.equal_range('x');
    EXAM_CHECK( ret.first != ret.second );
    EXAM_CHECK( (*(ret.first)).first == 'x' );
    EXAM_CHECK( (*(ret.first)).second == 10 );
    EXAM_CHECK( ++(ret.first) == ret.second );
  }
  {
    {
      maptype m;

      maptype::iterator i = m.lower_bound( 'x' );
      EXAM_CHECK( i == m.end() );

      i = m.upper_bound( 'x' );
      EXAM_CHECK( i == m.end() );

      pair<maptype::iterator, maptype::iterator> ret;
      ret = m.equal_range('x');
      EXAM_CHECK( ret.first == ret.second );
      EXAM_CHECK( ret.first == m.end() );
    }

    {
      const maptype m;
      pair<maptype::const_iterator, maptype::const_iterator> ret;
      ret = m.equal_range('x');
      EXAM_CHECK( ret.first == ret.second );
      EXAM_CHECK( ret.first == m.end() );
    }
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(map_test::allocator_with_state)
{
  char buf1[1024];
  StackAllocator<pair<const int, int> > stack1(buf1, buf1 + sizeof(buf1));

  char buf2[1024];
  StackAllocator<pair<const int, int> > stack2(buf2, buf2 + sizeof(buf2));

  {
    typedef map<int, int, less<int>, StackAllocator<pair<const int, int> > > MapInt;
    less<int> intLess;
    MapInt mint1(intLess, stack1);
    int i;
    for (i = 0; i < 5; ++i)
      mint1.insert(MapInt::value_type(i, i));
    MapInt mint1Cpy(mint1);

    MapInt mint2(intLess, stack2);
    for (; i < 10; ++i)
      mint2.insert(MapInt::value_type(i, i));
    MapInt mint2Cpy(mint2);

    mint1.swap(mint2);

    EXAM_CHECK( mint1.get_allocator().swaped() );
    EXAM_CHECK( mint2.get_allocator().swaped() );

    EXAM_CHECK( mint1 == mint2Cpy );
    EXAM_CHECK( mint2 == mint1Cpy );
    EXAM_CHECK( mint1.get_allocator() == stack2 );
    EXAM_CHECK( mint2.get_allocator() == stack1 );
  }
  EXAM_CHECK( stack1.ok() );
  EXAM_CHECK( stack2.ok() );

  return EXAM_RESULT;
}

struct Key
{
  Key() : m_data(0) {}
  explicit Key(int data) : m_data(data) {}

  int m_data;
};

struct KeyCmp
{
  bool operator () (Key lhs, Key rhs) const
  { return lhs.m_data < rhs.m_data; }

  bool operator () (Key lhs, int rhs) const
  { return lhs.m_data < rhs; }

  bool operator () (int lhs, Key rhs) const
  { return lhs < rhs.m_data; }
};

struct KeyCmpPtr
{
  bool operator () (Key const volatile *lhs, Key const volatile *rhs) const
  { return (*lhs).m_data < (*rhs).m_data; }

  bool operator () (Key const volatile *lhs, int rhs) const
  { return (*lhs).m_data < rhs; }

  bool operator () (int lhs, Key const volatile *rhs) const
  { return lhs < (*rhs).m_data; }
};

int EXAM_IMPL(map_test::template_methods)
{
#if defined (STLPORT) && defined (_STLP_USE_CONTAINERS_EXTENSION)
  {
    typedef map<Key, int, KeyCmp> Container;
    typedef Container::value_type value;
    Container cont;
    cont.insert(value(Key(1), 1));
    cont.insert(value(Key(2), 2));
    cont.insert(value(Key(3), 3));
    cont.insert(value(Key(4), 4));

    EXAM_CHECK( cont.count(Key(1)) == 1 );
    EXAM_CHECK( cont.count(1) == 1 );
    EXAM_CHECK( cont.count(5) == 0 );

    EXAM_CHECK( cont.find(2) != cont.end() );
    EXAM_CHECK( cont.lower_bound(2) != cont.end() );
    EXAM_CHECK( cont.upper_bound(2) != cont.end() );
    EXAM_CHECK( cont.equal_range(2) != make_pair(cont.begin(), cont.end()) );

    Container const& ccont = cont;
    EXAM_CHECK( ccont.find(2) != ccont.end() );
    EXAM_CHECK( ccont.lower_bound(2) != ccont.end() );
    EXAM_CHECK( ccont.upper_bound(2) != ccont.end() );
    EXAM_CHECK( ccont.equal_range(2) != make_pair(ccont.end(), ccont.end()) );
  }

  {
    typedef map<Key*, int, KeyCmpPtr> Container;
    typedef Container::value_type value;
    Container cont;
    Key key1(1), key2(2), key3(3), key4(4);
    cont.insert(value(&key1, 1));
    cont.insert(value(&key2, 2));
    cont.insert(value(&key3, 3));
    cont.insert(value(&key4, 4));

    EXAM_CHECK( cont.count(1) == 1 );
    EXAM_CHECK( cont.count(5) == 0 );

    EXAM_CHECK( cont.find(2) != cont.end() );
    EXAM_CHECK( cont.lower_bound(2) != cont.end() );
    EXAM_CHECK( cont.upper_bound(2) != cont.end() );
    EXAM_CHECK( cont.equal_range(2) != make_pair(cont.begin(), cont.end()) );

    Container const& ccont = cont;
    EXAM_CHECK( ccont.find(2) != ccont.end() );
    EXAM_CHECK( ccont.lower_bound(2) != ccont.end() );
    EXAM_CHECK( ccont.upper_bound(2) != ccont.end() );
    EXAM_CHECK( ccont.equal_range(2) != make_pair(ccont.begin(), ccont.end()) );
  }
  {
    typedef multimap<Key, int, KeyCmp> Container;
    typedef Container::value_type value;
    Container cont;
    cont.insert(value(Key(1), 1));
    cont.insert(value(Key(2), 2));
    cont.insert(value(Key(3), 3));
    cont.insert(value(Key(4), 4));

    EXAM_CHECK( cont.count(Key(1)) == 1 );
    EXAM_CHECK( cont.count(1) == 1 );
    EXAM_CHECK( cont.count(5) == 0 );

    EXAM_CHECK( cont.find(2) != cont.end() );
    EXAM_CHECK( cont.lower_bound(2) != cont.end() );
    EXAM_CHECK( cont.upper_bound(2) != cont.end() );
    EXAM_CHECK( cont.equal_range(2) != make_pair(cont.begin(), cont.end()) );

    Container const& ccont = cont;
    EXAM_CHECK( ccont.find(2) != ccont.end() );
    EXAM_CHECK( ccont.lower_bound(2) != ccont.end() );
    EXAM_CHECK( ccont.upper_bound(2) != ccont.end() );
    EXAM_CHECK( ccont.equal_range(2) != make_pair(ccont.end(), ccont.end()) );
  }

  {
    typedef multimap<Key const volatile*, int, KeyCmpPtr> Container;
    typedef Container::value_type value;
    Container cont;
    Key key1(1), key2(2), key3(3), key4(4);
    cont.insert(value(&key1, 1));
    cont.insert(value(&key2, 2));
    cont.insert(value(&key3, 3));
    cont.insert(value(&key4, 4));

    EXAM_CHECK( cont.count(1) == 1 );
    EXAM_CHECK( cont.count(5) == 0 );

    EXAM_CHECK( cont.find(2) != cont.end() );
    EXAM_CHECK( cont.lower_bound(2) != cont.end() );
    EXAM_CHECK( cont.upper_bound(2) != cont.end() );
    EXAM_CHECK( cont.equal_range(2) != make_pair(cont.begin(), cont.end()) );

    Container const& ccont = cont;
    EXAM_CHECK( ccont.find(2) != ccont.end() );
    EXAM_CHECK( ccont.lower_bound(2) != ccont.end() );
    EXAM_CHECK( ccont.upper_bound(2) != ccont.end() );
    EXAM_CHECK( ccont.equal_range(2) != make_pair(ccont.begin(), ccont.end()) );
  }
#else
  throw exam::skip_exception();
#endif

  return EXAM_RESULT;
}

#if !defined (STLPORT) || \
    !defined (_STLP_USE_PTR_SPECIALIZATIONS) || defined (_STLP_CLASS_PARTIAL_SPECIALIZATION)
#  if !defined (__DMC__)
/* Simple compilation test: Check that nested types like iterator
 * can be access even if type used to instanciate container is not
 * yet completely defined.
 */
class IncompleteClass
{
  map<IncompleteClass, IncompleteClass> instances;
  typedef map<IncompleteClass, IncompleteClass>::iterator it;
  multimap<IncompleteClass, IncompleteClass> minstances;
  typedef multimap<IncompleteClass, IncompleteClass>::iterator mit;
};
#  endif
#endif

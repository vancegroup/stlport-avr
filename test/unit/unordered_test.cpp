// -*- C++ -*- Time-stamp: <2012-04-21 08:34:10 ptr>

/*
 * Copyright (c) 2005-2012
 * Petr Ovtchenkov
 *
 * Copyright (c) 2005-2008
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

#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

const int NB_ELEMS = 2000;

int EXAM_IMPL(unordered_test::uset)
{
#if defined (STLPORT)
  typedef unordered_set<int, hash<int>, equal_to<int> > usettype;
  usettype us;

  //Small compilation check of the copy constructor:
  usettype us2(us);
  //And assignment operator
  us = us2;

  int i;
  pair<usettype::iterator, bool> ret;
  for (i = 0; i < NB_ELEMS; ++i) {
    ret = us.insert(i);
    EXAM_CHECK( ret.second );
    EXAM_CHECK( *ret.first == i );

    ret = us.insert(i);
    EXAM_CHECK( !ret.second );
    EXAM_CHECK( *ret.first == i );
  }

  vector<int> us_val;

  usettype::local_iterator lit, litEnd;
  for (i = 0; i < NB_ELEMS; ++i) {
    lit = us.begin(us.bucket(i));
    litEnd = us.end(us.bucket(i));

    usettype::size_type bucket_pos = us.bucket(*lit);
    for (; lit != litEnd; ++lit) {
      EXAM_CHECK( us.bucket(*lit) == bucket_pos );
      us_val.push_back(*lit);
    }
  }

  //A compilation time check to uncomment from time to time
  {
    //usettype::iterator it;
    //EXAM_CHECK( it != lit );
  }

  sort(us_val.begin(), us_val.end());
  for (i = 0; i < NB_ELEMS; ++i) {
    EXAM_CHECK( us_val[i] == i );
  }
#else
  throw skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(unordered_test::umultiset)
{
#if defined (STLPORT)
  typedef unordered_multiset<int, hash<int>, equal_to<int> > usettype;
  usettype us;

  int i;
  usettype::iterator ret;
  for (i = 0; i < NB_ELEMS; ++i) {
    ret = us.insert(i);
    EXAM_CHECK( *ret == i );

    ret = us.insert(i);
    EXAM_CHECK( *ret == i );
  }

  EXAM_CHECK( us.size() == 2 * NB_ELEMS );
  vector<int> us_val;

  usettype::local_iterator lit, litEnd;
  for (i = 0; i < NB_ELEMS; ++i) {
    lit = us.begin(us.bucket(i));
    litEnd = us.end(us.bucket(i));

    usettype::size_type bucket_pos = us.bucket(*lit);
    for (; lit != litEnd; ++lit) {
      EXAM_CHECK( us.bucket(*lit) == bucket_pos );
      us_val.push_back(*lit);
    }
  }

  sort(us_val.begin(), us_val.end());
  for (i = 0; i < NB_ELEMS; ++i) {
    EXAM_CHECK( us_val[2 * i] == i );
    EXAM_CHECK( us_val[2 * i + 1] == i );
  }
#else
  throw skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(unordered_test::umap)
{
#if defined (STLPORT)
  typedef unordered_map<int, int, hash<int>, equal_to<int> > umaptype;
  umaptype us;

  //Compilation check of the [] operator:
  umaptype us2;
  us[0] = us2[0];
  us.clear();

  {
    //An other compilation check
    typedef unordered_map<int, umaptype> uumaptype;
    uumaptype uus;
    umaptype const& uref = uus[0];
    umaptype ucopy = uus[0];
    ucopy = uref;
    //Avoids warning:
    //(void*)&uref;
  }

  int i;
  pair<umaptype::iterator, bool> ret;
  for (i = 0; i < NB_ELEMS; ++i) {
    umaptype::value_type p1(i, i);
    ret = us.insert(p1);
    EXAM_CHECK( ret.second );
    EXAM_CHECK( *ret.first == p1 );

    umaptype::value_type p2(i, i + 1);
    ret = us.insert(p2);
    EXAM_CHECK( !ret.second );
    EXAM_CHECK( *ret.first == p1 );
  }

  {
    //Lets look for some values to see if everything is normal:
    umaptype::iterator umit;
    for (int j = 0; j < NB_ELEMS; j += NB_ELEMS / 100) {
      umit = us.find(j);

      EXAM_CHECK( umit != us.end() );
      EXAM_CHECK( (*umit).second == j );
    }
  }

  EXAM_CHECK( us.size() == (size_t)NB_ELEMS );
  vector<pair<int, int> > us_val;

  umaptype::local_iterator lit, litEnd;
  for (i = 0; i < NB_ELEMS; ++i) {
    lit = us.begin(us.bucket(i));
    litEnd = us.end(us.bucket(i));

    umaptype::size_type bucket_pos = us.bucket((*lit).first);
    for (; lit != litEnd; ++lit) {
      EXAM_CHECK( us.bucket((*lit).first) == bucket_pos );
      us_val.push_back(make_pair((*lit).first, (*lit).second));
    }
  }

  sort(us_val.begin(), us_val.end());
  for (i = 0; i < NB_ELEMS; ++i) {
    EXAM_CHECK( us_val[i] == make_pair(i, i) );
  }
#else
  throw skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(unordered_test::umultimap)
{
#if defined (STLPORT)
  typedef unordered_multimap<int, int, hash<int>, equal_to<int> > umaptype;
  umaptype us;

  int i;
  umaptype::iterator ret;
  for (i = 0; i < NB_ELEMS; ++i) {
    umaptype::value_type p(i, i);
    ret = us.insert(p);
    EXAM_CHECK( *ret == p );

    ret = us.insert(p);
    EXAM_CHECK( *ret == p );
  }

  EXAM_CHECK( us.size() == 2 * NB_ELEMS );
  typedef pair<int, int> ptype;
  vector<ptype> us_val;

  umaptype::local_iterator lit, litEnd;
  for (i = 0; i < NB_ELEMS; ++i) {
    lit = us.begin(us.bucket(i));
    litEnd = us.end(us.bucket(i));

    umaptype::size_type bucket_pos = us.bucket((*lit).first);
    for (; lit != litEnd; ++lit) {
      EXAM_CHECK( us.bucket((*lit).first) == bucket_pos );
      us_val.push_back(ptype((*lit).first, (*lit).second));
    }
  }

  sort(us_val.begin(), us_val.end());
  for (i = 0; i < NB_ELEMS; ++i) {
    ptype p(i, i);
    EXAM_CHECK( us_val[i * 2] == p );
    EXAM_CHECK( us_val[i * 2 + 1] == p );
  }
#else
  throw skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(unordered_test::user_case)
{
#if defined (STLPORT)
  typedef unordered_map<int, string> UnorderedMap1;
  typedef unordered_map<int, UnorderedMap1> UnorderedMap2;

  UnorderedMap1 foo;
  UnorderedMap2 bar;

  foo.insert(UnorderedMap1::value_type(1, string("test1")));
  foo.insert(UnorderedMap1::value_type(2, string("test2")));
  foo.insert(UnorderedMap1::value_type(3, string("test3")));
  foo.insert(UnorderedMap1::value_type(4, string("test4")));
  foo.insert(UnorderedMap1::value_type(5, string("test5")));

  bar.insert(UnorderedMap2::value_type(0, foo));
  UnorderedMap2::iterator it = bar.find(0);
  EXAM_CHECK( it != bar.end() );

  UnorderedMap1 &body = it->second;
  UnorderedMap1::iterator cur = body.find(3);
  EXAM_CHECK( cur != body.end() );

  body.erase(body.begin(), body.end());
  EXAM_CHECK( body.empty() );
#else
  throw skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(unordered_test::hash_policy)
{
#if defined (STLPORT)
  unordered_set<int> int_uset;

  EXAM_CHECK( int_uset.max_load_factor() == 1.0f );
  EXAM_CHECK( int_uset.load_factor() == 0.0f );

  size_t nbInserts = int_uset.bucket_count() - 1;
  for (int i = 0; (size_t)i < nbInserts; ++i) {
    int_uset.insert(i);
  }
  EXAM_CHECK( int_uset.size() == nbInserts );

  int_uset.max_load_factor(0.5f);
  int_uset.rehash(0);
  EXAM_CHECK( int_uset.load_factor() < int_uset.max_load_factor() );

  size_t bucketsHint = int_uset.bucket_count() + 1;
  int_uset.rehash(bucketsHint);
  EXAM_CHECK( int_uset.bucket_count() >= bucketsHint );

  EXAM_CHECK( int_uset.key_eq()(10, 10) );
  EXAM_CHECK( int_uset.hash_function()(10) == 10 );
#else
  throw skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(unordered_test::buckets)
{
#if defined (STLPORT) 
  unordered_set<int> int_uset;

  EXAM_CHECK( int_uset.bucket_count() < int_uset.max_bucket_count() );

  int i;
  size_t nbBuckets = int_uset.bucket_count();
  size_t nbInserts = int_uset.bucket_count() - 1;
  for (i = 0; (size_t)i < nbInserts; ++i) {
    int_uset.insert(i);
  }
  EXAM_CHECK( nbBuckets == int_uset.bucket_count() );

  size_t bucketSizes = 0;
  for (i = 0; (size_t)i < nbBuckets; ++i) {
    bucketSizes += int_uset.bucket_size(i);
  }
  EXAM_CHECK( bucketSizes == int_uset.size() );
#else
  throw skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(unordered_test::equal_range)
{
#if defined (STLPORT)
  typedef unordered_multiset<size_t> umset;
  {
    //General test
    umset iumset;
    iumset.max_load_factor(10.0f);

    size_t nbBuckets = iumset.bucket_count();

    for (size_t i = 0; i < nbBuckets; ++i) {
      iumset.insert(i);
      iumset.insert(i + nbBuckets);
      iumset.insert(i + 2 * nbBuckets);
      iumset.insert(i + 3 * nbBuckets);
      iumset.insert(i + 4 * nbBuckets);
    }

    EXAM_CHECK( nbBuckets == iumset.bucket_count() );
    EXAM_CHECK( iumset.size() == 5 * nbBuckets );

    pair<umset::iterator, umset::iterator> p = iumset.equal_range(1);
    EXAM_CHECK( p.first != p.second );

    size_t nbElems = iumset.size();
    nbElems -= distance(p.first, p.second);
    for (umset::iterator j = p.first; j != p.second;) {
      iumset.erase(j++);
    }

    EXAM_CHECK( nbElems == iumset.size() );

    p = iumset.equal_range(2);
    EXAM_CHECK( p.first != p.second );
    nbElems -= distance(p.first, p.second);
    iumset.erase(p.first, p.second);
    EXAM_CHECK( nbElems == iumset.size() );
  }

  {
    //More specific test that tries to put many values in the same bucket
    umset iumset;

    size_t i;
    //We are going to add at least 20 values, to get a stable hash container while doing that
    //we force a large number of buckets:
    iumset.rehash(193);

    size_t nbBuckets = iumset.bucket_count();
    EXAM_CHECK( nbBuckets == 193 );
    const size_t targetedBucket = nbBuckets / 2;

    //Lets put 10 values in the targeted bucket:
    for (i = 0; i < 10; ++i) {
      iumset.insert(targetedBucket + (i * nbBuckets));
    }

    //We put again 10 values in the targeted bucket and in reverse order:
    for (i = 9; i <= 10; --i) {
      iumset.insert(targetedBucket + (i * nbBuckets));
    }

    //Now we put some more elements until hash container is resized:
    i = 0;
    while (iumset.bucket_count() == nbBuckets) {
      iumset.insert(i++);
    }

    //EXAM_CHECK( iumset.bucket_size(targetedBucket) == 21 );

    pair<umset::iterator, umset::iterator> p = iumset.equal_range(targetedBucket);
    EXAM_CHECK( p.first != p.second );
    EXAM_CHECK( distance(p.first, p.second) == 3 );

    // Now we remove some elements until hash container is resized:
    nbBuckets = iumset.bucket_count();
    while (iumset.bucket_count() == nbBuckets &&
           !iumset.empty()) {
      iumset.erase(iumset.begin());
    }
    EXAM_CHECK( iumset.load_factor() <= iumset.max_load_factor() );

    // Adding an element back shouldn't change number of buckets:
    nbBuckets = iumset.bucket_count();
    iumset.insert(0);
    EXAM_CHECK( iumset.bucket_count() == nbBuckets );
  }

  {
    srand(0);
    for (int runs = 0; runs < 2; ++runs) {
      size_t magic = rand();
      umset hum;
      size_t c = 0;
      for (int i = 0; i < 10000; ++i) {
        if ((rand() % 500) == 0) {
          hum.insert(magic);
          ++c;
        }
        else {
          size_t r;
          while ((r = rand()) == magic)
            ;
          hum.insert(r);
        }

        /*
        if ((float)(hum.size() + 1) / (float)hum.bucket_count() > hum.max_load_factor()) {
          cout << "Hash container dump: Nb elems: " << hum.size() << ", Nb buckets: " << hum.bucket_count() << "\n";
          for (size_t b = 0; b < hum.bucket_count(); ++b) {
            if (hum.bucket_size(b) != 0) {
              umset::local_iterator litBegin(hum.begin(b)), litEnd(hum.end(b));
              cout << "B" << b << ": ";
              for (umset::local_iterator lit = litBegin; lit != litEnd; ++lit) {
                if (lit != litBegin) {
                  cout << " - ";
                }
                cout << *lit;
              }
              cout << "\n";
            }
          }
          cout << endl;
        }
        */
      }
      EXAM_CHECK( hum.count(magic) == c );
    }
  }
#else
  throw skip_exception();
#endif

  return EXAM_RESULT;
}

#if 0
int EXAM_IMPL(unordered_test::benchmark1)
{
#if defined (STLPORT)
  typedef unordered_multiset<size_t> umset;

  const size_t target = 500000;
  umset iumset;
  iumset.max_load_factor(10);
  size_t i;
  for (i = 0; i < target; ++i) {
    iumset.insert(i);
  }

  for (i = 0; i < target; ++i) {
    iumset.erase(i);
  }
#else
  throw skip_exception();
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(unordered_test::benchmark2)
{
#if defined (STLPORT)
  typedef unordered_multiset<size_t> umset;

  const size_t target = 500000;
  umset iumset;
  iumset.max_load_factor(10);
  size_t i;
  for (i = 0; i < target; ++i) {
    iumset.insert(target - i);
  }

  for (i = 0; i < target; ++i) {
    iumset.erase(target - i);
  }
#else
  throw skip_exception();
#endif

  return EXAM_RESULT;
}
#endif

struct Key
{
  Key() : m_data(0) {}
  explicit Key(int data) : m_data(data) {}

  int m_data;

#if defined (__DMC__) // forward_list<_Tp,_Alloc>::remove error
  bool operator==(const Key&) const;
#endif
};

struct KeyHash
{
  size_t operator () (Key key) const
  { return (size_t)key.m_data; }

  size_t operator () (int data) const
  { return (size_t)data; }
};

struct KeyEqual
{
  bool operator () (Key lhs, Key rhs) const
  { return lhs.m_data == rhs.m_data; }

  bool operator () (Key lhs, int rhs) const
  { return lhs.m_data == rhs; }

  bool operator () (int lhs, Key rhs) const
  { return lhs == rhs.m_data; }
};

struct KeyHashPtr
{
  size_t operator () (Key const volatile *key) const
  { return (size_t)key->m_data; }

  size_t operator () (int data) const
  { return (size_t)data; }
};

struct KeyEqualPtr
{
  bool operator () (Key const volatile *lhs, Key const volatile *rhs) const
  { return lhs->m_data == rhs->m_data; }

  bool operator () (Key const volatile *lhs, int rhs) const
  { return lhs->m_data == rhs; }

  bool operator () (int lhs, Key const volatile *rhs) const
  { return lhs == rhs->m_data; }
};

int EXAM_IMPL(unordered_test::template_methods)
{
#if defined (STLPORT) && defined (_STLP_USE_CONTAINERS_EXTENSION)
  {
    typedef unordered_set<Key, KeyHash, KeyEqual> Container;
    Container cont;
    cont.insert(Key(1));
    cont.insert(Key(2));
    cont.insert(Key(3));
    cont.insert(Key(4));

    EXAM_CHECK( cont.count(Key(1)) == 1 );
    EXAM_CHECK( cont.count(1) == 1 );
    EXAM_CHECK( cont.count(5) == 0 );

    EXAM_CHECK( cont.find(2) != cont.end() );
    EXAM_CHECK( cont.equal_range(2) != make_pair(cont.begin(), cont.end()) );

    Container const& ccont = cont;
    EXAM_CHECK( ccont.find(2) != ccont.end() );
    EXAM_CHECK( ccont.bucket(2) == ccont.bucket(2) );
    EXAM_CHECK( ccont.equal_range(2) != make_pair(ccont.begin(), ccont.end()) );
  }

  {
    typedef unordered_set<Key*, KeyHashPtr, KeyEqualPtr> Container;
    Container cont;
    Key key1(1), key2(2), key3(3), key4(4);
    cont.insert(&key1);
    cont.insert(&key2);
    cont.insert(&key3);
    cont.insert(&key4);

    EXAM_CHECK( cont.count(1) == 1 );
    EXAM_CHECK( cont.count(5) == 0 );

    EXAM_CHECK( cont.find(2) != cont.end() );
    EXAM_CHECK( cont.equal_range(2) != make_pair(cont.begin(), cont.end()) );

    Container const& ccont = cont;
    EXAM_CHECK( ccont.find(2) != ccont.end() );
    EXAM_CHECK( ccont.bucket(2) == ccont.bucket(2) );
    EXAM_CHECK( ccont.equal_range(2) != make_pair(ccont.begin(), ccont.end()) );
  }
  {
    typedef unordered_multiset<Key, KeyHash, KeyEqual> Container;
    Container cont;
    cont.insert(Key(1));
    cont.insert(Key(2));
    cont.insert(Key(1));
    cont.insert(Key(2));

    EXAM_CHECK( cont.count(Key(1)) == 2 );
    EXAM_CHECK( cont.count(1) == 2 );
    EXAM_CHECK( cont.count(5) == 0 );

    EXAM_CHECK( cont.find(2) != cont.end() );
    EXAM_CHECK( cont.equal_range(1) != make_pair(cont.end(), cont.end()) );

    Container const& ccont = cont;
    EXAM_CHECK( ccont.find(2) != ccont.end() );
    EXAM_CHECK( ccont.bucket(2) == ccont.bucket(2) );
    EXAM_CHECK( ccont.equal_range(2) != make_pair(ccont.end(), ccont.end()) );
  }

  {
    typedef unordered_multiset<Key const volatile*, KeyHashPtr, KeyEqualPtr> Container;
    Container cont;
    Key key1(1), key2(2), key3(3), key4(4);
    cont.insert(&key1);
    cont.insert(&key2);
    cont.insert(&key3);
    cont.insert(&key4);

    EXAM_CHECK( cont.count(1) == 1 );
    EXAM_CHECK( cont.count(5) == 0 );

    EXAM_CHECK( cont.find(2) != cont.end() );
    EXAM_CHECK( cont.equal_range(2) != make_pair(cont.begin(), cont.end()) );

    Container const& ccont = cont;
    EXAM_CHECK( ccont.find(2) != ccont.end() );
    EXAM_CHECK( ccont.bucket(2) == ccont.bucket(2) );
    EXAM_CHECK( ccont.equal_range(2) != make_pair(ccont.begin(), ccont.end()) );
  }
#else
  throw skip_exception();
#endif

  return EXAM_RESULT;
}

#if defined (STLPORT) && \
    (!defined (_STLP_USE_PTR_SPECIALIZATIONS) || defined (_STLP_CLASS_PARTIAL_SPECIALIZATION))
/* Simple compilation test: Check that nested types like iterator
 * can be access even if type used to instanciate container is not
 * yet completely defined.
 */
class IncompleteClass
{
  unordered_set<IncompleteClass> usinstances;
  typedef unordered_set<IncompleteClass>::iterator usit;
  unordered_multiset<IncompleteClass> usminstances;
  typedef unordered_multiset<IncompleteClass>::iterator usmit;

  unordered_map<IncompleteClass, IncompleteClass> uminstances;
  typedef unordered_map<IncompleteClass, IncompleteClass>::iterator umit;
  unordered_multimap<IncompleteClass, IncompleteClass> umminstances;
  typedef unordered_multimap<IncompleteClass, IncompleteClass>::iterator ummit;
};
#endif

int EXAM_IMPL(unordered_test::remains)
{
  typedef unordered_map<int, int> hmap;

  hmap m;

  for ( int i = 0; i < 100; ++i ) {
    m.insert( make_pair(i,i) );
  }
  
  EXAM_CHECK( m.size() == 100 );

  int sz = 0;

  for ( hmap::const_iterator i = m.begin(); i != m.end(); ++i ) {
    ++sz;
  }

  EXAM_CHECK( sz == 100 );

  /* 
     <snip>

     The elements of an unordered associative container
     are organized into buckets. Keys with the same hash
     code appear in the same bucket. The number of buckets
     is automatically increased as elements are added
     to an unordered associative container, so that
     the average number of elements per bucket is kept below
     a bound. Rehashing invalidates iterators, changes
     ordering between elements, and changes which buckets
     elements appear in, but does not invalidate pointers
     or references to elements. For unordered_multiset
     and unordered_multimap, rehashing preserves the relative
     ordering of equivalent elements.

     </snip>

     But

     <snip>

     The insert members shall not affect the validity of references
     to container elements, but may invalidate all iterators
     to the container. The erase members shall invalidate only
     iterators and references to the erased elements.

     </snip>

     Rationale: if we would rehash on erase, we can't use
     remove_if() for unordered containers.

   */
  sz = 0;
  for ( hmap::iterator i = m.begin(); i != m.end(); ) {
    m.erase( i++ );
    ++sz;
  }

  // Bug ID: 3004998
  // sz == 98, m.size() == 2

  EXAM_CHECK( sz == 100 );
  EXAM_CHECK( m.size() == 0 );

  for ( int i = 0; i < 100; ++i ) { // re-initiate
    m.insert( make_pair(i,i) );
  }

  /* Another way to erase: */

  sz = 0;
  while ( !m.empty() ) {
    m.erase( m.begin() );
    ++sz;
  }

  EXAM_CHECK( sz == 100 );
  EXAM_CHECK( m.size() == 0 );

  /* Yet another correct code: */

  for ( int i = 0; i < 100; ++i ) { // re-initiate
    m.insert( make_pair(i,i) );
  }

  EXAM_CHECK( m.size() == 100 );

  sz = 0;
  for ( int i = 0; i < 100; ++i ) {
    m.erase( i );
    ++sz;
  }

  EXAM_CHECK( sz == 100 );
  EXAM_CHECK( m.size() == 0 );

  return EXAM_RESULT;
}

int EXAM_IMPL(unordered_test::move)
{
  struct movable
  {
    movable() :
        f( 0 )
      { }

    movable( movable&& r ) :
        f( std::move( r.f ) )
      { }

    movable( const movable& ) = delete;

    int f;
  };

#if !defined(__clang__) || (__clang_major__ > 3) || ((__clang_major__ == 3) && (__clang_minor__ > 1))
  /* CLang 3.0, 3.1 has this problem. CLang pre-3.2 (svn) has not. */
  unordered_map<int,movable> m;

  pair<int,movable> p0;
  pair<int,movable> p1( std::move(p0) );
#else
  /* http://llvm.org/bugs/show_bug.cgi?id=12575

     This testcase is valid depends on how to interpret
     [class.copy] p8: clang assumes "has a copy constructor"
     means something like "is copy constructible".
   */
  throw exam::skip_exception();
#endif

  // m.insert( p0 );

  return EXAM_RESULT;
}

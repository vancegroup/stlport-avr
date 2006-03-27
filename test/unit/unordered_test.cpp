#include <vector>
#if defined (STLPORT)
#  include <algorithm>
#  include <string>
#  include <unordered_map>
#  include <unordered_set>

//#  include <iostream>

#  include "cppunit/cppunit_proxy.h"

#  if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#  endif

//
// TestCase class
//
class UnorderedTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(UnorderedTest);
#  if defined (__DMC__)
  CPPUNIT_IGNORE;
#  endif
  CPPUNIT_TEST(uset);
  CPPUNIT_TEST(umultiset);
  CPPUNIT_TEST(umap);
  CPPUNIT_TEST(umultimap);
  CPPUNIT_TEST(user_case);
  CPPUNIT_TEST(hash_policy);
  CPPUNIT_TEST(buckets);
  CPPUNIT_TEST(equal_range);
  CPPUNIT_TEST_SUITE_END();

protected:
  void uset();
  void umultiset();
  void umap();
  void umultimap();
  void user_case();
  void hash_policy();
  void buckets();
  void equal_range();
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnorderedTest);

const int NB_ELEMS = 2000;

//
// tests implementation
//
void UnorderedTest::uset()
{
#  if !defined (__DMC__)
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
    CPPUNIT_ASSERT( ret.second );
    CPPUNIT_ASSERT( *ret.first == i );

    ret = us.insert(i);
    CPPUNIT_ASSERT( !ret.second );
    CPPUNIT_ASSERT( *ret.first == i );
  }

  vector<int> us_val;

  usettype::local_iterator lit, litEnd;
  for (i = 0; i < NB_ELEMS; ++i) {
    lit = us.begin(us.bucket(i));
    litEnd = us.end(us.bucket(i));

    usettype::size_type bucket_pos = us.bucket(*lit);
    for (; lit != litEnd; ++lit) {
      CPPUNIT_ASSERT( us.bucket(*lit) == bucket_pos );
      us_val.push_back(*lit);
    }
  }

  //A compilation time check to uncomment from time to time
  {
    //usettype::iterator it;
    //CPPUNIT_ASSERT( it != lit );
  }

  sort(us_val.begin(), us_val.end());
  for (i = 0; i < NB_ELEMS; ++i) {
    CPPUNIT_ASSERT( us_val[i] == i );
  }
#  endif
}

void UnorderedTest::umultiset()
{
#  if !defined (__DMC__)
  typedef unordered_multiset<int, hash<int>, equal_to<int> > usettype;
  usettype us;

  int i;
  usettype::iterator ret;
  for (i = 0; i < NB_ELEMS; ++i) {
    ret = us.insert(i);
    CPPUNIT_ASSERT( *ret == i );

    ret = us.insert(i);
    CPPUNIT_ASSERT( *ret == i );
  }

  CPPUNIT_ASSERT( us.size() == 2 * NB_ELEMS );
  vector<int> us_val;

  usettype::local_iterator lit, litEnd;
  for (i = 0; i < NB_ELEMS; ++i) {
    lit = us.begin(us.bucket(i));
    litEnd = us.end(us.bucket(i));

    usettype::size_type bucket_pos = us.bucket(*lit);
    for (; lit != litEnd; ++lit) {
      CPPUNIT_ASSERT( us.bucket(*lit) == bucket_pos );
      us_val.push_back(*lit);
    }
  }

  sort(us_val.begin(), us_val.end());
  for (i = 0; i < NB_ELEMS; ++i) {
    CPPUNIT_ASSERT( us_val[2 * i] == i );
    CPPUNIT_ASSERT( us_val[2 * i + 1] == i );
  }
#  endif
}

void UnorderedTest::umap()
{
#  if !defined (__DMC__)
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
    CPPUNIT_ASSERT( ret.second );
    CPPUNIT_ASSERT( *ret.first == p1 );

    umaptype::value_type p2(i, i + 1);
    ret = us.insert(p2);
    CPPUNIT_ASSERT( !ret.second );
    CPPUNIT_ASSERT( *ret.first == p1 );
  }

  {
    //Lets look for some values to see if everything is normal:
    umaptype::iterator umit;
    for (int j = 0; j < NB_ELEMS; j += NB_ELEMS / 100) {
      umit = us.find(j);

      CPPUNIT_ASSERT( umit != us.end() );
      CPPUNIT_ASSERT( (*umit).second == j );
    }
  }

  CPPUNIT_ASSERT( us.size() == (size_t)NB_ELEMS );
  vector<pair<int, int> > us_val;

  umaptype::local_iterator lit, litEnd;
  for (i = 0; i < NB_ELEMS; ++i) {
    lit = us.begin(us.bucket(i));
    litEnd = us.end(us.bucket(i));

    umaptype::size_type bucket_pos = us.bucket((*lit).first);
    for (; lit != litEnd; ++lit) {
      CPPUNIT_ASSERT( us.bucket((*lit).first) == bucket_pos );
      us_val.push_back(*lit);
    }
  }

  sort(us_val.begin(), us_val.end());
  for (i = 0; i < NB_ELEMS; ++i) {
    CPPUNIT_ASSERT( us_val[i] == make_pair(i, i) );
  }
#  endif
}

void UnorderedTest::umultimap()
{
#  if !defined (__DMC__)
  typedef unordered_multimap<int, int, hash<int>, equal_to<int> > umaptype;
  umaptype us;

  int i;
  umaptype::iterator ret;
  for (i = 0; i < NB_ELEMS; ++i) {
    umaptype::value_type p(i, i);
    ret = us.insert(p);
    CPPUNIT_ASSERT( *ret == p );

    ret = us.insert(p);
    CPPUNIT_ASSERT( *ret == p );
  }

  CPPUNIT_ASSERT( us.size() == 2 * NB_ELEMS );
  typedef pair<int, int> ptype;
  vector<ptype> us_val;

  umaptype::local_iterator lit, litEnd;
  for (i = 0; i < NB_ELEMS; ++i) {
    lit = us.begin(us.bucket(i));
    litEnd = us.end(us.bucket(i));

    umaptype::size_type bucket_pos = us.bucket((*lit).first);
    for (; lit != litEnd; ++lit) {
      CPPUNIT_ASSERT( us.bucket((*lit).first) == bucket_pos );
      us_val.push_back(ptype((*lit).first, (*lit).second));
    }
  }

  sort(us_val.begin(), us_val.end());
  for (i = 0; i < NB_ELEMS; ++i) {
    ptype p(i, i);
    CPPUNIT_ASSERT( us_val[i * 2] == p );
    CPPUNIT_ASSERT( us_val[i * 2 + 1] == p );
  }
#  endif
}

void UnorderedTest::user_case()
{
#  if !defined (__DMC__)
  typedef unordered_map<int, string> UnorderedMap1;
  typedef unordered_map<int, UnorderedMap1> UnorderedMap2;

  UnorderedMap1 foo;
  UnorderedMap2 bar;

  foo.insert(make_pair(1, string("test1")));
  foo.insert(make_pair(2, string("test2")));
  foo.insert(make_pair(3, string("test3")));
  foo.insert(make_pair(4, string("test4")));
  foo.insert(make_pair(5, string("test5")));

  bar.insert(make_pair(0, foo));
  UnorderedMap2::iterator it = bar.find(0);
  CPPUNIT_ASSERT( it != bar.end() );

  UnorderedMap1 &body = it->second;
  UnorderedMap1::iterator cur = body.find(3);
  CPPUNIT_ASSERT( cur != body.end() );

  body.erase(body.begin(), body.end());
  CPPUNIT_ASSERT( body.empty() );
#  endif
}

void UnorderedTest::hash_policy()
{
#  if !defined (__DMC__)
  unordered_set<int> int_uset;

  CPPUNIT_ASSERT( int_uset.max_load_factor() == 1.0f );
  CPPUNIT_ASSERT( int_uset.load_factor() == 0.0f );

  size_t nbInserts = int_uset.bucket_count() - 1;
  for (int i = 0; (size_t)i < nbInserts; ++i) {
    int_uset.insert(i);
  }
  CPPUNIT_ASSERT( int_uset.size() == nbInserts );

  int_uset.max_load_factor(0.5f);
  int_uset.rehash(0);
  CPPUNIT_ASSERT( int_uset.load_factor() < int_uset.max_load_factor() );

  size_t bucketsHint = int_uset.bucket_count() + 1;
  int_uset.rehash(bucketsHint);
  CPPUNIT_ASSERT( int_uset.bucket_count() >= bucketsHint );
#  endif
}

void UnorderedTest::buckets()
{
#  if !defined (__DMC__)
  unordered_set<int> int_uset;

  CPPUNIT_ASSERT( int_uset.bucket_count() < int_uset.max_bucket_count() );

  int i;
  size_t nbBuckets = int_uset.bucket_count();
  size_t nbInserts = int_uset.bucket_count() - 1;
  for (i = 0; (size_t)i < nbInserts; ++i) {
    int_uset.insert(i);
  }
  CPPUNIT_ASSERT( nbBuckets == int_uset.bucket_count() );

  size_t bucketSizes = 0;
  for (i = 0; (size_t)i < nbBuckets; ++i) {
    bucketSizes += int_uset.bucket_size(i);
  }
  CPPUNIT_ASSERT( bucketSizes == int_uset.size() );
#  endif
}

void UnorderedTest::equal_range()
{
#  if !defined (__DMC__)
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

    CPPUNIT_ASSERT( nbBuckets == iumset.bucket_count() );
    CPPUNIT_ASSERT( iumset.size() == 5 * nbBuckets );

    pair<umset::iterator, umset::iterator> p = iumset.equal_range(1);
    CPPUNIT_ASSERT( p.first != p.second );

    size_t nbElems = iumset.size();
    nbElems -= distance(p.first, p.second);
    for (umset::iterator j = p.first; j != p.second;) {
      iumset.erase(j++);
    }

    CPPUNIT_ASSERT( nbElems == iumset.size() );

    p = iumset.equal_range(2);
    CPPUNIT_ASSERT( p.first != p.second );
    nbElems -= distance(p.first, p.second);
    iumset.erase(p.first, p.second);
    CPPUNIT_ASSERT( nbElems == iumset.size() );
  }

  {
    //More specific test that tries to put many values in the same bucket
    umset iumset;

    size_t i;
    const size_t nbBuckets = iumset.bucket_count();
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

    //CPPUNIT_ASSERT( iumset.bucket_size(targetedBucket) == 21 );

    pair<umset::iterator, umset::iterator> p = iumset.equal_range(targetedBucket);
    CPPUNIT_ASSERT( p.first != p.second );
    CPPUNIT_ASSERT( distance(p.first, p.second) == 3 );
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
          while ((r = rand()) == magic);
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
      CPPUNIT_ASSERT( hum.count(magic) == c );
    }
  }
#  endif
}

#endif


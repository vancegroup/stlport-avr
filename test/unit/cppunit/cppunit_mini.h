/*
 * Copyright (c) 2003, 2004
 * Zdenek Nemec
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

/* $Id$ */

#ifndef _CPPUNITMPFR_H_
#define _CPPUNITMPFR_H_

// Usage: make this part of the project
//#define CPPUNIT_LIB
//  or
//#define CPPUNIT_DUMMY
//  or
//#define CPPUNIT_MINI


///////////////////////////////////////////////////////////
#ifdef CPPUNIT_DUMMY
  #define CPPUNIT_NS CppUnitDummy

  namespace CPPUNIT_NS
  {
    class TestCase
    {};
  }

  #define CPPUNIT_TEST_SUITE(X)
  #define CPPUNIT_TEST(X)
  #define CPPUNIT_TEST_SUITE_END()
  #define CPPUNIT_TEST_SUITE_REGISTRATION(X)
  #define CPPUNIT_ASSERT(X)
  #define CPPUNIT_ASSERT_DOUBLES_EQUAL(X,Y,Z)
  #define CPPUNIT_ASSERT_EQUAL(X,Y)
  #define CPPUNIT_TEST_EXCEPTION(X,Y)
#endif

///////////////////////////////////////////////////////////
#ifdef CPPUNIT_MINI
  #define CPPUNIT_NS CppUnitMini
  
  #include <cstring>


  namespace CPPUNIT_NS
  {
    class Reporter
    {
    public:
      virtual ~Reporter() {}
      virtual void error(char *macroName, char *in_macro, char *in_file, int in_line) {}
      virtual void progress(char *in_className, char *in_testName) {}
      virtual void printSummary() {}
    };

    class TestFixture
    {
    public:
      virtual ~TestFixture() {};

      //! \brief Set up context before running a test.
      virtual void setUp() {};

      //! Clean up after the test run.
      virtual void tearDown() {};
    };

    class TestCase : public TestFixture
    {
    public:
      TestCase() { registerTestCase(this); }
      virtual ~TestCase() {}
      
      static int run(Reporter *in_reporter = 0, const char *in_testName = "");
      int numErrors() { return m_numErrors; }
      static void registerTestCase(TestCase *in_testCase);

      virtual void myRun(const char *in_name) {}

      virtual void error(char *in_macroName, char *in_macro, char *in_file, int in_line)
      {
        m_numErrors++;
        if(m_reporter)
        {
          m_reporter->error(in_macroName, in_macro, in_file, in_line);
        }
      }

      bool equalDoubles(double in_expected, double in_real, double in_maxErr)
      {
        double diff = in_expected - in_real;
        if(diff < 0)
        {
          diff = -diff;
        }
        return diff < in_maxErr;
      }

      virtual void progress(char *in_className, char *in_functionName)
      {
        m_numTests++;
        if(m_reporter)
        {
          m_reporter->progress(in_className, in_functionName);
        }
      }

      bool shouldRunThis(const char *in_desiredTest, const char *in_className, const char *in_functionName)
      {
        if((in_desiredTest) && (in_desiredTest[0] != '\0'))
        {
          const char *ptr = strstr(in_desiredTest, "::");
          if(ptr)
          {
            return (strncmp(in_desiredTest, in_className, strlen(in_className)) == 0)
              && (strncmp(ptr + 2, in_functionName, strlen(in_functionName)) == 0);
          }
          return (strcmp(in_desiredTest, in_className) == 0);
        }
        return true;
      }

    protected:
      static int m_numErrors;
      static int m_numTests;

    private:
      static TestCase *m_root;
      TestCase *m_next;

      static Reporter *m_reporter;
    };
  }

  #define CPPUNIT_TEST_SUITE(X) virtual void myRun(const char *in_name) { char *className = #X;
  #define CPPUNIT_TEST(X) if(shouldRunThis(in_name, className, #X)) {setUp(); progress(className, #X); X(); tearDown();}
  #define CPPUNIT_TEST_EXCEPTION(X,Y) if(shouldRunThis(in_name, className, #X)) {progress(className, #X);}
  #define CPPUNIT_TEST_SUITE_END() }
  #define CPPUNIT_TEST_SUITE_REGISTRATION(X) static X local;

  #define CPPUNIT_ASSERT(X) if(!(X)){ TestCase::error("CPPUNIT_ASSERT", #X, __FILE__, __LINE__); return; }
  #define CPPUNIT_ASSERT_EQUAL(X,Y) if((X)!=(Y)){ TestCase::error("CPPUNIT_ASSERT_EQUAL", #X","#Y, __FILE__, __LINE__); return; }
  #define CPPUNIT_ASSERT_DOUBLES_EQUAL(X,Y,Z) if(!equalDoubles((X),(Y),(Z))){ TestCase::error("CPPUNIT_ASSERT_DOUBLES_EQUAL", #X","#Y","#Z, __FILE__, __LINE__); return; }

#endif

#endif // for header


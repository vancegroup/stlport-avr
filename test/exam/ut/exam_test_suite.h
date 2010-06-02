// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2007
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
 */

#ifndef __exam_test_suite_h
#define __exam_test_suite_h

#include <exam/suite.h>
#include <string>
#include <sstream>

class exam_basic_test
{
  public:
    exam_basic_test() :
        buff(),
        logger( buff ) //,
        // tlogger( buff )
      {  }

    int EXAM_DECL(function_good);
    int EXAM_DECL(function);
    int EXAM_DECL(dep);
    int EXAM_DECL(trace);
    int EXAM_DECL(dep_test_suite);
    int EXAM_DECL(multiple_dep);
    int EXAM_DECL(multiple_dep_complex);
    int EXAM_DECL(perf);
    int EXAM_DECL(dry);
    int EXAM_DECL(single);

  private:
    std::stringstream buff;
    exam::trivial_logger logger;
    // exam::trivial_time_logger tlogger;
    

    static const std::string r0;
    static const std::string r1;
    static const std::string r2;
    static const std::string r3;
    static const std::string r4;
    static const std::string r5;
    static const std::string r6;
    static const std::string r7;
    static const std::string r8;
    static const std::string r9;
    static const std::string r10;
    static const std::string r11;
};

int EXAM_DECL(exam_self_test);

#endif // __exam_test_suite_h

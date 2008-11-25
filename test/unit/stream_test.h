// -*- C++ -*- Time-stamp: <08/11/22 00:40:58 ptr>

/*
 * Copyright (c) 2004-2008
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#ifndef __TEST_STREAM_TEST_H
#define __TEST_STREAM_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class iostream_test
{
  public:
    int EXAM_DECL(manipulators);
    int EXAM_DECL(in_avail);
};

class sstream_test
{
  public:
    int EXAM_DECL(output);
    int EXAM_DECL(input);
    int EXAM_DECL(input_char);
    int EXAM_DECL(io);
    int EXAM_DECL(err);
    int EXAM_DECL(err_long);
    int EXAM_DECL(maxint);
    int EXAM_DECL(init_in);
    int EXAM_DECL(init_out);
    int EXAM_DECL(buf);
    int EXAM_DECL(rdbuf);
    int EXAM_DECL(streambuf_output);
    int EXAM_DECL(seek);
    int EXAM_DECL(seekp);
    int EXAM_DECL(seek_gp);
    int EXAM_DECL(tellp);
    int EXAM_DECL(negative);
};

class fstream_test
{
  public:
    int EXAM_DECL(output);
    int EXAM_DECL(input);
    int EXAM_DECL(input_char);
    int EXAM_DECL(io);
    int EXAM_DECL(err);
    int EXAM_DECL(tellg);
    int EXAM_DECL(tellp);
    int EXAM_DECL(seek);
    int EXAM_DECL(buf);
    int EXAM_DECL(rdbuf);
    int EXAM_DECL(streambuf_output);
    int EXAM_DECL(win32_file_format);
    int EXAM_DECL(null_stream);
    int EXAM_DECL(null_buf);
    int EXAM_DECL(offset);
    int EXAM_DECL(big_file);
    int EXAM_DECL(custom_facet);
};

#endif // __TEST_STREAM_TEST_H

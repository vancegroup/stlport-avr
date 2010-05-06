// -*- C++ -*- Time-stamp: <10/05/06 08:09:58 ptr>

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

#define __FIT_EXAM

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
    int EXAM_DECL(init_in_str);
    int EXAM_DECL(buf);
    int EXAM_DECL(rdbuf);
    int EXAM_DECL(streambuf_output);
    int EXAM_DECL(seek);
    int EXAM_DECL(seekp);
    int EXAM_DECL(seek_gp);
    int EXAM_DECL(tellp);
    int EXAM_DECL(negative);
    int EXAM_DECL(extra0_bug_id_2728232);
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
    int EXAM_DECL(seek_binary);
    int EXAM_DECL(seek_text);
    int EXAM_DECL(seek_wide_stream);
    int EXAM_DECL(rewind);
    int EXAM_DECL(buf);
    int EXAM_DECL(rdbuf);
    int EXAM_DECL(streambuf_output);
    int EXAM_DECL(win32_file_format);
    int EXAM_DECL(null_stream);
    int EXAM_DECL(null_buf);
    int EXAM_DECL(offset);
    int EXAM_DECL(big_file);
    int EXAM_DECL(custom_facet);
    int EXAM_DECL(tell_binary_wce);
};

class strstream_buffer_test
{
  public:
    int EXAM_DECL(read_from_buffer);
};

class strstream_test
{
  public:
    int EXAM_DECL(input);
};

#endif // __TEST_STREAM_TEST_H

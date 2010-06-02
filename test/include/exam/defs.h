/* -*- C -*- Time-stamp: <09/03/16 16:53:50 ptr> */

/*
 * Copyright (c) 2009
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

#ifndef __exam_defs_h
#define __exam_defs_h

#define STRX__(x) #x
#define STR__(x) STRX__(x)

#define HERE __FILE__ ":" STR__(__LINE__)

#endif /* __exam_defs_h */

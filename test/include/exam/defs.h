/* -*- C -*- Time-stamp: <09/03/16 16:53:50 ptr> */

/*
 * Copyright (c) 2009
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License Version 3.0
 */

#ifndef __exam_defs_h
#define __exam_defs_h

#define STRX__(x) #x
#define STR__(x) STRX__(x)

#define HERE __FILE__ ":" STR__(__LINE__)

#endif /* __exam_defs_h */

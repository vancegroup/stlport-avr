/*
 * Copyright (c) 2000, 2001 Alexey Zelkin <phantom@FreeBSD.org>
 * All rights reserved.
 *
 * Copyright (c) 2011 The FreeBSD Foundation
 * All rights reserved.
 * Portions of this software were developed by David Chisnall
 * under sponsorship from the FreeBSD Foundation.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)locale.h	8.1 (Berkeley) 6/2/93
 * $FreeBSD$
 */

#ifndef _LOCALE_H_
#define _LOCALE_H_

struct lconv {
	const char	*decimal_point;
	const char	*thousands_sep;
	const char	*grouping;
	const char	*int_curr_symbol;
	const char	*currency_symbol;
	const char	*mon_decimal_point;
	const char	*mon_thousands_sep;
	const char	*mon_grouping;
	const char	*positive_sign;
	const char	*negative_sign;
	char	int_frac_digits;
	char	frac_digits;
	char	p_cs_precedes;
	char	p_sep_by_space;
	char	n_cs_precedes;
	char	n_sep_by_space;
	char	p_sign_posn;
	char	n_sign_posn;
	char	int_p_cs_precedes;
	char	int_n_cs_precedes;
	char	int_p_sep_by_space;
	char	int_n_sep_by_space;
	char	int_p_sign_posn;
	char	int_n_sign_posn;
};

#define	LC_ALL		0
#define	LC_COLLATE	1
#define	LC_CTYPE	2
#define	LC_MONETARY	3
#define	LC_NUMERIC	4
#define	LC_TIME		5
#define	LC_MESSAGES	6

#define	_LC_LAST	7		/* marks end */
static const char	empty[] = "";
static const char	numempty[] = { CHAR_MAX, '\0'};
inline const lconv * localeconv() {
	static const lconv defaultLocale = {
		".",     	/* decimal_point */
		"",     	/* thousands_sep */
		numempty,	/* grouping */
		empty,		/* int_curr_symbol */
		empty,		/* currency_symbol */
		empty,		/* mon_decimal_point */
		empty,		/* mon_thousands_sep */
		numempty,	/* mon_grouping */
		empty,		/* positive_sign */
		empty,		/* negative_sign */
		CHAR_MAX,	/* int_frac_digits */
		CHAR_MAX,	/* frac_digits */
		CHAR_MAX,	/* p_cs_precedes */
		CHAR_MAX,	/* p_sep_by_space */
		CHAR_MAX,	/* n_cs_precedes */
		CHAR_MAX,	/* n_sep_by_space */
		CHAR_MAX,	/* p_sign_posn */
		CHAR_MAX,	/* n_sign_posn */
		CHAR_MAX,	/* int_p_cs_precedes */
		CHAR_MAX,	/* int_n_cs_precedes */
		CHAR_MAX,	/* int_p_sep_by_space */
		CHAR_MAX,	/* int_n_sep_by_space */
		CHAR_MAX,	/* int_p_sign_posn */
		CHAR_MAX	/* int_n_sign_posn */
	};
	return &defaultLocale;

};


#endif /* _LOCALE_H_ */

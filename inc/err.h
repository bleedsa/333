#ifndef __ERR_H__
#define __ERR_H__

#include <u.h>

extern C *PRS_ERR;

inl C *prs_error(V) {
	return PRS_ERR;
}

V err_deinit(V);
C *err_lex(Pos p, CC *fmt, ...);
V err_prs(Pos p, CC *fmt, ...);

#endif

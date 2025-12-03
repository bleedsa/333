#ifndef __ERR_H__
#define __ERR_H__

#include <u.h>

C *err_lex(Pos p, CC *fmt, ...);
C *err_prs(Pos p, CC *fmt, ...);

#endif

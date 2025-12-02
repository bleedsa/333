#ifndef __U_H__
#define __U_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

/* llvm */
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

/* k */
typedef i32 I;
typedef double F;
typedef char C;
typedef const char CC;
typedef uintptr_t S;
typedef void V;

/* macros */
#define Z(T) (sizeof(T))
#define inl [[clang::always_inline]] inline
#define CASE(c, x...) case c: { x; break; }
#define fatal(f...) {fprintf(stderr, "FATAL: " f);putc('\n', stdout);exit(-1);}
#define println(f...) {printf(f);putc('\n', stdout);}

/* common structs */
typedef struct {
	S line, col;
} Pos;

inl Pos pos_mk(void) {
	return (Pos){1, 1};
}

/* col++ */
inl V pos_inc(Pos *p) {
	p->col++;
}

/* newline */
inl V pos_nl(Pos *p) {
	p->line++, p->col = 1;
}

#endif

#ifndef __STR_H__
#define __STR_H__

#include <string.h>

#include <u.h>
#include <mem.h>

typedef struct {
	S len;
	S cap;
	C *ptr;
} Str;

Str str_mk(void);
V str_append(Str *str, C *x);
V str_free(Str *str);

inl V str_reZ(Str *str, S cap) {
	S L = str->len;
	if (L >= str->cap) {
		str->cap = cap;
		str->ptr = remk(str->ptr, C, cap);
		memset(str->ptr+L, 0, str->cap-L);
	}
}

inl V str_push(Str *str, C x) {
	str_reZ(str, str->cap * 2);
	str->ptr[str->len++] = x;
}

#endif

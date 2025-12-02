#ifndef __MEM_H__
#define __MEM_H__

#define mk(T, z) (T*)malloc(Z(T)*z)
#define remk(P, T, z) realloc(P, Z(T)*z)

#endif

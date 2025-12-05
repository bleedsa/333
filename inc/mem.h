#ifndef __MEM_H__
#define __MEM_H__

#include <stdlib.h>

#define mk(T, z) ((T*)malloc(Z(T)*z))
#define remk(P, T, z) ((T*)realloc(P, Z(T)*z))

#endif

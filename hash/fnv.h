#ifndef __FNV_H__
#define __FNV_H__

#include <stdint.h>

/*a 32 bit Fowler/Noll/Vo hash on buffer*/
uint32_t fnv_32(const void* key, int len);

/*FNV-1a for 32bit hash.*/
uint32_t fnv_32a(const void* key, int len);

/*FNV-1 for 64bit hash*/
uint64_t fnv_64(const void *key, int len);

/*FNV-1a for 64bit hash*/
uint64_t fnv_64a(const void *key, int len);
#endif

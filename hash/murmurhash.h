#ifndef __MURMURHASH_H__
#define __MURMURHASH_H__

#include <sys/types.h>
#include <stdint.h>
/*murmurhash2 32-bit hash*/
uint32_t murmurhash2_32(const void * key, int len);
/*murmurhash2 64-bit hash for 64-bit platforms*/
uint64_t murmurhash2_64A(const void * key, int len);
/*murmurhash2 64-bit hash for 32-bit platforms*/
uint64_t murmurhash2_64B(const void * key, int len);


uint32_t murmurhash3_32(const void *key, size_t len);
#endif


#ifndef __HASH_H__
#define __HASH_H__
/*C99 standard*/
#include <stdint.h>
#include <sys/types.h>
#include "fnv.h"
#include "murmurhash.h"
#include "city.h"

/***********************************************************
*possible hash size:
*       17,           37,           79,        163,       331,
*      673,          1361,         2729,      5417,      10949,
*     21911,        43853,        87719,     175447,     350899,
*    701819,       1403641,      2807303,    5614657,   11229331,
*   22458671,     44917381,     89834777,   179669557, 359339171,
*  718678369,    1437356741,    2147483647,
************************************************************/

/*32 bit magic FNV-1a prime*/
#define FNV_32_PRIME ((FNV32_T)0x01000193)
#define FNV_64_PRIME ((u_int64_t)0x100000001b3ULL)

/*hash data structure*/
typedef struct _BUCKET{
    void           *key;
    void           *value;
    struct _BUCKET   *next;
}BUCKET_T;

/*hash table structure.*/
typedef struct _HASHTABLE{
    BUCKET_T      **buckets;
    unsigned int  hashsize;
    size_t        keysize;
    size_t        valuesize;
    size_t        blocksize;
    BUCKET_T      **freelist;
}HASH_T;

extern HASH_T *new_hash(int hashsize,size_t blocksize,size_t keysize, size_t valuesize);
extern int     hash_add(HASH_T *hash,const void *key, void *value);
extern int     hash_lookup(HASH_T *hash,const void *key, void *value);
extern int     hash_delete_key(HASH_T *hash,const void *key);
extern int     hash_delete_key_value(HASH_T *hash, const void *key, void *value);
extern int     hash_free(HASH_T *hash);

uint32_t fnv_32(const void* key, int len);
#endif

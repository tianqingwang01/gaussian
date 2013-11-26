#include "fnv.h"

#define FNV_32_PRIME ((uint32_t)0x01000193)
#define FNV_64_PRIME ((uint64_t)0x100000001b3ULL)

uint32_t fnv_32(const void* key, int len)
{
    unsigned char *bp = (unsigned char*)key;
    unsigned char *be = bp + len;
    
    uint32_t hval = 0;
    
    while(bp < be){
        hval *= FNV_32_PRIME;
        hval ^= (uint32_t)*bp++;
    }
    
    return hval;
}

uint32_t fnv_32a(const void* key, int len)
{
    unsigned char *bp = (unsigned char*)key;
    unsigned char *be = bp + len;
    
    uint32_t hval = 0;
    
    while(bp < be){
        hval ^= (uint32_t)*bp++;
        hval *= FNV_32_PRIME;
    }
    
    return hval;
}

uint64_t fnv_64(const void *key, int len)
{
    unsigned char *bp = (unsigned char *)key;
    unsigned char *be = bp + len;
    
    uint64_t hval = 0;
    
    while(bp < be){
        hval *= FNV_64_PRIME;
        hval ^= (uint64_t)*bp++;
    }
    
    return hval;
}

uint64_t fnv_64a(const void *key, int len)
{
    unsigned char *bp = (unsigned char *)key;
    unsigned char *be = bp + len;
    
    uint64_t hval = 0;
    
    while(bp < be){
        hval ^= (uint64_t)*bp++;
        hval *= FNV_64_PRIME;
    }
    
    return hval;
}

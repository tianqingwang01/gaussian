#include "murmurhash.h"

#define BIG_CONSTANT(x) (x##LLU)

inline uint32_t getblock32(const uint32_t *p, int i)
{
    return p[i];
}

inline uint64_t getblock64(const uint64_t *p, int i)
{
    return p[i];
}

/*murmurhash2 was written by Austin Appleby, and is placed 
* in public domain. The author hereby disclaims copyright
* to this source code.
*/
uint32_t murmurhash2_32( const void * key, int len)
{
  const uint32_t m = 0x5bd1e995;
  const int r = 24;

  // Initialize the hash to a 'random' value

  uint32_t h = 0 ^ len;

  // Mix 4 bytes at a time into the hash

  const unsigned char * data = (const unsigned char *)key;

  while(len >= 4)
  {
    uint32_t k = *(uint32_t*)data;

    k *= m;
    k ^= k >> r;
    k *= m;

    h *= m;
    h ^= k;

    data += 4;
    len -= 4;
  }

  // Handle the last few bytes of the input array

  switch(len)
  {
  case 3: h ^= data[2] << 16;
  case 2: h ^= data[1] << 8;
  case 1: h ^= data[0];
      h *= m;
  };

  // Do a few final mixes of the hash to ensure the last few
  // bytes are well-incorporated.

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
} 


/*murmurhash2, 64-bit version, by Austin Appleby.
* 64-bit hash for 64-bit platforms
*/
uint64_t murmurhash2_64A ( const void * key, int len)
{
//  const uint64_t m = BIG_CONSTANT(0xc6a4a7935bd1e995);
  const uint64_t m = 0xc6a4a7935bd1e995LLU;
  const int r = 47;

  uint64_t h = 0 ^ (len * m);

  const uint64_t * data = (const uint64_t *)key;
  const uint64_t * end = data + (len/8);

  while(data != end)
  {
    uint64_t k = *data++;

    k *= m; 
    k ^= k >> r; 
    k *= m; 
    
    h ^= k;
    h *= m; 
  }

  const unsigned char * data2 = (const unsigned char*)data;

  switch(len & 7)
  {
  case 7: h ^= uint64_t(data2[6]) << 48;
  case 6: h ^= uint64_t(data2[5]) << 40;
  case 5: h ^= uint64_t(data2[4]) << 32;
  case 4: h ^= uint64_t(data2[3]) << 24;
  case 3: h ^= uint64_t(data2[2]) << 16;
  case 2: h ^= uint64_t(data2[1]) << 8;
  case 1: h ^= uint64_t(data2[0]);
          h *= m;
  };
 
  h ^= h >> r;
  h *= m;
  h ^= h >> r;

  return h;
} 

/*64-bit hash for 32-bit platforms*/
uint64_t murmurhash2_64B( const void * key, int len )
{
  const uint32_t m = 0x5bd1e995;
  const int r = 24;

  uint32_t h1 = uint32_t(0) ^ len;
  uint32_t h2 = uint32_t(0 >> 32);

  const uint32_t * data = (const uint32_t *)key;

  while(len >= 8)
  {
    uint32_t k1 = *data++;
    k1 *= m; k1 ^= k1 >> r; k1 *= m;
    h1 *= m; h1 ^= k1;
    len -= 4;

    uint32_t k2 = *data++;
    k2 *= m; k2 ^= k2 >> r; k2 *= m;
    h2 *= m; h2 ^= k2;
    len -= 4;
  }

  if(len >= 4)
  {
    uint32_t k1 = *data++;
    k1 *= m; k1 ^= k1 >> r; k1 *= m;
    h1 *= m; h1 ^= k1;
    len -= 4;
  }

  switch(len)
  {
  case 3: h2 ^= ((unsigned char*)data)[2] << 16;
  case 2: h2 ^= ((unsigned char*)data)[1] << 8;
  case 1: h2 ^= ((unsigned char*)data)[0];
      h2 *= m;
  };

  h1 ^= h2 >> 18; h1 *= m;
  h2 ^= h1 >> 22; h2 *= m;
  h1 ^= h2 >> 17; h1 *= m;
  h2 ^= h1 >> 19; h2 *= m;

  uint64_t h = h1;

  h = (h << 32) | h2;

  return h;
} 

uint32_t murmurhash3_32(const void *key, size_t len)
{
    int i;
    
    const uint8_t *data = (const uint8_t*)key;
    
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    
    const int nblocks = len/4;
    const uint32_t *blocks = (const uint32_t*)(data + nblocks*4);
    
    uint32_t hval = 0;
    
    for (i=-nblocks; i; i++){
        uint32_t k1 = getblock32(blocks,i);
        
        k1 *= c1;
        k1  = (k1<<15) | (k1>>(32-15));
        k1 *= c2;
        
        hval ^= k1;
        hval  = (hval << 13) | (hval >> (32 - 13));
        hval  = hval*5 + 0xe6546b64;
    }
    
    const uint8_t *tail = (const uint8_t*)(data + nblocks*4);
    uint32_t k1 = 0;
    switch(len & 3){
        case 3: k1 ^= tail[2] << 16;
        case 2: k1 ^= tail[1] << 8;
        case 1: k1 ^= tail[0];
                k1 *= c1;
                k1  = (k1 << 15)|(k1 >> (32 -15));
                k1 *= c2;
                hval ^= k1;
    }
    
    hval ^= len;
    hval ^= hval >> 16;
    hval *= 0x85ebca6b;
    hval ^= hval >> 13;
    hval *= 0xc2b2ae35;
    hval ^= hval >> 16;
    
    return hval;
}



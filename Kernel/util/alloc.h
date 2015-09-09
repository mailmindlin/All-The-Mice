/*
 * alloc.h
 *
 *  Created on: Aug 21, 2015
 *      Author: wfeehery17
 */

#ifndef UTIL_ALLOC_H_
#define UTIL_ALLOC_H_

#include <util/syscfg.h>
#include <util/util.hpp>
#include <cstdint>

#define BLOCK_ALIGN	16
#define ALIGN_MASK	(BLOCK_ALIGN-1)

#define PAGE_MASK	(PAGE_SIZE-1)

#define BLOCK_MAGIC 0x424C4D43
struct BlockHeader_t {
	uint32_t magic PACKED;
	uint32_t size PACKED;
	uint32_t *next PACKED;
	uint32_t padding PACKED;
	uint8_t data[0];
};
struct BlockBucket_t {
	uint32_t size;
	BlockHeader_t* freelist;
};
#define PAGE_MAGIC 0x50474D43
struct FreePage_t {
	uint32_t magic;
	FreePage_t* next;
};
struct PageBucket_t {
	uint32_t count;
	uint32_t maxCount;
	FreePage_t* freeList;
};

static uint8_t* nextBlock;
static uint8_t* blockLimit;

static uint8_t* nextPage;
static uint8_t* pageLimit;





#endif /* UTIL_ALLOC_H_ */

/**
 * memtypes.h
 *
 *  Created on: Sep 25, 2015
 *      Author: mailmindlin
 */

#ifndef IO_MEMORY_MEMTYPES_HPP_
#define IO_MEMORY_MEMTYPES_HPP_

#include <cstdint>

namespace MemoryMap {

typedef const uint32_t				memconst_t;
typedef volatile uint32_t* const	memptr_t;
typedef volatile uint32_t			REG32RW;
typedef volatile const uint32_t		REG32RO;
typedef volatile uint32_t			REG32WO;
typedef const uint32_t				RESRV32;

}




#endif /* IO_MEMORY_MEMTYPES_HPP_ */

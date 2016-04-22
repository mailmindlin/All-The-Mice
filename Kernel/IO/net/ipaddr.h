#ifndef _IO_NET_IPADDR_H_
#define _IO_NET_IPADDR_H_

#include <stdint.h>

union ip4addr_t {
	uint32_t raw;
	uint8_t[4] bytes;
};
union ip6addr_t {
	
};
#endif
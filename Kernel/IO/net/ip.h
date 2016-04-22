#ifndef _IO_NET_IP_H_
#define _IO_NET_IP_H_
#include <stdint.h>

namespace net {
	enum ipProtocols {
		HOPOPT	= 0,
		ICMP	= 1,
		IGMP	= 2,
		GGP		= 3,
		IPnIP	= 4,
		ST,
		TCP,
		CBT,
		EGP,
		IGP,
		BBN_RCC_MON,
		NVP_II,
		PUP,
		ARGUS,
		EMCON,
		XNET,
		CHAOS,
		UDP,
		MUX,
		DCN-MEAS,
		HMP,
		PRM,
		XNS-IDP,
		TRUNK_1,
		TRUNK_2,
		LEAF_1,
		LEAF_2,
		//TODO populate
	}
}
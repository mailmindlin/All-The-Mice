#include <stdint.h>
#include "ip.h"
#include "ipaddr.h"
namespace net {
	struct UDPHeader {
		uint16_t src_port : 16;
		uint16_t dst_port : 16;
		uint16_t length   : 16;
		uint16_t checksum : 16;
	}
	struct UDP4PseudoHeader {
		ip4addr_t src_ip;
		ip4addr_t dst_ip;
		uint32_t packet_len;
		uint8_t zeroes;
		uint8_t protocol;
		uint16_t packet_len;
		UDPHeader header;
	}
	struct UDP6PacketHeader {
		ip6addr_t src_ip;
		ip6addr_t dst_ip;
		uint32_t packet_len;
		uint8_t zeroes[3];
		uint8_t next_header;
		UDPHeader header;
	}
	class UDPPacket {
		public:
			UDPPacket(uint8_t* buf, size_t len);
			UDPPacket(size_t payloadSize);
			size_t getPayloadSize() const;
			UDPHeader& getHeader();
			uint16_t getChecksum();
			~UDPPacket();
		protected:
			const size_t payload_length;
			uint8_t* payload;
			uint16_t src_port;
			uint16_t dst_port;
			UDP6PseudoHeader& getPseudoHeader4(ip4addr_t src_ip, ip4addr_t dst_ip);
			UDP6PseudoHeader& getPseudoHeader6(ip6addr_t src_ip, ip6addr_t dst_ip);
	}
}
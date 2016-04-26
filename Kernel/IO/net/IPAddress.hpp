#ifndef _IO_NET_IPADDRESS_HPP_
#define _IO_NET_IPADDRESS_HPP_
namespace net {
	class IPAddress {
		public:
			IPAddress(uint32_t addr);
			IPAddress(uint8_t* addr);
			IPAddress(const IPAddress& addr);
			~IPAddress();
		protected:
		
	}
}
#endif
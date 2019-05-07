#include <stdint.h>

#define ECHO_REPLY 0
#define ECHO_REQUEST 8

struct icmp{
  uint8_t type;
  uint8_t code;
  uint16_t checksum;
  unsigned char rest_of_header[];
}__attribute__((packed));

extern struct icmp *icmp_pkt;

void parse_icmp();

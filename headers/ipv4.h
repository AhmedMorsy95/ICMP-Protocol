#include <stdint.h>
#define TCP 6
#define ICMP 1

struct ipv4{
  /// the normal order is version then ihl but we reordered them
  /// because we are considering the host to be little endian
  /// using ntohs would only solve the problem for 2 bytes but not a single byte
  /// u can see an example on the issue here explained in one of the answers
  // https://stackoverflow.com/questions/6043483/why-bit-endianness-is-an-issue-in-bitfields
  uint8_t ihl : 4;
  uint8_t version : 4; // 4 bits only
  uint8_t dscp_ecn; // 4 bits only
  uint16_t total_length;
  uint16_t id;
  uint16_t flags_fragment_offset;
  uint8_t ttl;
  uint8_t protocol;
  uint16_t header_checksum;
  uint32_t sip;
  uint32_t dip;
  unsigned char options[];
}__attribute__((packed));

extern struct ipv4 * ipv4_pkt;

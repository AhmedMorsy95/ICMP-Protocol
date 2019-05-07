#include "../headers/icmp.h"
#include "../headers/ipv4.h"
#include "../headers/tap_tun.h"
#include "../headers/ethernet.h"
#include <string.h>
#include <inttypes.h>

#define ECHO_REQUEST_LEN
struct icmp* icmp_pkt;

void parse_icmp(){
    icmp_pkt = (struct icmp*) ipv4_pkt -> options;
    if(icmp_pkt -> type == ECHO_REQUEST){
      icmp_pkt -> type = ECHO_REPLY;
      checksum();
      modify_ipv4_packet();
      modify_ethernet_packet();
      icmp_echo_reply();
    }
}

void checksum(){
    //length of icmp payload 84 - 20 - 8 = 5
    icmp_pkt->checksum = 0;

    uint32_t sum = 0;
    uint16_t *start = icmp_pkt;
    int length = (int)ntohs(ipv4_pkt->total_length) - 4*(int)ipv4_pkt->ihl;
    //printf("length of the icmp packets is %d\n\n",length);

    while (length > 1) {
      sum += *start;
      start++;
      length -=2;
    }
    if(length){
      sum += *(uint8_t*)start;
    }
    while(sum >> 16){
      sum = (sum & 0xffff) + (sum >> 16);
    }
    sum = ~sum;
    sum &= 0xffff;

    icmp_pkt -> checksum = (uint16_t)sum;
   // printf("checksum is %d\n",sum);


}
void modify_ethernet_packet(){
  ethernet_packet->ethertype = htons(ETH_P_IP);
  memcpy(ethernet_packet->dmac, ethernet_packet->smac, 6);
  memset(ethernet_packet->smac, 0, 6);
}

void modify_ipv4_packet(){

  uint32_t tmp = ipv4_pkt -> sip;
  ipv4_pkt -> sip = ipv4_pkt -> dip;
  ipv4_pkt -> dip = tmp;
  ipv4_pkt -> header_checksum = 0;

  uint32_t sum = 0;
  uint16_t *start = ipv4_pkt;
  int length = 4*(int)ipv4_pkt->ihl;
  //printf("length of the icmp packets is %d\n\n",length);

  while (length > 1) {
    sum += *start;
    start++;
    length -=2;
  }
  if(length){
    sum += *(uint8_t*)start;
  }
  while(sum >> 16){
    sum = (sum & 0xffff) + (sum >> 16);
  }
  sum = ~sum;
  sum &= 0xffff;

  ipv4_pkt -> header_checksum = (uint16_t)sum;
}

void icmp_echo_reply(){
   // write into tap
   int bytes = tap_write(ethernet_packet,ethernet_len);
  // printf("%d  %d written into tap\n\n",ethernet_len,bytes);
}

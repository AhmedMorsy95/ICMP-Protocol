#include "../headers/arp.h"
#include "../headers/ipv4.h"
#include "../headers/ethernet.h"
#include "../headers/icmp.h"

struct ipv4* ipv4_pkt;

void parse_ipv4(){
  ipv4_pkt = (struct ipv4*) ethernet_packet -> payload;
  // printf("version is %d, protocol is %d, dip is ",ipv4_pkt->version,ipv4_pkt->protocol);
  // print_ipv4_address(ipv4_pkt->dip);

  if(ipv4_pkt -> protocol == TCP){
    // printf("This is a TCP packet\n");
  }
  else if(ipv4_pkt -> protocol == ICMP){
    // printf("This is an ICMP packet\n");
    parse_icmp();
  }
}

#include "ft_malcolm.h"

void  display_request_info(char *ether_frame, arp_hdr *arphdr) {
  printf ("\nEthernet frame header:\n");
  printf ("Destination MAC (this node): ");
  for (int i=0; i<5; i++) {
    printf ("%02x:", ether_frame[i]);
  }
  printf ("%02x\n", ether_frame[5]);
  printf ("Source MAC: ");
  for (int i=0; i<5; i++) {
    printf ("%02x:", ether_frame[i+6]);
  }
  printf ("%02x\n", ether_frame[11]);
  printf ("Ethernet type code (2054 = ARP): %u\n", ((ether_frame[12]) << 8) + ether_frame[13]);
  printf ("\nEthernet data (ARP header):\n");
  printf ("Hardware type (1 = ethernet (10 Mb)): %u\n", ntohs (arphdr->htype));
  printf ("Protocol type (2048 for IPv4 addresses): %u\n", ntohs (arphdr->ptype));
  printf ("Hardware (MAC) address length (bytes): %u\n", arphdr->hlen);
  printf ("Protocol (IPv4) address length (bytes): %u\n", arphdr->plen);
  printf ("Opcode (2 = ARP reply): %u\n", ntohs (arphdr->opcode));
  printf ("Sender hardware (MAC) address: ");
  for (int i=0; i<5; i++) {
    printf ("%02x:", arphdr->sender_mac[i]);
  }
  printf ("%02x\n", arphdr->sender_mac[5]);
  printf ("Sender protocol (IPv4) address: %u.%u.%u.%u\n",
    arphdr->sender_ip[0], arphdr->sender_ip[1], arphdr->sender_ip[2], arphdr->sender_ip[3]);
  printf ("Target (this node) hardware (MAC) address: ");
  for (int i=0; i<5; i++) {
    printf ("%02x:", arphdr->target_mac[i]);
  }
  printf ("%02x\n", arphdr->target_mac[5]);
  printf ("Target (this node) protocol (IPv4) address: %u.%u.%u.%u\n",
    arphdr->target_ip[0], arphdr->target_ip[1], arphdr->target_ip[2], arphdr->target_ip[3]);
}

void  display_addr(int len, uint8_t *addr, char *mess, int8_t hex) {
  dprintf(1, mess);
  if (hex == 1) {
    for (int i = 0; i < len - 1; i++)
      dprintf(1, "%.2hhx:", addr[i]);
    dprintf(1, "%.2hhx\n", addr[len - 1]);
  }
  else {
    for (int i = 0; i < len - 1; i++)
      dprintf(1, "%.2hhu:", addr[i]);
    dprintf(1, "%.2hhu\n", addr[len - 1]);
  }
}

void  display_device_info(struct sockaddr_ll device) {
  dprintf(1, "device.sll_family = %d\n", device.sll_family);
  dprintf(1, "device.sll_protocol = %d\n", device.sll_protocol);
  dprintf(1, "device.sll_ifindex = %d\n", device.sll_ifindex);
  dprintf(1, "device.sll_hatype = %d\n", device.sll_hatype);
  dprintf(1, "device.sll_pkttype = %d\n", device.sll_pkttype);
  dprintf(1, "device.sll_halen = %d\n", device.sll_halen);
  dprintf(1, "device.sll_addr = ");
  for (int i = 0; i < 5; i++)
    dprintf(1, "%.2hhx:", device.sll_addr[i]);
  dprintf(1, "%.2hhx\n", device.sll_addr[5]);
}

void  display_arphdr_info(arp_hdr arphdr) {
  dprintf(1, "arphdr.htype = %hu\n", arphdr.htype);
  dprintf(1, "arphdr.hlen = %hhu\n", arphdr.hlen);
  dprintf(1, "arphdr.opcode = %hu\n", arphdr.opcode);
  dprintf(1, "arphdr.plen = %hhu\n", arphdr.plen);
  dprintf(1, "arphdr.ptype = %hu\n", arphdr.ptype);
  display_addr(4, arphdr.sender_ip, "arphdr.sender_ip = ", 0);
  display_addr(6, arphdr.sender_mac, "arphdr.sender_mac = ", 1);
  display_addr(4, arphdr.target_ip, "arphdr.target_ip = ", 0);
  display_addr(6, arphdr.target_mac, "arphdr.target_mac = ", 1);
}
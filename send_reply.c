#include "ft_malcolm.h"

#define ETH_HDRLEN 14
#define FRAME_LEN 42

void  close_and_free(int sd, uint8_t *ether_frame) {
  close (sd);
  free (ether_frame);
  ether_frame = NULL;
}

void  allocation(uint8_t **ether_frame, arp_hdr *arphdr) {
  *ether_frame =  (uint8_t *)allocate_ustrmem (IP_MAXPACKET, 1);
  memcpy ((*ether_frame), arphdr->target_mac, 6 * sizeof (uint8_t));
  memcpy ((*ether_frame) + 6, arphdr->sender_mac, 6 * sizeof (uint8_t));
  (*ether_frame)[12] = 0x08;
  (*ether_frame)[13] = 0x06;
  memcpy ((*ether_frame) + ETH_HDRLEN, arphdr, 28 * sizeof (uint8_t));
}

void init_struct_arphdr(arp_hdr *arphdr, t_addr *addresses) {
  in_addr_t tmp;

  arphdr->htype = htons (1);
  arphdr->ptype = htons (ETH_P_IP);
  arphdr->hlen = 6;
  arphdr->plen = 4;
  arphdr->opcode = htons (ARPOP_REPLY);
  tmp = inet_addr(addresses->target_ip);
  memcpy (arphdr->target_ip, &tmp, 4 * sizeof (uint8_t));
  sscanf(addresses->target_mac_address, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
    &arphdr->target_mac[0], &arphdr->target_mac[1], &arphdr->target_mac[2], 
    &arphdr->target_mac[3], &arphdr->target_mac[4], &arphdr->target_mac[5]);
  sscanf(addresses->source_mac_address, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
    &arphdr->sender_mac[0], &arphdr->sender_mac[1], &arphdr->sender_mac[2], 
    &arphdr->sender_mac[3], &arphdr->sender_mac[4], &arphdr->sender_mac[5]);
  tmp = inet_addr(addresses->source_ip);
  memcpy (arphdr->sender_ip, &tmp, 4 * sizeof (uint8_t));
}

int if_name_to_index(char *interface) {
  struct ifaddrs *ifap = NULL, *backup = NULL;
  int index = 0;

  if (getifaddrs(&ifap) == -1) {
    // ifaddrs(ifap);
    perror("getifaddrs");
    exit(EXIT_FAILURE);
  }
  backup = ifap;

  while(ifap->ifa_next) {
    index++;
    if (strncmp(ifap->ifa_name, interface, strlen(ifap->ifa_name)) == 0) {
      freeifaddrs(backup);
      return (index);
    }
    ifap = ifap->ifa_next;
  }
  freeifaddrs(backup);
  return (-1);
}

void init_struct_sockaddr_ll(struct sockaddr_ll *device) {
  memset (device, 0, sizeof (*device));
  // sscanf(addresses.source_mac_address, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
  //   &device->sll_addr[0], &device->sll_addr[1], &device->sll_addr[2], &device->sll_addr[3], 
  //   &device->sll_addr[4], &device->sll_addr[5]);
  device->sll_hatype = 0x01;
  device->sll_protocol = htons(0x0800);
  device->sll_family = AF_PACKET;
  device->sll_halen = 6;
  if ((device->sll_ifindex = if_name_to_index ("eth0")) == 0) // ne pas oublier de modifier car func interdite
    exit (EXIT_FAILURE);
}

void send_reply(int sd, t_addr *addresses){
  arp_hdr arphdr;
  uint8_t *ether_frame;
  struct sockaddr_ll device;
  int bytes_sended = -1;
  
  init_struct_sockaddr_ll(&device);
  init_struct_arphdr(&arphdr, addresses);
  allocation(&ether_frame, &arphdr);

  // display_device_info(device);
  // display_arphdr_info(arphdr);
  bytes_sended = sendto (sd, ether_frame, FRAME_LEN, 0, (struct sockaddr *) &device, sizeof (device));
  if (bytes_sended <= 0) {
    perror("Error: ");
    close_and_free(sd, ether_frame);
    exit (1);
  }
  else {
    dprintf(1, "ARP Reply of %d bytes sended to %s\n", bytes_sended, addresses->source_mac_address);
  }
  close_and_free(sd, ether_frame);
}


#ifndef FT_MALCOLM
#define FT_MALCOLM
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>      
#include <net/if.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>


typedef struct s_addresses {
    char *source_ip;
    char *source_mac_address;
    char *target_ip;
    char *target_mac_address;
} t_addr;

typedef struct _arp_hdr arp_hdr;
struct _arp_hdr {
  uint16_t htype;
  uint16_t ptype;
  uint8_t hlen;
  uint8_t plen;
  uint16_t opcode;
  uint8_t sender_mac[6];
  uint8_t sender_ip[4];
  uint8_t target_mac[6];
  uint8_t target_ip[4];
};

void  free_addresses(t_addr **addresses);
int error_check (int ac, char **av);

//receiv_request.c
void received_request(char *target, char *source, int *sd);

//send_reply.c
void send_reply(int sd, t_addr *addresses);

//utils.c
void fill_addresses_struct(t_addr **addresses, char **argv);
void *allocate_ustrmem (unsigned int len, ssize_t size);
// void fill_arp_hdr(arp_hdr *reply);

// utils_display.c
void display_request_info(char *ether_frame, arp_hdr *arphdr);
void display_addr(int len, uint8_t *addr, char *mess, int8_t hex);
void display_device_info(struct sockaddr_ll device);
void display_arphdr_info(arp_hdr arphdr);

#endif
#include "ft_malcolm.h"

void  free_addresses(t_addr **addresses) {

  (*addresses)->source_ip = NULL;
  (*addresses)->source_mac_address = NULL;
  (*addresses)->target_ip = NULL;
  (*addresses)->target_mac_address = NULL;
  free(*addresses); (*addresses) = NULL;
}

int main(int argc, char **argv) {
  int sd;
  t_addr *addresses;
  
  if (argc != 5) return (1);
  if (error_check(argc, argv) == 1) return (1);

  while (1) {
    fill_addresses_struct(&addresses, argv);
    received_request(addresses->target_ip, addresses->source_ip, &sd);
    send_reply(sd, addresses);
    free_addresses(&addresses);
  }
  return (0);
}
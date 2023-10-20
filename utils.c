#include "ft_malcolm.h"



void fill_addresses_struct(t_addr **addresses, char **argv) {
    (*addresses) = malloc(sizeof(t_addr));
    if (!*addresses)
        exit(1);
    (*addresses)->source_ip = argv[1];
    (*addresses)->source_mac_address = argv[2];
    (*addresses)->target_ip = argv[3];
    (*addresses)->target_mac_address = argv[4];
    if (!(*addresses)->source_ip || !(*addresses)->source_mac_address || \
    !(*addresses)->target_ip || !(*addresses)->target_mac_address)
        exit(1);
}

void *allocate_ustrmem (unsigned int len, ssize_t size) {
    char *tmp;

    tmp = (char *)calloc(len, size);
    if (tmp == NULL) {
        fprintf (stderr, "ERROR: memory allocation.\n");
        exit (1);
    }
    return (tmp);
}

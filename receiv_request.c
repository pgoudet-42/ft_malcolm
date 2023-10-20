#include "ft_malcolm.h"

void init_addr_struc(struct sockaddr_in *addr, t_addr *addresses) {
  addr->sin_family = AF_INET;
  addr->sin_port = htons(0);
  addr->sin_addr.s_addr = inet_addr(addresses->source_ip);
}

void    reset_addr(struct sockaddr_in **addr) {
    if (*addr != NULL) {
        free(*addr);
        *addr = NULL;
    }
    *addr = (struct sockaddr_in *)allocate_ustrmem(1, sizeof(struct addr_in *));
    (*addr)->sin_port = 0;
    (*addr)->sin_addr.s_addr = 0;
    (*addr)->sin_family = AF_INET;
}

socklen_t reset(char **ether_frame, arp_hdr **arphdr, struct sockaddr_in **from) {
    if (*ether_frame != NULL) {
        free(*ether_frame);
        *ether_frame = NULL;
    }
    *ether_frame = (char *)allocate_ustrmem(IP_MAXPACKET, 1);
    *arphdr = (arp_hdr *)(*ether_frame + 6 + 6 + 2);
    reset_addr(from);
    return (sizeof(t_addr *));
}

void received_request(char *target, char *source, int *sd) {
    int status = 0;
    socklen_t len = 0;
    arp_hdr *arphdr = NULL;
    char *ether_frame = NULL;
    struct sockaddr_in *from = NULL;

    if ((*sd = socket (PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {perror(""); exit (1);}

    do {
        len = reset(&ether_frame, &arphdr, &from);
        while (((((ether_frame[12]) << 8) + ether_frame[13]) != ETH_P_ARP) && (ntohs(arphdr->opcode) != ARPOP_REPLY)) {
            if ((status = recvfrom(*sd, ether_frame, IP_MAXPACKET, 0, (struct sockaddr *)from, &len)) < 0) {
                if (from) {
                    free(from);
                    from = NULL;
                }
                perror ("recv() failed:");
                exit (1);
            }
       }
        // display_arphdr_info(*arphdr);
    }
    while (*(uint32_t *)&(arphdr->sender_ip[0]) != inet_addr(target) || *(uint32_t *)&(arphdr->target_ip[0]) != inet_addr(source));
    free(from);
    from = NULL;
    free(ether_frame);
    ether_frame = NULL;
}
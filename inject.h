#ifndef _INJECT_H_
#define _INJECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include "llist.h"

struct radiotap_header {
    uint8_t it_version;
    uint8_t it_pad;
    uint16_t it_len;      
    uint32_t it_present;
    uint16_t rate;
    uint16_t tx_flags;
} __attribute__((__packed__));

struct mgmt_frame{
    struct radiotap_header rt_header;
    uint16_t frame_control;
    uint16_t duration;
    uint8_t dest_addr[6];
    uint8_t src_addr[6];
    uint8_t bssid[6];
    uint16_t seq_ctrl;
    uint16_t reason;
} __attribute__((__packed__));

struct llist frame_storage(struct llist* info);

void inject(struct llist* storage, int sock, struct sockaddr_ll* dev, int density, int delay);

void switch_side(struct mgmt_frame* deau);

void spam_frame(int sock, struct sockaddr_ll* dev, void* frame, int times);

#endif
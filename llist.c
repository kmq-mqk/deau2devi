#include "llist.h"

struct llist create_ls(){
    struct llist ls;
    ls.head_node = NULL;
    ls.tail_node = NULL;
    return ls;
}

struct node* create_node(void* val, size_t size){
    struct node* node = (struct node*)malloc(sizeof(struct node));

    if(node != NULL){
        node->data = malloc(size);
        if(node->data == NULL){

            free(node);
            return NULL;
        }

        memcpy(node->data, val, size);

        node->next_node = NULL;
        return node;
    }
}

void add_head(struct llist* ls, void* val, size_t size){
    struct node* node = create_node(val, size);
    if(node == NULL){
        fprintf(stderr, "Error! Don't have enough memory");
        exit(EXIT_FAILURE);
    }
    if(ls->head_node == NULL){
        ls->head_node = node;
        ls->tail_node = node;
        return;
    }
    
    node->next_node = ls->head_node;
    ls->head_node = node;
}

void add_tail(struct llist* ls, void* val, size_t size){
    if(ls->head_node == NULL){
        add_head(ls, val, size);
        return;
    }

    struct node* node = create_node(val, size);
    if(node == NULL){
        fprintf(stderr, "Error! Don't have enough memory");
        exit(EXIT_FAILURE);
    }

    ls->tail_node->next_node = node;
    ls->tail_node = node;
}

void clr_ls(struct llist* ls){
    while(ls->head_node != NULL){
        struct node* tmp = ls->head_node;
        ls->head_node = ls->head_node->next_node;
        free(tmp->data);
        free(tmp);
    }
    ls->tail_node = NULL;
}

void print_ls(struct llist* ls, int options){
    for(struct node* cur = ls->head_node; cur != NULL; cur = cur->next_node){
        if(options == 0){
            printf("%s -> ", (char*)cur->data);
        }
        if(options == 1){
            printf("%d -> ", (int*)cur->data);
        }
    }
}
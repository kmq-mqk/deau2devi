#ifndef _LLIST_H_
#define _LLIST_H_

/*
Linked List will be used to store 
-MAC addresses from input (unsigned char*)
-Frames to be injected (struct of unsigned char*)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct node{
    void* data;
    struct node* next_node;
};

struct llist{
    struct node* head_node;
    struct node* tail_node;
};

struct llist create_ls();
struct node* create_node(void* val, size_t size);

void add_head(struct llist* ls, void* val, size_t size);
void add_tail(struct llist* ls, void* val, size_t size);

void print_ls(struct llist* ls, int options);
void clr_ls(struct llist* ls);

#endif
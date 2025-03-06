#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <net/if.h>
#include "llist.h"

struct llist* categorize(int argc, char** argv, char* interface, int* density, int* delay);
int conv_target(struct llist* ls, int pos, int argc, char** argv, char flag);
int conv_ap(struct llist* ls, int pos, int argc, char** argv);
int conv_if(char* interface, int pos, int argc, char** argv);
void conv_dens_delay(int* density, int* delay, int pos, int argc, char** argv);

// below will be for adjustative features (maybe later)
/*
-density
-delay
-pick interface
*/

#endif
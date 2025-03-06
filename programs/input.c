#include "input.h"

/*
FLAGS:
-a : send frame to broadcast (all devices connecting to AP)
[flag -a doesn't need additional MAc addr]
-t : target (MAC addr)
SHOULD CHOOSE ONE BETWEEN -a and -t
-b : AP (MAC addr)
-i : interfaces (e.g.: wlan0mon)
--density : number of frames per burst [optional]
--delay : rest time after a burst (milisecond) [optional]
*/

struct llist* categorize(int argc, char** argv, char* interface, int* density, int* delay){
    struct llist* ret = (struct llist*)malloc(sizeof(struct llist) * 3);
    ret[0] = create_ls();
    ret[1] = create_ls();

    /*
    ret[0] contains target MAC addr(s)
    ret[1] contains AP MAC addr(s)
    */

    int flag_check = 1;

    if(!ret){
        fprintf(stderr, "Error! Don't have enough memory\n");
        exit(EXIT_FAILURE);
    }
        
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            if(argv[i][1] == 't' || argv[i][1] == 'a'){
                flag_check *= 2;
                i = conv_target(&ret[0], i, argc, argv, argv[i][1]);
            }
            else if(argv[i][1] == 'b'){
                flag_check *= 3;
                i = conv_ap(&ret[1], i, argc, argv);
            }
            else if(argv[i][1] == 'i'){
                flag_check *= 5;
                i = conv_if(interface, i, argc, argv);
            }
            else{
                conv_dens_delay(density, delay, i, argc, argv);
                i++;
            }
        }
    }
    if(flag_check % (2 * 3 * 5)){
        fprintf(stderr, "Error! Need informations for all 3 flags");
    }
    
    return ret;
}

int conv_target(struct llist* ls, int pos, int argc, char** argv, char flag){
    if(flag == 't'){
        if(ls->head_node == NULL){
            if(pos == argc - 1 || argv[pos + 1][0] == '-'){
                fprintf(stderr, "Error! Lack information for flag '-t'\n");
                exit(EXIT_FAILURE);
            }
            for(int i = pos + 1; i < argc; i++){
                if(argv[i][0] == '-')
                    return i - 1;

                add_tail(ls, argv[i], strlen(argv[i]) * sizeof(char));
            }
        }
    }
    else{
        if(ls->head_node)
            clr_ls(ls);
        add_head(ls, "FF:FF:FF:FF:FF:FF", strlen("FF:FF:FF:FF:FF:FF") * sizeof(char));
    }
}

int conv_ap(struct llist* ls, int pos, int argc, char** argv){
    if(pos == argc - 1 || argv[pos + 1][0] == '-'){
        fprintf(stderr, "Error! Lack information for flag '-b'\n");
        exit(EXIT_FAILURE);
    }
    for(int i = pos + 1; i < argc; i++){
        if(argv[i][0] == '-')
            return i - 1;

        add_tail(ls, argv[i], strlen(argv[i]) * sizeof(char));
    }
}

int conv_if(char* interface, int pos, int argc, char** argv){
    if(pos == argc - 1 || argv[pos + 1][0] == '-'){
        fprintf(stderr, "Error! Lack information for flag '-i'\n");
        exit(EXIT_FAILURE);
    }
    if(pos + 2 < argc && argv[pos + 2][0] != '-'){
        fprintf(stderr, "Error! Only choose one interface\n");
        exit(EXIT_FAILURE);
    }
    strncpy(interface, argv[pos + 1], IFNAMSIZ - 1);

    return pos + 1;
}

int str2int(char* str){
    int ret = 0;
    for(int i=0; i<strlen(str); i++){
        if(str[i] < '0' || str[i] > '9'){
            fprintf(stderr, "Error! Not an expected number value\n");
            exit(EXIT_FAILURE);
        }
        ret *= 10;
        ret += str[i] - '0';
    }
    return ret;
}
void conv_dens_delay(int* density, int* delay, int pos, int argc, char** argv){
    if(!strcmp(argv[pos], "--density")){
        if(pos == argc - 1 || argv[pos + 1][0] == '-'){
            fprintf(stderr, "Error! Lack information for flag '--density'\n");
            exit(EXIT_FAILURE);
        }
        if(pos + 2 < argc && argv[pos + 2][0] != '-'){
            fprintf(stderr, "Error! Only choose one value\n");
            exit(EXIT_FAILURE);
        }
        *density = str2int(argv[pos + 1]);
    }
    if(!strcmp(argv[pos], "--delay")){
        if(pos == argc - 1 || argv[pos + 1][0] == '-'){
            fprintf(stderr, "Error! Lack information for flag '--delay'\n");
            exit(EXIT_FAILURE);
        }
        if(pos + 2 < argc && argv[pos + 2][0] != '-'){
            fprintf(stderr, "Error! Only choose one value\n");
            exit(EXIT_FAILURE);
        }
        *delay = str2int(argv[pos + 1]) * 1000;
    }
}
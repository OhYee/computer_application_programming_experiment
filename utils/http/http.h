#include "../boolean/boolean.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct _HTML HTML;

struct _HTML {
    char *host;
    int   length;
    char *body;
};

boolean get_page(char *ip, uint16_t port, char *reponse, int reponse_size);
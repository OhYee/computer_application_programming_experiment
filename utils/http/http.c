#include "http.h"

#define MAX_REQUEST_LENGTH 2048

int get_page(char *prefix, char *url, char *ip, uint16_t port, char *reponse,
             int reponse_size) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);

    int con = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (con != 0) {
        return F;
    }

    char request[MAX_REQUEST_LENGTH] = "\0";
    strcat(request, "GET ");
    strcat(request, prefix);
    strcat(request, url);
    strcat(request, " HTTP/1.1\r\n");
    strcat(request, "Host:");
    strcat(request, ip);
    strcat(request, "\r\nConnection:Keep-alive\r\n\r\n");

    write(sock, request, sizeof(request));

    int read_length = 0;
    while (1) {
        int ret =
            read(sock, reponse + read_length, reponse_size - read_length - 1);
        if (ret <= 0) {
            break;
        }
        read_length += ret;
    }

    close(sock);
    return read_length;
}
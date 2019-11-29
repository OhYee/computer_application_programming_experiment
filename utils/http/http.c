#include "http.h"

#define MAX_REQUEST_LENGTH 2048

boolean get_page(char *ip, uint16_t port, char *reponse, int reponse_size) {
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
    strcat(request, "GET / HTTP/1.1\r\n");
    strcat(request, "Host:");
    strcat(request, ip);
    strcat(request, "\r\nConnection:Close\r\n\r\n");

    send(sock, request, sizeof(request), 0);

    recv(sock, reponse, reponse_size - 1, 0);

    close(sock);
    return T;
}
#include "pu_socket.h"

//#include <sys/socket.h>// socket()
#include <netdb.h>// IPPROTO_TCP, IPPROTO_UDP
#include <netinet/in.h>// htons(), struct sockaddr_in
#include <string.h>// memset(), memcpy()
#include <unistd.h>// close()

pu_socket_err_t pu_socket_open(pu_socket_info_o *info) {
    int sock;
    if(info->fam == PU_SOCKET_FAM_IP) {
        sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    } else if(info->fam == PU_SOCKET_FAM_IPV6) {
        //sock = socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);
        return -11;
    } else {
        return -10;
    }
    if(sock < 0) return -1;
    info->sock = sock;
    return 0;
}

pu_socket_err_t pu_socket_bind(pu_socket_info_o *info, pu_socket_addr_o *addr) {
    int b;    
    if(info->fam == PU_SOCKET_FAM_IP) {
        struct sockaddr_in sin;
        memset((void *)&sin, 0x00, sizeof(struct sockaddr_in));
        sin.sin_family = AF_INET;
        memcpy((void *)&sin.sin_port , (void *)&addr->port , 2);
        memcpy((void *)&sin.sin_addr.s_addr , (void *)&addr->addr , 4);
        b = bind(info->sock, (struct sockaddr *)&sin, sizeof(struct sockaddr));
    } else if(info->fam == PU_SOCKET_FAM_IPV6) {
        return -11;
    } else {
        return -10;
    }
    if(b < 0) return -1;
    return 0;
}

pu_socket_err_t pu_socket_read(pu_socket_info_o *info, char *data, pu_socket_len_t length, pu_socket_addr_o *addr) {
    int n;
    socklen_t cin_length;
    if(info->fam == PU_SOCKET_FAM_IP) {
        struct sockaddr_in cin;
        memset((void *)&cin, 0x00, sizeof(struct sockaddr_in));
        cin_length = sizeof(struct sockaddr);
        n = recvfrom(info->sock, (void *)data, length, 0, (struct sockaddr *)&cin, &cin_length);
        if(cin.sin_family != PU_SOCKET_FAM_IP) return -2;
        memcpy((void *)&addr->port , (void *)&cin.sin_port , 2);
        memcpy((void *)&addr->addr , (void *)&cin.sin_addr.s_addr , 4);
    } else if(info->fam == PU_SOCKET_FAM_IPV6) {
        return -11;
    } else {
        return -10;
    }
    if(n < 0) return -1;
    // один байт избыточный!!!
    addr->pkg_length = n - 1;
    //addr->pkg_length = n;
    // .......................
    return 0;    
}

pu_socket_err_t pu_socket_write(pu_socket_info_o *info, char *data, pu_socket_len_t length, pu_socket_addr_o *addr) {
    int n;
    if(info->fam == PU_SOCKET_FAM_IP) {
        struct sockaddr_in cin;
        memset((void *)&cin, 0x00, sizeof(struct sockaddr_in));
        cin.sin_family = AF_INET;
        memcpy((void *)&cin.sin_port , (void *)&addr->port , 2);
        memcpy((void *)&cin.sin_addr.s_addr , (void *)&addr->addr , 4);        
        n = sendto(info->sock, data, length, 0, (struct sockaddr *)&cin, sizeof(struct sockaddr));
    } else if(info->fam == PU_SOCKET_FAM_IPV6) {
        return -11;
    } else {
        return -10;
    }
    if(n < 0) return -1;
    return 0;
}

pu_socket_err_t pu_socket_close(pu_socket_info_o *info) {
    int r;
    if(info->sock > 0) {
        if(close(info->sock) < 0) return -1; else return 0;
    } else return -2;
}
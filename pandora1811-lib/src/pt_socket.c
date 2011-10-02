#include "pt_socket.h"

//#include <sys/socket.h>// socket()
#include <netdb.h>// IPPROTO_TCP, IPPROTO_UDP
#include <netinet/in.h>// htons(), struct sockaddr_in
#include <string.h>// memset(), memcpy()
#include <unistd.h>// close()
#include <fcntl.h>// fcntl()
#include <netinet/tcp.h>// SOL_TCP, TCP_MAXSEG

pt_socket_err_t pt_socket_open(pt_socket_info_o *info) {
    int sock;
    if(info->fam == PT_SOCKET_FAM_IP) {
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    } else if(info->fam == PT_SOCKET_FAM_IPV6) {
        //sock = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP);
        return -11;
    } else {
        return -10;
    }
    if(sock < 0) return -1;
    info->sock = sock;
    return 0;
}

pt_socket_err_t pt_socket_async(pt_socket_info_o *info) {
    int flag;
    flag = fcntl(info->sock, F_GETFL, 0);
    if(flag < 0) return -1;
    flag = fcntl(info->sock, F_SETFL, flag | O_NONBLOCK);
    if(flag < 0) return -1;
    //if(fcntl(info->sock, F_SETFL, O_NONBLOCK) < 0) return -1;
    return 0;
}



pt_socket_err_t pt_socket_mss(pt_socket_info_o *info, pt_socket_mss_t *mss) {// ok!!!
    socklen_t optlen = 4;
    // IPPROTO_TCP
    if(getsockopt(info->sock, SOL_TCP, TCP_MAXSEG, (void *)mss, &optlen) < 0) return -1;
    //if(getsockopt(info->sock, SOL_IP, IP_MTU, (void *)mss, &optlen) < 0) return -1;
    return 0;
}

pt_socket_err_t pt_socket_bind(pt_socket_info_o *info, pt_socket_addr_o *addr) {
    int b;    
    if(info->fam == PT_SOCKET_FAM_IP) {
        struct sockaddr_in sin;
        memset((void *)&sin, 0x00, sizeof(struct sockaddr_in));
        sin.sin_family = AF_INET;
        memcpy((void *)&sin.sin_port , (void *)&addr->port , 2);
        memcpy((void *)&sin.sin_addr.s_addr , (void *)&addr->addr , 4);
        b = bind(info->sock, (struct sockaddr *)&sin, sizeof(struct sockaddr));
    } else if(info->fam == PT_SOCKET_FAM_IPV6) {
        return -11;
    } else {
        return -10;
    }
    if(b < 0) return -1;
    return 0;
}

pt_socket_err_t pt_socket_listen(pt_socket_info_o *info, int backlog) {
    if(listen(info->sock, backlog) < 0) return -1; else return 0;
}

pt_socket_err_t pt_socket_connect(pt_socket_info_o *info, pt_socket_addr_o *addr) {
    int c;    
    if(info->fam == PT_SOCKET_FAM_IP) {
        struct sockaddr_in sin;
        memset((void *)&sin, 0x00, sizeof(struct sockaddr_in));
        sin.sin_family = AF_INET;
        memcpy((void *)&sin.sin_port , (void *)&addr->port , 2);
        memcpy((void *)&sin.sin_addr.s_addr , (void *)&addr->addr , 4);
        c = connect(info->sock, (struct sockaddr *)&sin, sizeof(struct sockaddr));
    } else if(info->fam == PT_SOCKET_FAM_IPV6) {
        return -11;
    } else {
        return -10;
    }
    if(c < 0) return -1;
    return 0;
}

pt_socket_err_t pt_socket_accept(pt_socket_info_o *info, pt_socket_info_o *ainfo, pt_socket_addr_o *addr) {
    int a;
    socklen_t sin_length;    
    if(info->fam == PT_SOCKET_FAM_IP) {
        struct sockaddr_in sin;
        sin_length = sizeof(struct sockaddr);
        memset((void *)&sin, 0x00, sizeof(struct sockaddr_in));
        a = accept(info->sock, (struct sockaddr *)&sin, &sin_length);
        if(sin.sin_family != PT_SOCKET_FAM_IP) return -2;
        memcpy((void *)&addr->port , (void *)&sin.sin_port , 2);
        memcpy((void *)&addr->addr , (void *)&sin.sin_addr.s_addr , 4);
    } else if(info->fam == PT_SOCKET_FAM_IPV6) {
        return -11;
    } else {
        return -10;
    }
    if(a < 0) return -1;
    ainfo->sock = a;
    ainfo->fam = info->fam;
    return 0;
}

pt_socket_err_t pt_socket_read(pt_socket_info_o *info, char *data, pt_socket_len_t length, pt_socket_addr_o *addr) {
    int n;
    n = recv(info->sock, data, length, 0);
    if(n < 0) return -1;
    // один байт избыточный!!!
    //addr->pkg_length = n - 1;
    addr->pkg_length = n;
    // .......................
    return 0;
}

pt_socket_err_t pt_socket_write(pt_socket_info_o *info, char *data, pt_socket_len_t length) {
    if(send(info->sock, data, length, 0) < 0) return -1; else return 0;
}

pt_socket_err_t pt_socket_close(pt_socket_info_o *info) {
    int r;
    if(info->sock > 0) {
        if(close(info->sock) < 0) return -1; else return 0;
    } else return -2;
}
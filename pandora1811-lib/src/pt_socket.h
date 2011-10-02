/* 
 * File:   socket_tcp.h
 * Author: andrey5
 *
 * Created on 15 Август 2011 г., 22:58
 */

#ifndef SOCKET_TCP_H
#define	SOCKET_TCP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <sys/socket.h>// AF_INET, AF_INET6
    
#define PT_SOCKET_FAM_IP AF_INET
#define PT_SOCKET_FAM_IPV6 AF_INET6

typedef unsigned int pt_socket_t;
typedef unsigned int pt_socket_len_t;
typedef int pt_socket_err_t;
typedef unsigned int pt_socket_mss_t;

// дескриптор сокета
typedef struct pt_socket_info_o {
    pt_socket_t sock;
    unsigned int fam;// ipv4|ipv6
    // +options
} pt_socket_info_o;

// структура с адресом
typedef struct pt_socket_addr_o {
    char port[2];// port, сетевой порядок байт
    char addr[16];// ip [сетевой порядок байт]
    unsigned short pkg_length;// размер пакета, содержит размер получаемого пакета
} pt_socket_addr_o;



/*
 * -1: socket() error
 * -10: неизвестный тип сокета
 * -11: ipv6 пока еще не поддерживается
 */
extern pt_socket_err_t pt_socket_open(pt_socket_info_o *info);

/*
 * -1: fcntl() error
 */
extern pt_socket_err_t pt_socket_async(pt_socket_info_o *info);

/*
 * -1: getsockopt() error
 */
extern pt_socket_err_t pt_socket_mss(pt_socket_info_o *info, pt_socket_mss_t *mss);

/*
 * -1: bind() error
 * -10: неизвестный тип сокета
 * -11: ipv6 пока еще не поддерживается
 */
extern pt_socket_err_t pt_socket_bind(pt_socket_info_o *info, pt_socket_addr_o *addr);

/*
 * -1: listen() error
 */
extern pt_socket_err_t pt_socket_listen(pt_socket_info_o *info, int backlog);

/*
 * -1: connect() error
 * -10: неизвестный тип сокета
 * -11: ipv6 пока еще не поддерживается
 */
extern pt_socket_err_t pt_socket_connect(pt_socket_info_o *info, pt_socket_addr_o *addr);

/*
 * -1: accept() error
 * -2: несоответствие типов семейств ip-протоколов
 * -10: неизвестный тип сокета
 * -11: ipv6 пока еще не поддерживается
 */
extern pt_socket_err_t pt_socket_accept(pt_socket_info_o *info, pt_socket_info_o *ainfo, pt_socket_addr_o *addr);

/*
 * -1: recv() error
 */
extern pt_socket_err_t pt_socket_read(pt_socket_info_o *info, char *data, pt_socket_len_t length, pt_socket_addr_o *addr);

/*
 * -1: send() error
 */
extern pt_socket_err_t pt_socket_write(pt_socket_info_o *info, char *data, pt_socket_len_t length);

/*
 * -1: close() error
 * -2: дескриптор сокета равен или менше 0
 */
extern pt_socket_err_t pt_socket_close(pt_socket_info_o *info);

#ifdef	__cplusplus
}
#endif

#endif	/* SOCKET_TCP_H */


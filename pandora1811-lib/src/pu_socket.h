/* 
 * File:   socket_udp.h
 * Author: andrey5
 *
 * Created on 2 Октябрь 2011 г., 18:08
 */

#ifndef SOCKET_UDP_H
#define	SOCKET_UDP_H

#ifdef	__cplusplus
extern "C" {
#endif


// size 576!!!
    
#include <sys/socket.h>// AF_INET, AF_INET6
    
#define PU_SOCKET_FAM_IP AF_INET
#define PU_SOCKET_FAM_IPV6 AF_INET6

typedef unsigned int pu_socket_t;
typedef unsigned int pu_socket_len_t;
typedef int pu_socket_err_t;

// дескриптор сокета
typedef struct pu_socket_info_o {
    pu_socket_t sock;
    unsigned int fam;// ipv4|ipv6
    // +options
} pu_socket_info_o;

// структура с адресом
typedef struct pu_socket_addr_o {
    char port[2];// port, сетевой порядок байт
    char addr[16];// ip [сетевой порядок байт]
    unsigned short pkg_length;// размер пакета, содержит размер получаемого пакета
} pu_socket_addr_o;

/*
 * -1: socket() error
 * -10: неизвестный тип сокета
 * -11: ipv6 пока еще не поддерживается
 */
extern pu_socket_err_t pu_socket_open(pu_socket_info_o *info);

/*
 * -1: bind() error
 * -10: неизвестный тип сокета
 * -11: ipv6 пока еще не поддерживается
 */
extern pu_socket_err_t pu_socket_bind(pu_socket_info_o *info, pu_socket_addr_o *addr);

/*
 * -1: recvfrom() error
 * -2: несоответствие типов семейств ip-протоколов
 * -10: неизвестный тип сокета
 * -11: ipv6 пока еще не поддерживается
 */
extern pu_socket_err_t pu_socket_read(pu_socket_info_o *info, char *data, pu_socket_len_t length, pu_socket_addr_o *addr);

/*
 * -1: sendto() error
 * -10: неизвестный тип сокета
 * -11: ipv6 пока еще не поддерживается
 */
extern pu_socket_err_t pu_socket_write(pu_socket_info_o *info, char *data, pu_socket_len_t length, pu_socket_addr_o *addr);

/*
 * -1: close() error
 * -2: дескриптор сокета равен или менше 0
 */
extern pu_socket_err_t pu_socket_close(pu_socket_info_o *info);


#ifdef	__cplusplus
}
#endif

#endif	/* SOCKET_UDP_H */


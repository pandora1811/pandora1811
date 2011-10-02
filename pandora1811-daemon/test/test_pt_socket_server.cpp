/* 
 * File:   main.cpp
 * Author: andrey5
 *
 * Created on 14 Август 2011 г., 14:51
 */

#include <cstdlib>

using namespace std;

#include <arpa/inet.h>// inet_aton();

// Debug
#include <stdio.h>
#include <errno.h>
#include <iostream>

// динамические параметры
#define PORT 1811
#define IP "192.168.1.3"
//#define IP "127.0.0.1"
#define BUFFER_LENGTH 65000

//#include "../../pandora-lib/src/socket_udp.h"

#include <string.h>// memset(), memcpy()

// tcp
#include "../../pandora1811-lib/src/pt_socket.h"

int main(int argc, char** argv) {
    
    // TCP server
    pt_socket_err_t st;
    pt_socket_info_o info;
    info.fam = PT_SOCKET_FAM_IP;
    
    // socket
    st = pt_socket_open(&info);
    if(st < 0) {
        printf("socket() error");
    }
    
    // bind
    pt_socket_addr_o addr;
    
    short port;
    port = htons(PORT);
    memcpy((void *)addr.port, (void *)&port, 2);
    struct sockaddr_in sin;
    inet_aton(IP, &sin.sin_addr);
    memcpy((void *)&addr.addr, (void *)&sin.sin_addr.s_addr, 4);
    
    st = pt_socket_bind(&info, &addr);
    if(st < 0) {
        printf("bind() error");
    }
    
    // async
    //st = pt_socket_async(&info);
    //if(st < 0) {
    //    printf("fcntl() error");
    //}
    
    // listen
    st = pt_socket_listen(&info, 8);
    if(st < 0) {
        printf("listen() error");
    }
    
    // прием пакета
    // accept
    pt_socket_info_o info1;
    pt_socket_addr_o addr1;
    
    st = pt_socket_accept(&info, &info1, &addr1);
    if(st < 0) {
        printf("accept() error");
    }
    
    // mss
    pt_socket_mss_t mss;
    
    st = pt_socket_mss(&info1, &mss);
    if(st < 0) {
        printf("getsockopt() error");
    }
    
    printf("mss: %d;\n",mss);
    
    // read
    char buffer[BUFFER_LENGTH];
    // read!!!
    int I = 0;
    while(1) {
    
        st = pt_socket_read(&info1, buffer, BUFFER_LENGTH, &addr1);
        if(st < 0) {
                printf("recv() error");
        }
    
        printf("PACKET NUMBER: %d;\n", I);
    
        if(addr1.pkg_length == 0) break;
    
        //printf("data: %s; size: %d;\n", buffer, addr1.pkg_length);
        printf("data: %d;\n", addr1.pkg_length);
        printf("port: %x; ip: %x;\n", addr1.port[1], addr1.addr[3]);
    
        ++I;
    }
    
    // close
    st = pt_socket_close(&info1);
    if(st < 0) {
        printf("close() error");
    }
    
    // ...........
    
    // close
    st = pt_socket_close(&info);
    if(st < 0) {
        printf("close() error");
    }
    
    return 0;
}
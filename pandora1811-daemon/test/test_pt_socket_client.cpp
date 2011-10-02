/* 
 * File:   main.cpp
 * Author: andrey5
 *
 * Created on 14 Август 2011 г., 15:02
 */

#include <cstdlib>

using namespace std;

//#include "../../pandora-lib/src/socket_udp.h"

// динамические параметры
#define PORT 1811
#define IP "192.168.1.3"
//#define IP "127.0.0.1"

#include <arpa/inet.h>// inet_aton();
#include <string.h>// memset(), memcpy()

// Debug
#include <stdio.h>
#include <errno.h>
#include <iostream>

#include "../../pandora1811-lib/src/pt_socket.h"

int main(int argc, char** argv) {
    
    // TCP client
    pt_socket_err_t st;
    pt_socket_info_o info;
    info.fam = PT_SOCKET_FAM_IP;
    
    // socket
    st = pt_socket_open(&info);
    if(st < 0) {
        printf("socket() error");
    }
    
    // connect
    pt_socket_addr_o addr;
    
    short port;
    port = htons(PORT);
    memcpy((void *)addr.port, (void *)&port, 2);
    struct sockaddr_in sin;
    inet_aton(IP, &sin.sin_addr);
    memcpy((void *)&addr.addr, (void *)&sin.sin_addr.s_addr, 4);
    
    st = pt_socket_connect(&info, &addr);
    if(st < 0) {
        perror("tcp connect error");
        printf("connect() error");
    }
    
    // mss
    pt_socket_mss_t mss;
    
    st = pt_socket_mss(&info, &mss);
    if(st < 0) {
        printf("getsockopt() error");
    }
    
    printf("mss: %d;\n",mss);
    
    // send
    char data[74000];
    // генерация данных
    char alf[] = "qwertyuioplkjhgfdsazxcvbnm";// 32
    srand(time(NULL)); int N = 26;
    for(int i=0; i<74000; ++i) {
        int r = rand() % (N-1);
        data[i] = alf[r];
    }
    
    st = pt_socket_write(&info, data, sizeof(data));
    if(st < 0) {
        printf("write() error");
    }
    
    // close
    st = pt_socket_close(&info);
    if(st < 0) {
        printf("close() error");
    }

    return 0;
}
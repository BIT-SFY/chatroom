#include "../inc/socket_helper.h"
#include <cstring>
#include <iostream>

struct sockaddr_in server_addr;
int server_socket_fd;

/*创建一个socket套接字*/
bool createSocket()
{
    bzero(&server_addr, sizeof(server_addr));        // 清空该地址结构
    server_addr.sin_family = AF_INET;                // 使用TCP/IP协议族
    server_addr.sin_addr.s_addr = htons(INADDR_ANY); // INADDR_ANY：127.0.0.1，泛指本机的意思
    server_addr.sin_port = htons(SERVER_PORT);       // 设置端口

    server_socket_fd = socket(AF_INET, SOCK_STREAM, 0); // 创建socket，若成功，返回socket描述符,使用TCP/IP协议族
    if (server_socket_fd < 0) {
        perror("Create Socket Failed:");
        exit(1);
    }
    
    int opt = 1;
    setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)); // 设置收发时限
    if (-1 == (bind(server_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))) {
        perror("Server Bind Failed:");
        exit(1);
    }
    
    // 开始监听，第一个参数即为要监听的socket描述符，第二个参数为相应socket可以排队的最大连接个数
    if (-1 == (listen(server_socket_fd, LENGTH_OF_LISTEN_QUEUE))) {
        perror("Server Listen Failed:");
        exit(1);
    }

    return true;
}

bool closeSocket()
{
    close(server_socket_fd);
    return false;
}
#ifndef SOCKET_HELPER_H
#define SOCKET_HELPER_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 8000          // 服务器端口
#define LENGTH_OF_LISTEN_QUEUE 20 // 监听队列
#define FILE_NAME_MAX_SIZE 512    // 文件名最大尺寸

extern struct sockaddr_in server_addr;
extern int server_socket_fd;

/*创建一个socket套接字*/
bool createSocket();

/*关闭套接字连接*/
bool closeSocket();

#endif
#include "client.h"
#include <cstring>

#define BUFFER_SIZE 1024

Client::Client()
{
    flag = 0;
    bzero(&client_addr, sizeof(client_addr));        // 初始化
    client_addr.sin_family = AF_INET;                // 使用TCP/IP协议族
    client_addr.sin_addr.s_addr = htons(INADDR_ANY); // 本机地址127.0.0.1
}

void Client::InitClient(string user_name, string user_password, int user_port)
{
    username = user_name;
    password = user_password;
    port = user_port;
    flag = 1;
    client_addr.sin_port = user_port;                   // 端口号
    client_socket_fd = socket(AF_INET, SOCK_STREAM, 0); // 创建socket
    if (client_socket_fd < 0) {
        perror("Create Socket Failed:");
        exit(1);
    }
    // 将socket和地址结构绑定
    if (-1 == (bind(client_socket_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)))) {
        perror("Client Bind Failed:");
        exit(1);
    }
}

void Client::ConnectWithServer()
{
    // 声明服务器端的socket地址结构
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) == 0) {
        perror("Server IP Address Error:");
        exit(1);
    }
    server_addr.sin_port = htons(SERVER_PORT);
    socklen_t server_addr_length = sizeof(server_addr);

    // 将客户端socket和服务端socket连接
    if (connect(client_socket_fd, (struct sockaddr *)&server_addr, server_addr_length) < 0) {
        perror("Can Not Connect To Server IP:");
        exit(0);
    }
}

void Client::SendMessageToServer(string content, int recver_port, int message_type)
{
    Message s;
    strcpy(s.sender_name, username.c_str()); // 发送方用户名
    s.sender_port = port;                    // 发送方端口
    strcpy(s.sender_addr, "127.0.0.1");      // 发送方的ip地址
    s.sender_id = uid;                       // 发送方的uid
    s.recver_port = recver_port;             // 接收方端口
    if (message_type == SENDALL)
        s.recver_id = recver_port;      // 接收方id
    strcpy(s.recver_addr, "127.0.0.1"); // 接受方的ip地址
    if (message_type == SIGNIN || message_type == LOGIN) {
        strcpy(s.content, password.c_str()); // 如果是注册或登录信息，则将内容改写为密码
    } else {
        strcpy(s.content, content.c_str()); // 内容
    }
    s.message_type = message_type; // 消息类型
    s.send_time = time(nullptr);   // 发送时间(当前时间戳)
    s.PrintMessageInfo();
    if (send(client_socket_fd, &s, sizeof(Message), 0) < 0) {
        perror("Send Failed:");
        exit(1);
    }
}

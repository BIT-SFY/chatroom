#ifndef CLIENT_H
#define CLIENT_H

#include "Frame.h"

class Client
{
private:
    string addr;                    // 发送方ip地址
    struct sockaddr_in client_addr; // socket地址结构

public:
    int uid;                                                                     // uid
    int flag;                                                                    // 当前在线状态
    int port;                                                                    // 端口号
    int client_socket_fd;                                                        // socket标识符
    string username;                                                             // 用户名
    string password;                                                             // 密码
    Client();                                                                    // 构造函数，初始化函数，用来登录
    void InitClient(string user_name, string user_password, int user_port);      // 初始化Client中的数据
    void ConnectWithServer();                                                    // 与服务建立连接
    void SendMessageToServer(string content, int recver_port, int message_type); // 发送消息给服务器
};

#endif // CLIENT_H

#ifndef FRAME_H
#define FRAME_H

#include <QMessageBox>
#include <arpa/inet.h>
#include <iostream>
#include <net/if.h>
#include <netinet/in.h>
#include <queue>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <time.h>

#define SERVER_PORT 8000
#define BUFFER_SIZE 1024 // 缓冲区大小
#define SIGNIN -3
#define USEREXIT -2
#define ONLINE -1
#define SENDMSG 0
#define SENDALL 1
#define LOGIN 2
#define CREATEGROUP 3
#define CALLGROUPLIST 4
#define JOINGROUP 5
#define QUITGROUP 6

using namespace std;

// 定义一个消息帧
typedef struct Message {
    int message_id;            // 信息id
    char sender_name[20];      // 发送方用户名
    int sender_id;             // 发送方用户id
    int sender_port;           // 发送方端口号
    char sender_addr[15];      // 发送方ip地址
    int recver_id;             // 接收方id
    int recver_port;           // 接收方端口号
    char recver_addr[15];      // 接收方ip地址
    char content[BUFFER_SIZE]; // 内容
    int message_type;          // 消息类型
    int send_time;             // 消息时间
    string GetMessageType()
    {
        switch (message_type) {
        case SIGNIN:
            return "注册";
            break;
        case ONLINE:
            return "申请上线";
            break;
        case SENDMSG:
            return "发送信息";
            break;
        case LOGIN:
            return "登录";
            break;
        case USEREXIT:
            return "用户退出";
            break;
        case CREATEGROUP:
            return "创建群聊";
            break;
        case CALLGROUPLIST:
            return "申请群聊列表";
            break;
        case JOINGROUP:
            return "加入群聊";
            break;
        case SENDALL:
            return "发送群消息";
            break;
        case QUITGROUP:
            return "退出群聊";
            break;
        default:
            return "司马操作";
            break;
        }
    }
    void PrintMessageInfo()
    {
        cout << sender_name << " " << sender_port << " " << recver_port << " " << content << " " << GetMessageType() << endl;
    }

} Message;

#endif // FRAME_H

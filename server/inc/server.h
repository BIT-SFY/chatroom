#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>

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

// 用户列表
typedef struct client_info {
    char username[20];
    char addr[20];
    int port;
    int socketId;
    int flag;
    int uid;
} clientInfo;

struct Message;

using namespace std;

class Server
{
private:
    unordered_map<int, clientInfo> clientHashMap;
    int USERCOUNT;  // 用户数目
    int MSGCOUNT;   // 信息数目
    int GROUPCOUNT; // 群聊组数目

public:
    Server();
    ~Server();
    void CatchMessage();
    void UserSignIn(Message &s, int session_fd);
    void UserLogin(Message &s, int session_fd);
    void AddNewClient(Message &s, int session_fd);
    void ReturnUsersList();
    void ReturnGroupList(Message &s, int session_fd);
    void SendMessageToUser(Message &s);
    void SendMessageToGroup(Message &s);
    void CreateGroup(Message &s, int session_fd);
    void AddNewUserToGroup(Message &s, int session_fd);
    void QuitGroup(Message &s, int session_fd);
    void DeleteUser(Message &s, int session_fd);
    friend void Data_handle(Server *sv, int session_fd);
};

string GetMessageType(int message_type);
void Data_handle(Server *sv, int session_fd);

#endif
#include "server.h"
#include "db_helper.h"
#include "socket_helper.h"
#include <thread>

Server::Server() : USERCOUNT(0), MSGCOUNT(0), GROUPCOUNT(0)
{
    // rebuildDatabase();
    USERCOUNT = getUsersNumber();
    MSGCOUNT = getMessageNumber();
    GROUPCOUNT = getGroupNumber();
    cout << "服务器成功启动!" << endl;
    CatchMessage(); 
}

Server::~Server()
{
    closeSocket();   // 关闭socket连接
    closeDatabase(); // 关闭与数据库的连接
}

void Server::CatchMessage()
{
    while (true) {
        // 定义客户端的socket地址结构
        struct sockaddr_in client_addr;
        socklen_t client_addr_length = sizeof(client_addr);

        // 返回一个新的socket(描述符)，并将接收到的客户端信息写在client_addr中
        int session_fd = accept(server_socket_fd, (struct sockaddr *)&client_addr, &client_addr_length);
        if (session_fd < 0) {
            perror("Server Accept Failed:");
        }
        printf("新接入客户端 ip地址:%s , 端口:%d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

        // 创建接收这个客户端消息的线程
        thread pthread(Data_handle, this, session_fd);
        pthread.detach();
    }
    // 关闭服务器的socket
    shutdown(server_socket_fd, SHUT_RDWR);
}

void Server::AddNewClient(Message &s, int session_fd)
{
    updateUserPortByUserName(s.sender_port, s.sender_name);
    strcpy(clientHashMap[s.sender_id].addr, s.sender_addr);
    strcpy(clientHashMap[s.sender_id].username, s.sender_name);
    clientHashMap[s.sender_id].port = s.sender_port;
    clientHashMap[s.sender_id].socketId = session_fd;
    printf("\n===========当前接入服务器的客户端==========\n");
    for (auto it = clientHashMap.begin(); it != clientHashMap.end(); it++) { // 连接队列数
        cout << "| addr:" << it->second.addr << " port:" << it->second.port << " socket:" << it->second.socketId << " uid:" << it->first << " |" << endl;
    }
    printf("===========================================\n\n");
    ReturnUsersList();
}

void Server::SendMessageToUser(Message &s)
{
    if (s.sender_port == s.recver_port)
        return; // 如果发的人和收的人是同一个人，则直接结束
    int recver_id = getUidByPort(s.recver_port);
    if (clientHashMap.find(recver_id) != clientHashMap.end()) {
        s.recver_id = recver_id;
        if (send(clientHashMap[recver_id].socketId, &s, sizeof(Message), 0) < 0) {
            perror("Send Failed:");
            exit(1);
        }
        insertIntoMessageInfo(s, ++MSGCOUNT);
        cout << "内容:" << s.content << endl;
    }
}

void Server::SendMessageToGroup(Message &s)
{
    // 先把消息插入消息表中
    insertIntoMessageInfo(s, ++MSGCOUNT);
    // 根据群id找出uid,再从uid中找出port
    vector<int> uidlist = getUidFromGroup(s.recver_id);
    while (!uidlist.empty()) {
        int recver_id = uidlist.back();
        uidlist.pop_back();
        if (s.sender_id == recver_id)
            continue;                                               // 如果发的人和收的人是同一个人，则继续
        if (clientHashMap.find(recver_id) != clientHashMap.end()) { // 如果在在线用户中能找到该用户uid
            if (send(clientHashMap[recver_id].socketId, &s, sizeof(Message), 0) < 0) {
                perror("Send Failed:");
                exit(1);
            }
        }
    }
}

void Server::ReturnUsersList()
{
    Message s;
    s.message_type = -1;
    string str;
    for (auto it = clientHashMap.begin(); it != clientHashMap.end(); it++) {
        str += it->second.username;
        str.push_back('.');
        str += to_string(it->second.port);
        str.push_back('.');
    }
    strcpy(s.content, str.c_str());
    for (auto it = clientHashMap.begin(); it != clientHashMap.end(); it++) {
        if (send(it->second.socketId, &s, sizeof(s), 0) < 0) {
            perror("Send Failed:");
            exit(1);
        }
    }
}

void Server::UserLogin(Message &s, int session_fd)
{
    // 密码存放在了s.content中
    s.sender_id = isUserPasswordCorrect(s.sender_name, s.content);
    if (send(session_fd, &s, sizeof(Message), 0) < 0) {
        perror("Send Failed:");
        exit(1);
    }
}

void Server::CreateGroup(Message &s, int session_fd)
{
    string group_name = s.content;
    int pos = group_name.find(':');
    group_name = group_name.substr(pos + 1);

    bool isOk = insertIntoGroupInfo(atoi(s.content), group_name.c_str(), s.sender_id, 0, s.send_time);
    if (isOk) {
        AddNewUserToGroup(s, session_fd);
    } else {
        if (send(session_fd, &s, sizeof(Message), 0) < 0) {
            perror("Send Failed:");
            exit(1);
        }
    }
}

void Server::AddNewUserToGroup(Message &s, int session_fd)
{
    // group_id存放在了content中
    bool isOK = insertIntoGroupUserRelation(atoi(s.content), s.sender_id);
    if (isOK) {
        ReturnGroupList(s, session_fd);
    } else {
        if (send(session_fd, &s, sizeof(Message), 0) < 0) {
            perror("Send Failed:");
            exit(1);
        }
    }
}

void Server::QuitGroup(Message &s, int session_fd)
{
    // 根据uid和groupid删除关系表中的数据
    deleteDataByUidGid(s.sender_id, s.recver_port);
    s.message_type = CALLGROUPLIST;
    ReturnGroupList(s, session_fd);
}

void Server::ReturnGroupList(Message &s, int session_fd)
{
    // 从数据库中捞出来这个uid加入了哪些群聊
    string str = getGroupListByUid(s.sender_id);
    strcpy(s.content, str.c_str());
    if (send(session_fd, &s, sizeof(s), 0) < 0) {
        perror("Send Failed:");
        exit(1);
    }
}

void Server::UserSignIn(Message &s, int session_fd)
{
    bool isOk = insertIntoUserInfo(++USERCOUNT, s.sender_name, s.content, s.send_time);
    if (isOk) { // 注册成功
        s.sender_id = USERCOUNT;
    } else {
        s.sender_id = -1; // 注册失败
        --USERCOUNT;
    }
    if (send(session_fd, &s, sizeof(Message), 0) < 0) {
        perror("Send Failed:");
        exit(1);
    }
    if (s.sender_id >= 0)
        close(session_fd); // 如果注册成功就关闭socket连接
}

void Server::DeleteUser(Message &s, int session_fd)
{
    // 关闭服务器中该端口的读写工作
    close(session_fd);
    // 删除该客户端在服务器中的在线记录
    clientHashMap.erase(s.sender_id);
    // 返回用户列表
    ReturnUsersList();
}

void Data_handle(Server *sv, int session_fd)
{
    Message s; // 创建结构体用来接受信息
    while (true) {
        // recv函数通过描述字读取数据到字节流，并存储到地址字符串
        // 如果断开了这个socket，这里会自动报错并关闭接收对应客户端的线程
        if (recv(session_fd, &s, sizeof(Message), 0) < 0) {
            perror("Server Recieve Data Failed:");
            break;
        }
        cout << "发送方端口:" << s.sender_port << "\t接收方端口:" << s.recver_port << "\t帧类型:" << GetMessageType(s.message_type) << endl;
        switch (s.message_type) {
        case SIGNIN:
            sv->UserSignIn(s, session_fd); // 用户注册
            break;
        case LOGIN:
            sv->UserLogin(s, session_fd); // 用户登录
            break;
        case ONLINE:
            sv->AddNewClient(s, session_fd); // 申请上线
            break;
        case CALLGROUPLIST:
            sv->ReturnGroupList(s, session_fd); // 申请群聊列表
            break;
        case SENDMSG:
            sv->SendMessageToUser(s); // 给用户转发消息
            break;
        case SENDALL:
            sv->SendMessageToGroup(s); // 给所有人转发
            break;
        case CREATEGROUP:
            sv->CreateGroup(s, session_fd); // 创建群聊
            break;
        case JOINGROUP:
            sv->AddNewUserToGroup(s, session_fd);
            break;
        case QUITGROUP:
            sv->QuitGroup(s, session_fd);
            break;
        case USEREXIT:
            sv->DeleteUser(s, session_fd); // 删除当前用户的在线记录
            break;
        default:
            break;
        }
    }
    pthread_exit(NULL); // terminate calling thread!
}

string GetMessageType(int message_type)
{
    switch (message_type) {
    case SIGNIN:
        return "注册账户";
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
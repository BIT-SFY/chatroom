#ifndef DB_HELPER_H
#define DB_HELPER_H

#include <iostream>
#include <mysql/mysql.h>
#include <vector>

#define BUFFER_SIZE 1024 // 缓冲区大小

using namespace std;

// 定义一个消息帧
typedef struct Message {
    int message_id;            // 信息id
    char sender_name[20];      // 发送法用户名
    int sender_id;             // 发送方用户id
    int sender_port;           // 发送方端口号
    char sender_addr[15];      // 发送方ip地址
    int recver_id;             // 接收方id
    int recver_port;           // 接收方端口号
    char recver_addr[15];      // 接收方ip地址
    char content[BUFFER_SIZE]; // 内容
    int message_type;          // 消息类型
    int send_time;             // 消息时间
} Message;

extern MYSQL *con;     // 设置服务器接口
extern MYSQL_RES *res; // 接收sql语句的返回内容
extern MYSQL_ROW row;  // 读取返回内容的每一行

/*连接服务器*/
bool connectDatabase();

/*重新构建服务器*/
void rebuildDatabase();

/*获取当前服务器人数*/
int getUsersNumber();

/*获取服务器中消息条数*/
int getMessageNumber();

/*获取服务器中群聊个数*/
int getGroupNumber();

/*将用户信息插入*/
bool insertIntoUserInfo(int user_id, char *user_name, char *user_password, int regtime);

/*检查用户名与密码是否匹配*/
int isUserPasswordCorrect(char *user_name, char *user_password);

/*获得此用户的群聊列表*/
string getGroupListByUid(int user_id);

/*获得该群聊的所有用户*/
vector<int> getUidFromGroup(int group_id);

/*插入群聊信息*/
bool insertIntoGroupInfo(int group_id, const char *group_name, int creater_id, int group_count, int create_time);

/*插入用户群聊对应表*/
bool insertIntoGroupUserRelation(int group_id, int user_id);

/*根据端口找到id*/
int getUidByPort(int user_port);

/*更新用户端口号*/
bool updateUserPortByUserName(int user_port, char *user_name);

/*去除用户群聊关系表中的数据*/
bool deleteDataByUidGid(int user_id, int group_id);

/*插入消息*/
bool insertIntoMessageInfo(Message &s, int message_id);

/*关闭数据库*/
void closeDatabase();

#endif
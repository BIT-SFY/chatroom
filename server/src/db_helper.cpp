#include "../inc/db_helper.h"
#include "../inc/initsql.h"

MYSQL *con;     // 设置服务器接口
MYSQL_RES *res; // 接收sql语句的返回内容
MYSQL_ROW row;  // 读取返回内容的每一行

/*连接服务器*/
bool connectDatabase()
{
    const char *host = "127.0.0.1";
    const char *user = "root";
    const char *pw = "";
    const char *database_name = "chatroom";
    const int port = 3306; // 默认端口号

    con = mysql_init(NULL);
    if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0)) {
        fprintf(stderr, "Failed to connect to database; Error:%s\n", mysql_error(con));
        return false;
    } else {
        cout << "数据库连接成功!" << endl;
    }
    return true;
}

/*重建数据库*/
void rebuildDatabase()
{
    for (int i = 0; i < sqlList.size(); i++) {
        if (mysql_query(con, sqlList[i].c_str())) {
            cout << i << endl;
            fprintf(stderr, "Error:%s\n", mysql_error(con));
            cout << "重建数据库失败!" << endl;
            return;
        }
    }
    cout << "重建数据库成功!" << endl;
}

/*获取当前注册人数*/
int getUsersNumber()
{
    // 统计用户个数
    char sql[64];
    sprintf(sql, "SELECT COUNT(*) FROM user_info");
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to select data: Error:%s\n", mysql_error(con));
        return -1;
    }
    res = mysql_store_result(con);
    row = mysql_fetch_row(res);
    return atoi(row[0]);
}

/*获取服务器中消息条数*/
int getMessageNumber()
{
    char sql[64];
    sprintf(sql, "SELECT COUNT(*) FROM message_info");
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to select data: Error:%s\n", mysql_error(con));
        return -1;
    }
    res = mysql_store_result(con);
    row = mysql_fetch_row(res);
    return atoi(row[0]);
}

/*获取服务器中群聊个数*/
int getGroupNumber()
{
    char sql[64];
    sprintf(sql, "SELECT COUNT(*) FROM group_info");
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to select data: Error:%s\n", mysql_error(con));
        return -1;
    }
    res = mysql_store_result(con);
    row = mysql_fetch_row(res);
    return atoi(row[0]);
}

/*将用户信息插入到用户表中*/
bool insertIntoUserInfo(int user_id, char *user_name, char *user_password, int regtime)
{
    char sql[256];
    sprintf(sql, "INSERT INTO user_info (user_id, user_name, user_password, regtime) VALUES (%d,'%s','%s',%d)",
            user_id, user_name, user_password, regtime);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to insert data: Error:%s\n", mysql_error(con));
        return false;
    }
    return true;
}

/*检查用户名与密码是否匹配*/
int isUserPasswordCorrect(char *user_name, char *user_password)
{
    char sql[256];
    sprintf(sql, "SELECT user_password,user_id FROM user_info WHERE user_name = '%s' AND user_password = '%s'",
            user_name, user_password);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to select data: Error:%s\n", mysql_error(con));
    }
    res = mysql_store_result(con);
    row = mysql_fetch_row(res);
    if (!row) {    // 没内容，该账号名与密码不匹配
        return -1; // 利用sender_id作为检查密码成功与否的中介
    }
    return atoi(row[1]);
}

/*获得此用户的群聊列表*/
string getGroupListByUid(int user_id)
{
    string str;
    char sql[256];
    sprintf(sql, "SELECT group_name, group_info.group_id"
                 " FROM group_user_relation, group_info"
                 " WHERE group_info.group_id = group_user_relation.group_id AND user_id = %d",
            user_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to select data: Error:%s\n", mysql_error(con));
        return str;
    }
    res = mysql_store_result(con);
    row;
    while ((row = mysql_fetch_row(res))) {
        str = str + row[0] + ':' + row[1] + ':';
    }
    return str;
}

/*获得该群聊的所有用户*/
vector<int> getUidFromGroup(int group_id)
{
    vector<int> uidlist;
    // 根据群id找出uid,再从uid中找出port
    char sql[128];
    sprintf(sql, "SELECT user_id FROM group_user_relation WHERE group_id = %d", group_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to select data: Error:%s\n", mysql_error(con));
        return uidlist;
    }
    res = mysql_store_result(con);
    row;
    while ((row = mysql_fetch_row(res))) {
        uidlist.push_back(atoi(row[0]));
    }
    return uidlist;
}

/*插入群聊信息*/
bool insertIntoGroupInfo(int group_id, const char *group_name, int creater_id, int group_count, int create_time)
{
    char sql[256];
    sprintf(sql, "INSERT INTO group_info (group_id, group_name, creater_id, group_count, create_time) VALUES (%d,'%s',%d,%d,%d)",
            group_id, group_name, creater_id, 0, create_time);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to insert data: Error:%s\n", mysql_error(con));
        return false;
    }
    return true;
}

/*插入用户群聊对应表*/
bool insertIntoGroupUserRelation(int group_id, int user_id)
{
    char sql[128];
    sprintf(sql, "INSERT INTO group_user_relation (group_id, user_id) VALUES (%d,%d)", group_id, user_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to insert data: Error:%s\n", mysql_error(con));
        return false; // 插入用户群聊信息失败
    }
    return true;
}

/*根据端口找到id*/
int getUidByPort(int user_port)
{
    string tsql = "SELECT user_id FROM user_info WHERE user_port = " + to_string(user_port);
    if (mysql_query(con, tsql.c_str())) {
        fprintf(stderr, "Failed to select data: Error:%s\n", mysql_error(con));
        return -1;
    }
    res = mysql_store_result(con);
    row = mysql_fetch_row(res);
    return atoi(row[0]);
}

/*更新用户端口号*/
bool updateUserPortByUserName(int user_port, char *user_name)
{
    char sql[128];
    sprintf(sql, "UPDATE user_info SET user_port = %d WHERE user_name = '%s' ", user_port, user_name);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to update data: Error:%s\n", mysql_error(con));
        return false;
    }
    return true;
}

/*去除用户群聊关系表中的数据*/
bool deleteDataByUidGid(int user_id, int group_id)
{
    char sql[128];
    sprintf(sql, "DELETE FROM group_user_relation WHERE user_id = %d AND group_id = %d", user_id, group_id);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to delete data: Error:%s\n", mysql_error(con));
        return false;
    }
    return true;
}

/*插入消息*/
bool insertIntoMessageInfo(Message &s, int message_id)
{
    char sql[2048];
    sprintf(sql, "INSERT INTO message_info (message_id,"
                 "sender_name, sender_id, sender_port,sender_addr,"
                 "recver_id,recver_port,recver_addr,"
                 "message_type,content,send_time) "
                 "VALUES (%d,'%s',%d,%d,'%s',%d,%d,'%s',%d,'%s',%d)",
            message_id,
            s.sender_name, s.sender_id, s.sender_port, s.sender_addr,
            s.recver_id, s.recver_port, s.recver_addr,
            s.message_type, s.content, s.send_time);
    if (mysql_query(con, sql)) {
        fprintf(stderr, "Failed to insert data: Error:%s\n", mysql_error(con));
    }
    return true;
}

/*关闭数据库*/
void closeDatabase()
{
    mysql_close(con);
}
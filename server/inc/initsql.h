
vector<string> sqlList = {
{"DROP TABLE group_user_relation;"},
{"DROP TABLE message_info;"},
{"DROP TABLE group_info;"},
{"DROP TABLE user_info;"},
{"CREATE TABLE user_info("
"user_id INT NOT NULL PRIMARY KEY,"
"user_name VARCHAR(20) NOT NULL UNIQUE,"
"user_password VARCHAR(20) NOT NULL,"
"user_port INT UNIQUE,"
"regtime INT NOT NULL);"},
{"CREATE TABLE message_info("
"message_id INT PRIMARY KEY,"
"sender_name VARCHAR(20),"
"sender_id INT,"
"sender_port INT,"
"sender_addr VARCHAR(15),"
"recver_id INT,"
"recver_port INT,"
"recver_addr VARCHAR(15),"
"message_type int,"
"content MEDIUMTEXT, "
"send_time int not null,"
"CONSTRAINT FK_SENDERID_USERID FOREIGN KEY(sender_id) REFERENCES user_info(user_id));"},
{"CREATE TABLE	group_info("
"group_id INT PRIMARY KEY,"
"group_name VARCHAR(20),"
"creater_id INT,"
"group_count INT,"
"create_time INT NOT NULL,"
"CONSTRAINT FK_CREATERID_USERID FOREIGN KEY(creater_id) REFERENCES user_info(user_id));"},
{"CREATE TABLE group_user_relation("
"group_id INT,"
"user_id INT,"
"CONSTRAINT PK_GROUPID_USERID PRIMARY KEY(group_id, user_id),"
"CONSTRAINT FK_GROUPID_USERID FOREIGN KEY(group_id) REFERENCES group_info(group_id),"
"CONSTRAINT FK_USERID_USERID FOREIGN KEY(user_id) REFERENCES user_info(user_id));"},
{"INSERT INTO user_info(user_id, user_name, user_password, regtime) VALUES (1,'申馥源',123,1678624723);"},
{"INSERT INTO user_info(user_id, user_name, user_password, regtime) VALUES (2,'孙子玉',123,1678624731);"},
{"INSERT INTO user_info(user_id, user_name, user_password, regtime) VALUES (3,'admin',123,1678626560);"},
{"INSERT INTO user_info(user_id, user_name, user_password, regtime) VALUES (4,'123',123,1678626571);"} 
};
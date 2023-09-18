#include "server.h"
#include "db_helper.h"
#include "socket_helper.h"

int main(){
    createSocket();
    connectDatabase();
    Server s;
    return 0;
}
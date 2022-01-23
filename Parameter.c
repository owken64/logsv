#include "Parameter.h"
#include "Config.h"
#include "Bool.h"
#include <arpa/inet.h> // struct sockaddr_in, struct sockaddr, inet_ntoa()
#include <stdio.h>

// Server
int sockLogsv;
struct sockaddr_in sockAddrLogsv;

// Client
int sockClient[MAX_CONNECTION];
struct sockaddr_in sockAddrClient[MAX_CONNECTION];

// Message
char message[MSG_LENGTH];

// Log file
FILE* logfile;

// 処理用
BOOL flg_recv;


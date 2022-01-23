#pragma once
#include "Config.h"
#include "Bool.h"
#include <arpa/inet.h> // struct sockaddr_in, struct sockaddr, inet_ntoa()
#include <stdio.h>

// Server
extern int sockLogsv;

// Client
extern int sockClient[MAX_CONNECTION];

// Message
extern char message[MSG_LENGTH];

// Log file
extern FILE* logfile;

// 処理用
extern BOOL flg_recv;


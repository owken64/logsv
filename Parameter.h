#pragma once
#include "Config.h"
#include "Bool.h"
#include <arpa/inet.h> // struct sockaddr_in, struct sockaddr, inet_ntoa()
#include <sys/select.h>
#include <stdio.h>

// Server
extern int sockLogsv;
extern struct sockaddr_in sockAddrLogsv;

// Client
extern int sockClient[MAX_CONNECTION];
extern struct sockaddr_in sockAddrClient[MAX_CONNECTION];
extern BOOL availableSockClient[MAX_CONNECTION];

// Select用
extern fd_set readfds;

// Message
extern char message[MSG_LENGTH];

// Log file
extern FILE* logfile;

// 処理用
extern BOOL flg_recv;


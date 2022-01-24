#pragma once
#include <sys/socket.h>

#define NETWORK_CONNECT_SUCCESS 0
#define NETWORK_CONNECT_FAILURE -1
#define NETWORK_RECEIVE_SUCCESS 0
#define NETWORK_RECEIVE_FAILURE -2

int NetworkInit();
void NetworkClose();

void NetworkReceive();

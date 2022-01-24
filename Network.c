#include "Network.h"
#include "Parameter.h"
#include "Config.h"
#include "Bool.h"
#include <stdio.h> //printf(), fprintf(), perror()
#include <sys/socket.h> //socket(), bind(), accept(), listen()
#include <arpa/inet.h> // struct sockaddr_in, struct sockaddr, inet_ntoa()
#include <stdlib.h> //atoi(), exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <string.h> //memset()
#include <unistd.h> //close()
#include <sys/select.h>

#define QUEUELIMIT 5

int NetworkListen();
int OpenSocket();
void CloseSocket(int);

int NetworkInit(){
	// パラメータの初期化
	for(int i = 0; i < MAX_CONNECTION; i++){
		availableSockClient[i] = FALSE;
	}
	
	// サーバーを待機させる
	if ( NetworkListen() == NETWORK_CONNECT_FAILURE) {
		return NETWORK_CONNECT_FAILURE;
	}
	
	// select()用fd_setの設定
	// fd_setの初期化します
	FD_ZERO(&readfds);

	// selectで待つ読み込みソケットとしてsockLogsv(サーバのソケット)を登録します
	FD_SET(sockLogsv, &readfds);

	return NETWORK_CONNECT_SUCCESS;
}

void NetworkClose(){
	// 各クライアントとのソケットをクローズ
	for(int i = 0; i < MAX_CONNECTION; i++) {
		CloseSocket(i);
	}
	
	// リッスン用ソケットをクローズ
	FD_CLR(sockLogsv, &readfds);
	close(sockLogsv);
}

int NetworkReceive(){
    fd_set fds;
	// 初期化
	// 読み込み用fd_setの初期化
	// selectが毎回内容を上書きしてしまうので、毎回初期化します
	memcpy(&fds, &readfds, sizeof(fd_set));

	// fdsに設定されたソケットが読み込み可能になるまで待ちます
	select(0, &fds, NULL, NULL, NULL);
	
	// サーバのソケットが受信したならば
	if(FD_ISSET(sockLogsv, &fds)){
		if( OpenSocket() == NETWORK_CONNECT_FAILURE) return NETWORK_RECEIVE_FAILURE;
	}
	// クライアントのソケットが受信したならば
	for (int i = 0; i < MAX_CONNECTION; i++ ) {
	  if (availableSockClient[i]) {
	    if (FD_ISSET(sockClient[i], &fds)){
		// メッセージを受け取る
		  if (recv(sockClient[i], message, sizeof(message), 0 ) < 0 ){
		    flg_recv = FALSE;
		    perror("message isn't completed to receive.");
		    return NETWORK_RECEIVE_FAILURE;
		  }
		  flg_recv = TRUE;
	    }
	  }
	} // 同時にメッセージを受け取った場合は、最後のソケットのメッセージのみが残る(バグ)
	
	return NETWORK_RECEIVE_SUCCESS;
}

int NetworkListen(){

    if ((sockLogsv = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ){
        perror("socket() failed.");
        return NETWORK_CONNECT_FAILURE;
    }

    memset(&sockAddrLogsv, 0, sizeof(sockAddrLogsv));
    sockAddrLogsv.sin_family      = AF_INET;
    sockAddrLogsv.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddrLogsv.sin_port        = htons(PORT_LOGSV);

    if (bind(sockLogsv, (struct sockaddr *) &sockAddrLogsv, sizeof(sockAddrLogsv) ) < 0 ) {
        perror("bind() failed.");
        return NETWORK_CONNECT_FAILURE;
    }

    if (listen(sockLogsv, QUEUELIMIT) < 0) {
        perror("listen() failed.");
        return NETWORK_CONNECT_FAILURE;
    }
    
    return NETWORK_CONNECT_SUCCESS;
}

int OpenSocket(){
		unsigned int clitLen; // client internet socket address length
		// 空いているクライアントのソケットを探す
		int idx;
		idx = 0;
		while((idx < MAX_CONNECTION) && (availableSockClient[idx] == TRUE) ) idx++;
		if (idx == MAX_CONNECTION ){
		 perror("Clients are full.");
		 return NETWORK_CONNECTION_FAILURE;
		}
		// Accept
		clitLen = sizeof(sockAddrClient[idx]);
        if ((sockClient[idx] = accept(sockLogsv, (struct sockaddr *) &sockAddrClient[idx], &clitLen)) < 0) {
            perror("accept() failed.");
            return NETWORK_CONNECTION_FAILURE;
        }
        availableSockClient[idx] = TRUE;
        
        // select()用の準備
        FD_SET(sockClient[idx], &readfds);
        
        return NETWORK_CONNECT_SUCCESS;
	
}

void CloseSocket(int idx){
	if (availableSocketClient[idx] ) {
		close(sockClient[idx]);
		availableSockClient[idx] = FALSE;
		FD_CLR(sockClient[idx], &readfds);
	}
}

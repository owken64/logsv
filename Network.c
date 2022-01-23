#include "Network.h"
#include "Parameter.h"
#include "Bool.h"

int NetworkInit(){

	return NETWORK_CONNECT_SUCCESS;
}

void NetworkClose(){
}

void NetworkReceive(){

	// メッセージを受け取ったならば
	
	flg_recv = TRUE;
}

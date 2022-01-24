#include <unistd.h>
#include <stdio.h>
#include "Network.h"
#include "Log.h"
#include "Parameter.h"
#include "BOOL.h"

void mainLoop(void){

	// 初期処理
	OpenLogfile();
	NetworkInit();
	
	// ループ
	while (TRUE){
	
	  NetworkReceive();
	
	  if (flg_recv) {
	  	WriteLog(message);
	  }
	}

	// 終了処理	
	NetworkClose();
	CloseLogfile();
}

int main(void){
    //ここで子プロセスを生成し親は終了
    if(daemon(0, 0) == 0) {
        mainLoop();
    } else {
        printf("error\n");
    }
    return 0;
}
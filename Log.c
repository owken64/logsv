#include "Log.h"
#include "Config.h"
#include "Parameter.h"
#include "Bool.h"
#include <stdio.h>

int OpenLogfile(){
	logfile = fopen(PATH_LOGFILE, "a");
}

void CloseLogfile(){
	fclose(logfile);
}

void writeLog(char *msg){

	flg_recv = FALSE;
}

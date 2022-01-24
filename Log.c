#include "Log.h"
#include "Config.h"
#include "Parameter.h"
#include "Bool.h"
#include <stdio.h>
#include <string.h>

int OpenLogfile(){
	logfile = fopen(PATH_LOGFILE, "a");
	
	return LOG_OPEN_SUCCESS;
}

void CloseLogfile(){
	fclose(logfile);
}

void writeLog(char *msg){
	char buf[MSG_LENGTH];

	memcpy(buf, message, sizeof(message));
	sprintf(message, "%s\n", buf);
	fputs(msg, logfile);
	flg_recv = FALSE;
}

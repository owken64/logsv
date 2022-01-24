#pragma once

#define LOG_OPEN_SUCCESS 0
#define LOG_OPEN_FAILURE -1

int OpenLogfile();
void CloseLogfile();

void WriteLog(char *msg);
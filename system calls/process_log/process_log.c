#include <stdio.h>
#include <linux/unistd.h>
#include "process_log.h"

int get_proc_log_level()
{
    int ret_level = syscall(PROC_LOG_CALL - 2);
    return ret_level;
}

int set_proc_log_level(int new_level)
{
    int ret_level = syscall(PROC_LOG_CALL - 1, new_level);
    return ret_level;
}

int proc_log_message(int level, char* message)
{
    int ret_level = syscall(PROC_LOG_CALL, message, level);
    return ret_level;
}

// HARNESS FUNCTIONS

int* retrieve_set_level_params(int new_level)
{
   // int params[3] = {PROC_LOG_CALL - 1, 1, new_level};
   // return params;
	int* params = (int *)malloc(sizeof(int)*3);
	params[0] = PROC_LOG_CALL - 1;
	params[1] = 1;
	params[2] = new_level;
	return params;
}

int* retrieve_get_level_params()
{
   // int params[2] = {PROC_LOG_CALL - 1, 0};
   // return params;
	int* params = (int *)malloc(sizeof(int)*2);
	params[0] = PROC_LOG_CALL - 2;
	params[1] = 0;
	return params;
}

int interpret_set_level_result(int ret_value)
{
    return ret_value;
}

int interpret_get_level_result(int ret_value)
{
    return ret_value;
}

int interpret_log_message_result(int ret_value)
{
    return ret_value;
}

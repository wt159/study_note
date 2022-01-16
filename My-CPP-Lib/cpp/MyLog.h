#ifndef MY_LOG_H
#define MY_LOG_H

#include <stdio.h>

// #define DEBUG 
#ifdef __DEBUG

#define MLOGI(fmt, ...) \
    printf("[INFO ][%s][%d]:" fmt, __func__, __LINE__, ##__VA_ARGS__)
#define MLOGW(fmt, ...) \
    printf("[WRAN ][%s][%d]:" fmt, __func__, __LINE__, ##__VA_ARGS__)
#define MLOGE(fmt, ...) \
    printf("[ERROR][%s][%d]:" fmt, __func__, __LINE__, ##__VA_ARGS__)
#define MLOGD(fmt, ...) \
    printf("[DEBUG][%s][%d]:" fmt, __func__, __LINE__, ##__VA_ARGS__)

#else

#define MLOGI(fmt, ...) 
#define MLOGW(fmt, ...) 
#define MLOGE(fmt, ...) 
#define MLOGD(fmt, ...) 

#endif // DEBUG

#endif // !MY_LOG_H

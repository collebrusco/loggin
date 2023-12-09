
#ifndef LOGGIN_H
#define LOGGIN_H

#ifdef __cplusplus
extern "C" {
#endif
#include <cstdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "level.h"
#ifndef _LOGGIN_LEVEL
	#error "define log level in level.h"
#endif

#define LOGGIN_FILE_OPEN(name) \
	#define _LOGGIN_FILE_OUT ; \
	#undef _LOGGIN_OUT(level, name, fmt, ...) \
	#define _LOGGIN_OUT(level, name, fmt, ...) fprintf(_logFile, "[[" level "] %s]: " fmt, name, ##__VA_ARGS__) \
	FILE* _logFile = fopen(#name, "w")

#define LOGGIN_FILE_CLOSE(name) fclose(_logFile)



#ifdef _LOGGIN_FILE_OUT
	extern FILE* _logFile;
    #define _LOGGIN_OUT(level, name, fmt, ...) \
        fprintf(_logFile, "[[" level "] %s]: " fmt, name, ##__VA_ARGS__)
#else
    #define _LOGGIN_OUT(level, name, fmt, ...) \
        printf("[[" level "] %s]: " fmt, name, ##__VA_ARGS__)
#endif

#define LOGGIN_MODULE(name) \
    static const char* moduleName = #name; \
    \
    #if LOG_LEVEL >= LOGGIN_DEBUG \
        #define LOG_DBG(fmt, ...) _LOGGIN_OUT("DEBUG", moduleName, fmt, ##__VA_ARGS__) \
    #else \
        #define LOG_DBG(fmt, ...) \
    #endif \
    \
    #if LOG_LEVEL >= LOGGIN_INFO \
        #define LOG_INF(fmt, ...) _LOGGIN_OUT("INFO", moduleName, fmt, ##__VA_ARGS__) \
    #else \
        #define LOG_INF(fmt, ...) \
    #endif \
    \
    #if LOG_LEVEL >= LOGGIN_WARN \
        #define LOG_WRN(fmt, ...) _LOGGIN_OUT("WARN", moduleName, fmt, ##__VA_ARGS__) \
    #else \
        #define LOG_WRN(fmt, ...) \
    #endif \
    \
    #if LOG_LEVEL >= LOGGIN_ERROR \
        #define LOG_ERR(fmt, ...) _LOGGIN_OUT("ERROR", moduleName, fmt, ##__VA_ARGS__) \
    #else \
        #define LOG_ERR(fmt, ...) \
    #endif




#ifdef __cplusplus
}
#endif

#endif // LOGGIN_H




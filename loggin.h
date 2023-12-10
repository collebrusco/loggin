
#ifndef LOGGIN_H
#define LOGGIN_H

#ifdef __cplusplus
extern "C" {
#endif
#include <cstdint>
#include <stdio.h>
#include <stdarg.h>

#include "config.h"
#ifndef _LOGGIN_LEVEL
	#error "define log level & settings in config.h"
#endif

FILE* _loggin_get_file();
void loggin_file_close();
#ifdef LOGGIN_FILE_IMPL
	FILE* _loggin_get_file() {
		static FILE* _logFile = fopen(_LOGGIN_FILE, "w");
		return _logFile;
	}
	void loggin_file_close() {
		fclose(_loggin_get_file());
	}
#endif

#if _LOGGIN_USE_FILE == 1
    #define _LOGGIN_OUT(level, name, fmt, ...) \
        fprintf(_loggin_get_file(), "[(" level ") %s]: " fmt "\n", name, ##__VA_ARGS__)
#else
    #define _LOGGIN_OUT(level, name, fmt, ...) \
        printf("[(" level ") %s]: " fmt "\n", name, ##__VA_ARGS__)
#endif

#define LOGGIN_MODULE(name) static const char* moduleName = #name

#if _LOGGIN_LEVEL >= LOGGIN_DEBUG 
    #define LOG_DBG(fmt, ...) _LOGGIN_OUT("DEBUG", moduleName, fmt, ##__VA_ARGS__) 
#else 
    #define LOG_DBG(fmt, ...) 
#endif 

#if _LOGGIN_LEVEL >= LOGGIN_INFO 
    #define LOG_INF(fmt, ...) _LOGGIN_OUT("INFO ", moduleName, fmt, ##__VA_ARGS__) 
#else 
    #define LOG_INF(fmt, ...) 
#endif 

#if _LOGGIN_LEVEL >= LOGGIN_WARN 
    #define LOG_WRN(fmt, ...) _LOGGIN_OUT("WARN ", moduleName, fmt, ##__VA_ARGS__) 
#else 
    #define LOG_WRN(fmt, ...) 
#endif 

#if _LOGGIN_LEVEL >= LOGGIN_ERROR 
    #define LOG_ERR(fmt, ...) _LOGGIN_OUT("ERROR", moduleName, fmt, ##__VA_ARGS__) 
#else 
    #define LOG_ERR(fmt, ...) 
#endif




#ifdef __cplusplus
}
	#ifdef LOGGIN_FILE_IMPL
	class _loggin_cpp {
	public:
		~_loggin_cpp() {
			fclose(_loggin_get_file());
			printf("closed file\n");
		}
	};
	static _loggin_cpp _loggin_cpp_filemngr;
	#endif
#endif

#endif // LOGGIN_H




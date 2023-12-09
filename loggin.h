#ifdef __cplusplus
extern "C" {
#endif


#include "level_config.h"

#if LOGGIN_LOG_LEVEL == LOGGIN_NONE
	#define LOGGIN_MODULE_REGISTER(_NAME_) \
		#define dpre "[[DEBUG]:_NAME_]: " \
		#define ipre "[[INFO ]:_NAME_]: " \
		#define wpre "[[WARN ]:_NAME_]: " \
		#define epre "[[ERROR]:_NAME_]: " \
		#include <stdio.h> \
		#if LOGGIN_LOG_LEVEL >= LOGGIN_DEBUG \
		    #define LOG_DBG(fmt, ...) printf(dpre fmt, ##__VA_ARGS__) \
		#else \
		    #define LOG_DBG(fmt, ...) \
		#endif \
		#if LOGGIN_LOG_LEVEL >= LOGGIN_INFO \
		    #define LOG_INF(fmt, ...) printf(ipre fmt, ##__VA_ARGS__) \
		#else \
		    #define LOG_INF(fmt, ...) \
		#endif \
		#if LOGGIN_LOG_LEVEL >= LOGGIN_WARN \
		    #define LOG_WARN(fmt, ...) printf(wpre fmt, ##__VA_ARGS__) \
		#else \
		    #define LOG_WARN(fmt, ...) \
		#endif \
		#if LOGGIN_LOG_LEVEL >= LOGGIN_ERROR \
		    #define LOG_ERR(fmt, ...) printf(epre fmt, ##__VA_ARGS__) \
		#else \
		    #define LOG_ERR(fmt, ...) \
		#endif \
#else
	#define LOGGIN_MODULE_REGISTER(name)
#endif



#ifdef __cplusplus
}
#endif


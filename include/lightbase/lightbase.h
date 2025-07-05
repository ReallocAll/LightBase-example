#pragma once

#ifdef WIN32
#define LBAPI __declspec(dllexport)
#elif __linux__
#define LBAPI __attribute__((visibility("default")))
#endif

#define LOADER_VER_MAJOR 0
#define LOADER_VER_MINOR 1
#define LOADER_VER_PATCH 6
#define LOADER_VER_BUILD 2
#define LOADER_VER_STR "%d.%d.%d.%d"
#define LOADER_VER_STR_EXT "-Lasso_Lake-Dev_8"

#define LOADER_NAME "LightBase"
#define PLUGIN_DIR "plugins/"
#define PLUGIN_DEPS_DIR "plugin_deps/"

#define LEVEL_ERROR 0
#define LEVEL_WARN 1
#define LEVEL_INFO 2
#define LEVEL_DEBUG 3
#define LEVEL_TRACE 4

#ifndef LOG_LEVEL
#define LOG_LEVEL LEVEL_INFO
#endif

#if LEVEL_ERROR <= LOG_LEVEL
#define LB_PREINIT_LOGGER_ERROR(...) \
	lb_preinit_logger(LEVEL_ERROR, LOADER_NAME, __VA_ARGS__)
#else
#define LB_PREINIT_LOGGER_ERROR(...)
#endif

#if LEVEL_WARN <= LOG_LEVEL
#define LB_PREINIT_LOGGER_WARN(...) \
	lb_preinit_logger(LEVEL_WARN, LOADER_NAME, __VA_ARGS__)
#else
#define LB_PREINIT_LOGGER_WARN(...)
#endif

#if LEVEL_INFO <= LOG_LEVEL
#define LB_PREINIT_LOGGER_INFO(...) \
	lb_preinit_logger(LEVEL_INFO, LOADER_NAME, __VA_ARGS__)
#else
#define LB_PREINIT_LOGGER_INFO(...)
#endif

#if LEVEL_DEBUG <= LOG_LEVEL
#define LB_PREINIT_LOGGER_DEBUG(...) \
	lb_preinit_logger(LEVEL_DEBUG, LOADER_NAME, __VA_ARGS__)
#else
#define LB_PREINIT_LOGGER_DEBUG(...)
#endif

#if LEVEL_TRACE <= LOG_LEVEL
#define LB_PREINIT_LOGGER_TRACE(...) \
	lb_preinit_logger(LEVEL_TRACE, LOADER_NAME, __VA_ARGS__)
#else
#define LB_PREINIT_LOGGER_TRACE(...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

LBAPI int lb_preinit_logger(int in_level, const char *in_perfix, const char *in_fmt, ...);
LBAPI unsigned char *lb_get_base_addr();

#ifdef __cplusplus
}
#endif

///
///@file logger.h
///@author frityet
///@version 1.0.0
///


#pragma once

#include "common.h"
#include "utilities.h"
#include "string.h"

#ifndef LOG_BUFFER_SIZE
#define LOG_BUFFER_SIZE   1024
#endif

#define LOG_COLOUR_CODE_INFO    "\x1b[39m"
#define LOG_COLOUR_CODE_SUCCESS "\x1b[32m"
#define LOG_COLOUR_CODE_DEBUG   "\x1b[90;4m"
#define LOG_COLOUR_CODE_WARNING "\x1b[33m"
#define LOG_COLOUR_CODE_ERROR   "\x1b[91m"
#define LOG_COLOUR_CODE_FATAL   "\x1b[31;5;88m"
#define LOG_COLOUR_CODE_RESET   "\x1b[0m"

/*
enum LogType {
    LOG_TYPE_INFO,
    LOG_TYPE_SUCCESS,
    LOG_TYPE_DEBUG,
    LOG_TYPE_WARNING,
    LOG_TYPE_ERROR,
    LOG_TYPE_FATAL
};


ATTRIBUTE(used)
static string log_to_string(enum LogType logtype, const char *msg, int line, const char *file, const char *func)
{
    switch (logtype) {
        default:
        case LOG_TYPE_INFO: {
            fprintf(stdout, LOG_COLOUR_CODE_INFO "[%s:%d - %s] %s\n" LOG_COLOUR_CODE_RESET, file, line, func, msg);
            break;
        }
        case LOG_TYPE_SUCCESS: {
            fprintf(stdout, LOG_COLOUR_CODE_SUCCESS "[%s:%d - %s] %s\n" LOG_COLOUR_CODE_RESET, file, line, func, msg);
            break;
        }
        case LOG_TYPE_DEBUG: {
            fprintf(stdout, LOG_COLOUR_CODE_DEBUG "[%s:%d - %s] %s\n" LOG_COLOUR_CODE_RESET, file, line, func, msg);
            break;
        }
        case LOG_TYPE_WARNING: {
            fprintf(stdout, LOG_COLOUR_CODE_WARNING "[%s:%d - %s] %s\n" LOG_COLOUR_CODE_RESET, file, line, func, msg);
            break;
        }
        case LOG_TYPE_ERROR: {
            fprintf(stderr, LOG_COLOUR_CODE_ERROR "[%s:%d - %s] %s\n" LOG_COLOUR_CODE_RESET, file, line, func, msg);
            break;
        }
        case LOG_TYPE_FATAL: {
            fprintf(stderr, LOG_COLOUR_CODE_FATAL "[%s:%d - %s] %s\n" LOG_COLOUR_CODE_RESET, file, line, func, msg);
            break;
        }
    }
}

#define LOG_INFO(...)       ({ \
                                char _LOG_buf[LOG_BUFFER_SIZE]; \
                                snprintf(_LOG_buf, LOG_BUFFER_SIZE, __VA_ARGS__);     \
                                logbase(LOG_TYPE_INFO, _LOG_buf, __LINE__, __FILE__, __PRETTY_FUNCTION__);  \
                            })


#define LOG_SUCCESS(...)    ({ \
                                char _LOG_buf[LOG_BUFFER_SIZE]; \
                                snprintf(_LOG_buf, LOG_BUFFER_SIZE, __VA_ARGS__);     \
                                logbase(LOG_TYPE_SUCCESS, _LOG_buf, __LINE__, __FILE__, __PRETTY_FUNCTION__);\
                            })


#define LOG_DEBUG(...)      ({ \
                                char _LOG_buf[LOG_BUFFER_SIZE]; \
                                snprintf(_LOG_buf, LOG_BUFFER_SIZE, __VA_ARGS__);     \
                                logbase(LOG_TYPE_DEBUG, _LOG_buf, __LINE__, __FILE__, __PRETTY_FUNCTION__);\
                            })


#define LOG_WARNING(...)    ({ \
                                char _LOG_buf[LOG_BUFFER_SIZE]; \
                                snprintf(_LOG_buf, LOG_BUFFER_SIZE, __VA_ARGS__);     \
                                logbase(LOG_TYPE_WARNING, _LOG_buf, __LINE__, __FILE__, __PRETTY_FUNCTION__);\
                            })


#define LOG_ERROR(...)      ({ \
                                char _LOG_buf[LOG_BUFFER_SIZE]; \
                                snprintf(_LOG_buf, LOG_BUFFER_SIZE, __VA_ARGS__);     \
                                logbase(LOG_TYPE_ERROR, _LOG_buf, __LINE__, __FILE__, __PRETTY_FUNCTION__);\
                            })


#define LOG_FATAL(...)      ({ \
                                char _LOG_buf[LOG_BUFFER_SIZE]; \
                                snprintf(_LOG_buf, LOG_BUFFER_SIZE, __VA_ARGS__);     \
                                logbase(LOG_TYPE_FATAL, _LOG_buf, __LINE__, __FILE__, __PRETTY_FUNCTION__);\
                            })
*/

#define LOG_FORMAT(msg) str("["__FILE__":"STRINGIFY(__LINE__)"] " msg)

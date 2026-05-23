/* date = May 22nd 2026 8:25 pm */

#ifndef CORE_LOGGER_H
#define CORE_LOGGER_H

////////////////////////////////////////////////////////////////
//~ Sebas: Log Level Toggles

#ifndef LOG_WARN_ENABLED
# define LOG_WARN_ENABLED 1
#endif
#ifndef LOG_INFO_ENABLED
# define LOG_INFO_ENABLED 1
#endif
#ifndef LOG_DEBUG_ENABLED
# define LOG_DEBUG_ENABLED 1
#endif
#ifndef LOG_TRACE_ENABLED 
# define LOG_TRACE_ENABLED 1
#endif

#if BUILD_RELEASE
# define LOG_DEBUG_ENABLED 0
# define LOG_TRACE_ENABLED 0
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Log Levels 
typedef enum LogLevel
{
    LOG_LEVEL_FATAL   =  0,
    LOG_LEVEL_ERROR   =  1,
    LOG_LEVEL_WARN =  2,
    LOG_LEVEL_INFO    =  3,
    LOG_LEVEL_DEBUG   =  4,
    LOG_LEVEL_TRACE   =  5,
    LOG_LEVEL_COUNT,
    LOG_LEVEL_NULL = -1
} LogLevel;

////////////////////////////////////////////////////////////////
//~ Sebas: Log Fucntions 

function B8   init_loggingr();
function void shut_down_logging();

shared_function void log_output(LogLevel level, const char* message, ...);

#define SFATAL(msg, ...) log_output(LOG_LEVEL_FATAL , SVA_ARGS(msg, __VA_ARGS__))
#define SERROR(msg, ...) log_output(LOG_LEVEL_ERROR, SVA_ARGS(msg, __VA_ARGS__))

#if LOG_WARN_ENABLED
# define SWARN(msg, ...) log_output(LOG_LEVEL_WARN, SVA_ARGS(msg, __VA_ARGS__))
#else
# define SWARN(msg, ...)
#endif

#if LOG_INFO_ENABLED
# define SINFO(msg, ...) log_output(LOG_LEVEL_INFO, SVA_ARGS(msg, __VA_ARGS__))
#else
# define SINFO(msg, ...)
#endif

#if LOG_DEBUG_ENABLED
# define SDEBUG(msg, ...) log_output(LOG_LEVEL_DEBUG, SVA_ARGS(msg, __VA_ARGS__))
#else
# define SDEBUG(msg, ...)
#endif

#if LOG_TRACE_ENABLED
# define STRACE(msg, ...) log_output(LOG_LEVEL_TRACE, SVA_ARGS(msg, __VA_ARGS__))
#else
# define STRACE(msg, ...)
#endif

#endif //CORE_LOGGER_H
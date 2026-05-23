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
    LOG_LEVEL_WARN    =  2,
    LOG_LEVEL_INFO    =  3,
    LOG_LEVEL_DEBUG   =  4,
    LOG_LEVEL_TRACE   =  5,
    LOG_LEVEL_COUNT,
} LogLevel;

////////////////////////////////////////////////////////////////
//~ Sebas: Log Fucntions 

function B8   init_loggingr();
function void shut_down_logging();

shared_function void log_output(LogLevel level, const char* message, ...);

#define SFATAL(msg, ...) log_output(LOG_LEVEL_FATAL , SVA_ARGS(msg, __VA_ARGS__))
#define SFATAL_LIT(msg) SFATAL("%s", msg)
#define SERROR(msg, ...) log_output(LOG_LEVEL_ERROR, SVA_ARGS(msg, __VA_ARGS__))
#define SERROR_LIT(msg) SERROR("%s", msg)

#if LOG_WARN_ENABLED
# define SWARN(msg, ...) log_output(LOG_LEVEL_WARN, SVA_ARGS(msg, __VA_ARGS__))
# define SWARN_LIT(msg) SWARN("%s", msg)
#else
# define SWARN(msg, ...)
# define SWARN_LIT(msg)
#endif

#if LOG_INFO_ENABLED
# define SINFO(msg, ...) log_output(LOG_LEVEL_INFO, SVA_ARGS(msg, __VA_ARGS__))
# define SINFO_LIT(msg) SINFO("%s", msg)
#else
# define SINFO(msg, ...)
# define SINFO_LIT(msg)
#endif

#if LOG_DEBUG_ENABLED
# define SDEBUG(msg, ...) log_output(LOG_LEVEL_DEBUG, SVA_ARGS(msg, __VA_ARGS__))
# define SDEBUG_LIT(msg) SDEBUG("%s", msg)
#else
# define SDEBUG(msg, ...)
# define SDEBUG_LIT(msg)
#endif

#if LOG_TRACE_ENABLED
# define STRACE(msg, ...) log_output(LOG_LEVEL_TRACE, SVA_ARGS(msg, __VA_ARGS__))
# define STRACE_LIT(msg) STRACE("%s", msg)
#else
# define STRACE(msg, ...)
# define STRACE_LIT(msg)
#endif




#endif //CORE_LOGGER_H
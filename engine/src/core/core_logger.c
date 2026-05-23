////////////////////////////////////////////////////////////////
//~ Sebas: Log Functions

function B8   
init_loggingr()
{
    // TODO(Sebas): Create a log file.
    return TRUE;
}
function void 
shut_down_logging()
{
    // TODO(Sebas): Cleanup logging/write queued entries.
}

void 
log_output(LogLevel level, const char* message, ...)
{
    Assert(level >= LOG_LEVEL_FATAL && level < LOG_LEVEL_COUNT);
    local const char* log_level_strings[] = 
    {
        "[FATAL]: ", 
        "[ERROR]: ",
        "[WARN]: ",
        "[INFO]: ",
        "[DEBUG]: ",
        "[TRACE]: ",
    };
    // B8 is_error = level < 2 && level >= 0;
    StaticAssert(ArrayCount(log_level_strings) == LOG_LEVEL_COUNT, "Invalid size of LogLevel char array!");
    //S32 size = 32000;
    char out_message[32000] = {};
    //MemoryZero(out_message, size);
    
    va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);
    
    char out_message2[32000] = {};
    sprintf(out_message2, "%s%s\n", log_level_strings[level], out_message);
    printf("%s", out_message2);
}


void 
report_assertion_failure(const char* expression, const char* message, const char* file, S32 line)
{
    SFATAL("Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}

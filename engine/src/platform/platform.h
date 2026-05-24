/* date = May 23rd 2026 9:07 am */

#ifndef PLATFORM_H
#define PLATFORM_H

////////////////////////////////////////////////////////////////
//~ Sebas: Platfrom Types

typedef struct PlatformState PlatformState;

typedef struct PlatformHandle PlatformHandle;
struct PlatformHandle
{
    PlatformState* state;
};

typedef struct TimeStamp TimeStamp;
struct TimeStamp
{
#if PLATFORM_WINDOWS
    U64 win32_counter;
#else
    
#endif
};

////////////////////////////////////////////////////////////////
//~ Sebas: Platform Macros

//#define MemoryReserve(size) platform_memory_reserve(size)
//#define MemoryCommit(ptr, size) platform_memory_commit(ptr, size)
//#define MemoryDecommit(ptr, size) platform_memory_decommit(ptr, size)
//#define MemoryFree(ptr) platform_memory_reserve(ptr)


////////////////////////////////////////////////////////////////
//~ Sebas: Platform Functions 

function B8    platform_startup(PlatformHandle* platform_handle, const char* app_name, S32 x, S32 y, S32 width, S32 height);
function void  platform_shutdown(PlatformHandle platform_handle);

function B8    platform_pump_messages(PlatformHandle platform_handle);

function void* platform_memory_reserve(U64 size);
function void  platform_memory_commit(void* ptr, U64 size);
function void  platform_memory_decommit(void* ptr, U64 size);
function void  platform_free(void* ptr);

function void  platform_console_write(const char* message, U8 colour);
function void  platform_console_write_error(const char* message, U8 colour);

function TimeStamp platform_create_time_stamp();
function F64   platform_get_elapsed_seconds(TimeStamp start, TimeStamp end);
function F64   platform_get_absolute_time();

function void  platform_sleep(U64 ms);

#endif //PLATFORM_H

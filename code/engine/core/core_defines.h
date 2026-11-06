/* date = November 5th 2026 10:46 am */

#ifndef CORE_DEFINES_H
#define CORE_DEFINES_H

////////////////////////////////////////////////////////////////
//~ Sebas: Core Types 

#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef float    f32;
typedef double   f64;

typedef s32      b32;
typedef s8       b8;

#define TRUE 1
#define FALSE 0

////////////////////////////////////////////////////////////////
//~ Sebas: Linking Keywords 

#if LANG_CPP
# define no_name_mangle extern "C"
#else
# define no_name_mangle
#endif

#if COMPILER_MSVC
# define sidus_import no_name_mangle __declspec(dllimport)
# define sidus_export no_name_mangle __declspec(dllexport)
#else
# define sidus_import no_name_mangle 
# define sidus_export no_name_mangle __attribute__((visibility("default")))
#endif

#ifdef BUILD_DLL
# define sidus_api sidus_export
#else
# define sidus_api no_name_mangle sidus_import
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Codebas Keywords

#define global        static
#define function      static
#define local_persist static

////////////////////////////////////////////////////////////////
//~ Sebas: Helper Macros

#define Stmnt(S) do{ S }while(0)

#define Stringify_(S) #S
#define Stringify(S) Stringify_(S)
#define Glue_(A,B) A##B
#define Glue(A,B) Glue_(A,B)

#if !defined(AssertBreak)
# define AssertBreak()
#endif

#if defined(__clang__) || defined(__gcc__)

#else

#endif




#endif //CORE_DEFINES_H

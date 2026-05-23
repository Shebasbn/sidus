/* date = May 22nd 2026 0:21 pm */

#ifndef CORE_BASE_H
#define CORE_BASE_H

////////////////////////////////////////////////////////////////
//~ Sebas: Third-Party Includes

#include <stdint.h>
// TODO(Sebas): temporary?
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#if COMPILER_MSVC && PLATFORM_WINDOWS
# include <intrin.h>
#endif


////////////////////////////////////////////////////////////////
//~ Sebas: Base Types

typedef int8_t   S8; 
typedef int16_t  S16;
typedef int32_t  S32;
typedef int64_t  S64;
typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef S8       B8;
typedef S16      B16;
typedef S32      B32;
typedef S64      B64;
typedef float    F32;
typedef double   F64;
typedef void VoidFunction(void);

////////////////////////////////////////////////////////////////
//~ Sebas: Linking Keywords

#if LANG_CPP
# define no_name_mangle extern "C"
#else
# define no_name_mangle
#endif

#define root_global no_name_mangle
#define root_function no_name_mangle function

#ifdef SIDUS_EXPORT
# if COMPILER_MSVC
#  define shared_function no_name_mangle __declspec(dllexport)
# else
#  define shared_function no_name_mangle __attribute__((visibility("default")))
# endif
#else
# if COMPILER_MSVC
#  define shared_function no_name_mangle __declspec(dllimport)
# else
#  define shared_function
# endif
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Codebase Keywords

#define global static
#define local static
#define function static 


#if COMPILER_MSVC && COMPILER_MSVC_YEAR < 2015
# define inline_function static
#else
# define inline_function inline static
#endif

#if COMPILER_MSVC || (COMPILER_CLANG && PLATFORM_WINDOWS)
# pragma section(".rdata$", read)
# define read_only __declspec(allocate(".rdata$"))
#elif (COMPILER_CLANG && PLATFORM_LINUX)
# define read_only __attribute__((section(".rodata")))
#else
# define read_only 
#endif

#if COMPILER_GCC || COMPILER_CLANG
# define SVA_ARGS(fmt, ...) fmt, ##__VA_ARGS__
#else
# define SVA_ARGS(fmt, ...) fmt, __VA_ARGS__
#endif

#define Stmnt(stmnt) do { stmnt } while(0)
#define TRUE 1
#define FALSE 0


////////////////////////////////////////////////////////////////
//~ Sebas: Memory Operations

#define MemoryCopy(dst, src, size) memcpy((dst), (src), (size))
#define MemoryMove(dst, src, size) memmove((dst), (src), (size))
#define MemorySet(dst, byte, size) memset((dst), (byte), (size))

#define MemoryCopyStruct(dst, src) Stmnt(Assert(sizeof(*(dst)) == sizeof(*(src)));\
MemoryCopy((dst), (src), sizeof(*(dst)));)
#define MemoryCopyArray(dst, src) Stmnt(Assert(sizeof(dst) == sizeof(src)); MemoryCopy((dst), (src), (src)))

#define MemoryZero(ptr, size) MemorySet((ptr), 0, (size))
#define MemoryZeroStruct(ptr) MemoryZero((ptr), sizeof(*(ptr)))
#define MemoryZeroArray(arr) MemoryZero((arr), sizeof(arr))

////////////////////////////////////////////////////////////////
//~ Sebas: Compiler Silencing

#define UnusedVariable(name) (void)name

////////////////////////////////////////////////////////////////
//~ Sebas: Arrays/Pointers/Integers

#define ArrayCount(arr) (sizeof(arr) / sizeof(*(arr)))
#define IntFromPtr(ptr) (U64)(((U8*)ptr) - 0)
#define PtrFromInt(n) (void*)(((U8*)0) + n)

#endif //CORE_BASE_H
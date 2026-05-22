/* date = May 22nd 2026 0:57 pm */

#ifndef BASE_CTX_CRACK_H
#define BASE_CTX_CRACK_H

////////////////////////////////////////////////////////////////
//~ Sebas: Compiler

#if defined(_MSC_VER)
# define S_COMPILER_MSVC 1

# if _MSC_VER >= 1920
#  define S_COMPILER_MSVC_YEAR 2019
# elif _MSC_VER >= 1910
#  define S_COMPILER_MSVC_YEAR 2017
# elif _MSC_VER >= 1900
#  define S_COMPILER_MSVC_YEAR 2015
# elif _MSC_VER >= 1800
#  define S_COMPILER_MSVC_YEAR 2013
# elif _MSC_VER >= 1700
#  define S_COMPILER_MSVC_YEAR 2012
# elif _MSC_VER >= 1600
#  define S_COMPILER_MSVC_YEAR 2010
# elif _MSC_VER >= 1500
#  define S_COMPILER_MSVC_YEAR 2008
# elif _MSC_VER >= 1400
#  define S_COMPILER_MSVC_YEAR 2005
# else
#  define S_COMPILER_MSVC_YEAR 0
# endif

#elif defined(__clang__)
# define S_COMPILER_CLANG 1
#elif defined(__GNUC__)
# define S_COMPILER_GCC 1
#else
# error "Can't find current compiler!"
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Platform 

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
# define S_PLATFORM_WINDOWS 1
# ifndef _WIN64
#  error "64-bit is required on Windows!"
# endif
#elif defined(__linux__) || defined(__gnu__linux__)
# define S_PLATFORM_LINUX 1 
# if defined(__ANDROID__)
#  define S_PLATORM_ANDROID 1
# endif
#elif defined(__unix__)
# define S_PLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
# define S_PLATFORM_POSIX 1
#elif defined(__APPLE__) 
# define S_PLATFORM_APPLE 1
# include <TargetConditionals.h>
# if TARGET_IPHONE_SIMULATOR
#  define S_PLATFORM_IOS 1
#  define S_PLATFORM_IOS_SIM 1
# elif TARGET_OS_IPHONE
#  define S_PLATFORM_IOS 1
# elif TARGET_OS_MAC
# else
#  error "Unknown Apple platform"
# endif
#else
# error "Unknown Platform!"
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Architecture

#if defined(__amd64__) || defined(_M_AMD64)
# define S_ARCH_X64 1
#elif defined(_M_IX86) || defined(__i386__)
# define S_ARCH_X86 1
#elif defined(__arm__) || defined(_M_ARM)
# define S_ARCH_ARM 1
#elif defined(__aarch64__)
# define S_ARCH_ARM64 1
#else
# error missing ARCH detection
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Language

#if defined(__cplusplus)
# define S_LANG_CPP
#else
# define S_LANG_C
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Zero

#if !defined(S_ARCH_X64)
# define S_ARCH_X64 0
#endif
#if !defined(S_ARCH_X86)
# define S_ARCH_X86 0
#endif
#if !defined(S_ARCH_ARM64)
# define S_ARCH_ARM64 0
#endif
#if !defined(S_ARCH_ARM)
# define S_ARCH_ARM 0
#endif
#if !defined(S_COMPILER_MSVC)
# define S_COMPILER_MSVC 0
#endif
#if !defined(S_COMPILER_GCC)
# define S_COMPILER_GCC 0
#endif
#if !defined(S_COMPILER_CLANG)
# define S_COMPILER_CLANG 0
#endif
#if !defined(S_PLATFORM_WINDOWS)
# define S_PLATFORM_WINDOWS 0
#endif
#if !defined(S_PLATFORM_LINUX)
# define S_PLATFORM_LINUX 0
#endif
#if !defined(S_PLATFORM_ANDROID)
# define S_PLATFORM_ANDROID 0
#endif
#if !defined(S_PLATFORM_UNIX)
# define S_PLATFORM_UNIX 0
#endif
#if !defined(S_PLATFORM_POSIX)
# define S_PLATFORM_POSIX 0
#endif
#if !defined(S_PLATFORM_APPLE)
# define S_PLATFORM_APPLE 0
#endif
#if !defined(S_PLATFORM_IOS)
# define S_PLATFORM_IOS 0
#endif
#if !defined(S_PLATFORM_IOS_SIM)
# define S_PLATFORM_IOS_SIM 0
#endif
#if !defined(S_LANG_CPP)
# define S_LANG_CPP 0
#endif
#if !defined(S_LANG_C)
# define S_LANG_C 0
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Build Parameters 

#if !defined(S_BUILD_DEBUG)
# define S_BUILD_DEBUG 1
#endif

#if !defined(S_BUILD_SUPPLEMENTARY_UNIT)
# define S_BUILD_SUPPLEMENTARY_UNIT 0
#endif

#if !defined(S_BUILD_ENTRY_POINT_DEFINING_UNIT)
# define S_BUILD_ENTRY_POINT_DEFINING_UNIT !BUILD_SUPPLEMENTARY_UNIT
#endif

#if !defined(S_BUILD_COMMAND_LINE_INTERFACE)
# define S_BUILD_COMMAND_LINE_INTERFACE 0
#endif

#if !defined(S_BUILD_TELEMETRY)
# define S_BUILD_TELEMETRY 0
#endif


#ifdef S_EXPORT
# if S_COMPILER_MSVC
#  define SAPI __declspec(dllexport)
# else
#  define SAPI __attribute__((visibility("default")))
# endif
#else
# if S_COMPILER_MSVC
#  define SAPI __declspec(dllimport)
# else
#  define SAPI
# endif
#endif


#endif //BASE_CTX_CRACK_H

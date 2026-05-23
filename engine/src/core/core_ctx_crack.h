/* date = May 22nd 2026 0:57 pm */

#ifndef CORE_CTX_CRACK_H
#define CORE_CTX_CRACK_H

////////////////////////////////////////////////////////////////
//~ Sebas: Compiler

#if defined(_MSC_VER)
# define COMPILER_MSVC 1

# if _MSC_VER >= 1920
#  define COMPILER_MSVC_YEAR 2019
# elif _MSC_VER >= 1910
#  define COMPILER_MSVC_YEAR 2017
# elif _MSC_VER >= 1900
#  define COMPILER_MSVC_YEAR 2015
# elif _MSC_VER >= 1800
#  define COMPILER_MSVC_YEAR 2013
# elif _MSC_VER >= 1700
#  define COMPILER_MSVC_YEAR 2012
# elif _MSC_VER >= 1600
#  define COMPILER_MSVC_YEAR 2010
# elif _MSC_VER >= 1500
#  define COMPILER_MSVC_YEAR 2008
# elif _MSC_VER >= 1400
#  define COMPILER_MSVC_YEAR 2005
# else
#  define COMPILER_MSVC_YEAR 0
# endif

#elif defined(__clang__)
# define COMPILER_CLANG 1
#elif defined(__GNUC__)
# define COMPILER_GCC 1
#else
# error "Can't find current compiler!"
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Platform 

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
# define PLATFORM_WINDOWS 1
# ifndef _WIN64
#  error "64-bit is required on Windows!"
# endif
#elif defined(__linux__) || defined(__gnu__linux__)
# define PLATFORM_LINUX 1 
# if defined(__ANDROID__)
#  define PLATORM_ANDROID 1
# endif
#elif defined(__unix__)
# define PLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
# define PLATFORM_POSIX 1
#elif defined(__APPLE__) 
# define PLATFORM_APPLE 1
# include <TargetConditionals.h>
# if TARGET_IPHONE_SIMULATOR
#  define PLATFORM_IOS 1
#  define PLATFORM_IOSIM 1
# elif TARGET_OIPHONE
#  define PLATFORM_IOS 1
# elif TARGET_OMAC
# else
#  error "Unknown Apple platform"
# endif
#else
# error "Unknown Platform!"
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Architecture

#if defined(__amd64__) || defined(_M_AMD64)
# define ARCH_X64 1
#elif defined(_M_IX86) || defined(__i386__)
# define ARCH_X86 1
#elif defined(__arm__) || defined(_M_ARM)
# define ARCH_ARM 1
#elif defined(__aarch64__)
# define ARCH_ARM64 1
#else
# error missing ARCH detection
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Language

#if defined(__cplusplus)
# define LANG_CPP 1
#else
# define LANG_C 1
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Zero

#if !defined(ARCH_X64)
# define ARCH_X64 0
#endif
#if !defined(ARCH_X86)
# define ARCH_X86 0
#endif
#if !defined(ARCH_ARM64)
# define ARCH_ARM64 0
#endif
#if !defined(ARCH_ARM)
# define ARCH_ARM 0
#endif
#if !defined(COMPILER_MSVC)
# define COMPILER_MSVC 0
#endif
#if !defined(COMPILER_GCC)
# define COMPILER_GCC 0
#endif
#if !defined(COMPILER_CLANG)
# define COMPILER_CLANG 0
#endif
#if !defined(PLATFORM_WINDOWS)
# define PLATFORM_WINDOWS 0
#endif
#if !defined(PLATFORM_LINUX)
# define PLATFORM_LINUX 0
#endif
#if !defined(PLATFORM_ANDROID)
# define PLATFORM_ANDROID 0
#endif
#if !defined(PLATFORM_UNIX)
# define PLATFORM_UNIX 0
#endif
#if !defined(PLATFORM_POSIX)
# define PLATFORM_POSIX 0
#endif
#if !defined(PLATFORM_APPLE)
# define PLATFORM_APPLE 0
#endif
#if !defined(PLATFORM_IOS)
# define PLATFORM_IOS 0
#endif
#if !defined(PLATFORM_IOSIM)
# define PLATFORM_IOSIM 0
#endif
#if !defined(LANG_CPP)
# define LANG_CPP 0
#endif
#if !defined(LANG_C)
# define LANG_C 0
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: Build Parameters 

#if !defined(BUILD_DEBUG)
# define BUILD_DEBUG 1
#endif

#if !defined(BUILD_RELEASE)
# define BUILD_RELEASE 0
#endif

#if !defined(BUILD_SUPPLEMENTARY_UNIT)
# define BUILD_SUPPLEMENTARY_UNIT 0
#endif

#if !defined(BUILD_ENTRY_POINT_DEFINING_UNIT)
# define BUILD_ENTRY_POINT_DEFINING_UNIT !BUILD_SUPPLEMENTARY_UNIT
#endif

#if !defined(BUILD_COMMAND_LINE_INTERFACE)
# define BUILD_COMMAND_LINE_INTERFACE 0
#endif

#if !defined(BUILD_TELEMETRY)
# define BUILD_TELEMETRY 0
#endif

#ifdef SIDUS_IMPORT
# undef SIDUS_EXPORT
#endif



#endif //CORE_CTX_CRACK_H

/* date = May 23rd 2026 0:56 am */

#ifndef CORE_ASSERT_H
#define CORE_ASSERT_H

////////////////////////////////////////////////////////////////
//~ Sebas: Assert Flag and Debug Break

#ifndef ASSERTS_ENABLED 
# define ASSERTS_ENABLED 1
#endif

#if ASSERTS_ENABLED

# if PLATFORM_WINDOWS && COMPILER_MSVC
#  define DebugBreak() __debugbreak()
# elif COMPILER_GCC 
#  define DebugBreak() __builtin_trap()
# else
#  define DebugBreak() (*(volatile int*)0 = 0)
# endif

////////////////////////////////////////////////////////////////
//~ Sebas: Assert Body Function 

shared_function void report_assertion_failure(const char* expression, const char* message, const char* file, S32 line);

# define AssertBody_(c, msg) Stmnt(if(!(c)){                                                \
report_assertion_failure(#c, msg, __FILE__, __LINE__); \
DebugBreak();})


# define AssertAllways(c) AssertBody_(c, "")
# define AssertAllwaysMsg(c, msg) AssertBody_(c, msg)

# undef Assert
# if BUILD_DEBUG
#  define Assert(c) AssertBody_(c, "")
#  define AssertMsg(c, msg) AssertBody_(c, msg)
# else
#  define Assert(c) 
#  define AssertMsg(c, msg)
# endif

# define StaticBreak_(c, label) static_assert(c, label)

# undef StaticAssert
# if !BUILD_SUPPLEMENTARY_UNIT
#  define StaticAssert(c, label) StaticBreak_(c, label)
# else
#  define StaticAssert(c, label) 
# endif

#else

# define AssertAllways(c) 
# define AssertAllwaysMsg(c, msg) 
# define Assert(c)
# define AssertMsg(c, msg))
# define StaticAssert(c, label)

#endif
#endif //CORE_ASSERT_H

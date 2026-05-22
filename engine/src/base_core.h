/* date = May 22nd 2026 0:21 pm */

#ifndef BASE_CORE_H
#define BASE_CORE_H

////////////////////////////////////////////////////////////////
//~ Sebas: Third-Party Includes

#include <stdint.h>
/*#include <TargetConditionals.h>*/

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
//~ Sebas: Assertions

#if S_PLATFORM_WINDOWS
# define DebugBreak() __debugbreak()
#else
# define DebugBreak() (*(volatile int*)0 = 0)
#endif

#define AssertAllways(b) do { if(!(b)) { DebugBreak():  }} while(0)

#undef Assert
#if S_BUILD_DEBUG
# define Assert(b)  do { if(!(b)) { DebugBreak():  }} while(0)
#else
# define Assert(b)  ((void)(b))
#endif

#undef StaticAssert
#if !S_BUILD_SUPPLEMENTARY_UNIT
# define StaticAssert(c, label) U8 static_assert_##label[(c)?(1):(-1)]
#else
# define StaticAssert(c, label) 
#endif

////////////////////////////////////////////////////////////////
//~ Sebas: 

#endif //BASE_CORE_H
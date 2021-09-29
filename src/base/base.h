#ifndef BASE_H
#define BASE_H

#include <stdint.h>
#include <assert.h>

// NOTE: Operating Systems defines
#ifdef _WIN32
    #define PLATFORM_WIN32
#elif __linux__
    #define PLATFORM_LINUX
#endif

#ifdef PLATFORM_WIN32
    #define COMET __declspec(dllexport)
#elif PLATFORM_LINUX
    #define COMET 
#endif

#ifdef _DEBUG
    #define ASSERT(value) assert((value))
#else
    #define ASSERT(value)
#endif

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef int8_t  b8;
typedef int32_t  b32;

#define true (1)
#define false (0)

#endif // BASE_H

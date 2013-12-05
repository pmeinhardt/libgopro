#ifndef INCLUDE_GOPRO_COMMON_H
#define INCLUDE_GOPRO_COMMON_H

#include <stdlib.h>

// C++ compatibility.

#ifdef __cplusplus
#define GOPRO_BEGIN_DECL extern "C" {
#define GOPRO_END_DECL   }
#else
#define GOPRO_BEGIN_DECL // empty
#define GOPRO_END_DECL   // empty
#endif

// Declare a public function exported for application use.

#if __GNUC__ >= 4
#define GOPRO_EXTERN(type) extern \
                         __attribute__((visibility("default"))) \
                         type
#elif defined(_MSC_VER)
#define GOPRO_EXTERN(type) __declspec(dllexport) type
#else
#define GOPRO_EXTERN(type) extern type
#endif

// Declare a function as always inlined.

#if defined(_MSC_VER)
#define GOPRO_INLINE(type) static __inline type
#else
#define GOPRO_INLINE(type) static inline type
#endif

#endif

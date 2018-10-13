// Library export macro
#ifdef _WIN32

#if defined(LIBTECH_EXPORTS)

#define LIBTECH_API extern "C" __declspec(dllexport)
#define LIBTECH_CLASS __declspec(dllexport)

#elif defined(LIBTECH_LOADDLL)

#define LIBTECH_API extern "C" __declspec(dllimport)
#define LIBTECH_CLASS __declspec(dllimport)

#else

#define LIBTECH_API extern "C"
#define LIBTECH_CLASS __declspec(dllexport)

#endif

#else
#define LIBTECH_API
#define LIBTECH_CLASS

#endif

#ifdef linux

// NDEBUG is set by GCC when in release mode
#if !defined(NDEBUG)
#define _DEBUG
#endif


#endif


// Common include
#include "libtypes.h"
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
#define LIBTECH_CLASS __declspec(dllimport)

#endif

#else
#define LIBTECH_API
#define LIBTECH_CLASS

#endif


// Common include
#include "libtypes.h"
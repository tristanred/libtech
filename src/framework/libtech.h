// Library export macro
#ifdef _WIN32

#if defined(LIBTECH_EXPORTS)

#define LIBTECH_API extern "C" __declspec(dllexport)

#elif defined(LIBTECH_LOADDLL)

#define LIBTECH_API extern "C" __declspec(dllimport)

#else

#define LIBTECH_API

#endif

#else
#define LIBTECH_API
#endif


// Common include
#include "types/libtypes.h"
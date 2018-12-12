/*
 * This file creates 2 export definitions :
 * - SuperSlotsSupport_API is for exported functions that are not part of a class.
 *     Example usage = "SuperSlotsSupport_API int MyFunction(int one, int two);"
 *
 * - SuperSlotsSupport_CLASS is for exported classes. Only the class typename needs to be given the attribute
 *     Example usage = "class SuperSlotsSupport_CLASS MyClass { }"
 *
 * Marking functions and classes with these defines will allow then to be called from a DLL. If the project
 * is compiled as a DLL, only the marked functions can be called from outside.
 *
 * This file checks multiple definitions, if SuperSlotsSupport_EXPORTS is defined that means the compiling project
 * aims to export those members. If SuperSlotsSupport_LOADDLL is defined, that means the compiling project aims
 * to import the members and call them. Not sure why but even when it isn't defined we can still call the 
 * functions.
 *
 * On Linux, apparently we don't need any of that, ELF format FTW.
*/

// Library export macro
#ifdef _WIN32

#if defined(SuperSlotsSupport_EXPORTS)

#define SuperSlotsSupport_API extern "C" __declspec(dllexport)
#define SuperSlotsSupport_CLASS __declspec(dllexport)

#elif defined(SuperSlotsSupport_LOADDLL)

#define SuperSlotsSupport_API extern "C" __declspec(dllimport)
#define SuperSlotsSupport_CLASS __declspec(dllimport)

#else

#define SuperSlotsSupport_API extern "C"
#define SuperSlotsSupport_CLASS __declspec(dllexport)

#endif

#else
#define SuperSlotsSupport_API
#define SuperSlotsSupport_CLASS

#endif

#ifdef linux

// NDEBUG is set by GCC when in release mode
#if !defined(NDEBUG)
#define _DEBUG
#endif


#endif

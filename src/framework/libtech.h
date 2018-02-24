#ifdef LIBTECH_EXPORTS  
#define LIBTECH_API __declspec(dllexport)
#else  
#define LIBTECH_API __declspec(dllimport)
#endif  

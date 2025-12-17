#ifndef VICOLIBGLOBAL_H
#define VICOLIBGLOBAL_H
#ifdef __cplusplus
	#if !defined(SAG_COM) && (!defined(WINAPI_FAMILY) || WINAPI_FAMILY==WINAPI_FAMILY_DESKTOP_APP) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(_WIN32))
		#  define OS_WIN32
	#endif
	#ifdef OS_WIN32
		#if defined(VICOLIB_LIBRARY)
		#  define VICOLIB_API __declspec(dllexport)
		#else
		#  define VICOLIB_API __declspec(dllimport)
		#endif
	#else
		#define VICOLIB_API
	#endif
#else
	#define VICOLIB_API
#endif
#endif // VICOLIBGLOBAL_H

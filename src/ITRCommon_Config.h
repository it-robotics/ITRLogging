#pragma once

#ifdef _WIN32

#ifdef ITR_COMMON_SHARED_EXPORTS
	#define ITR_COMMON_SHARED_API __declspec(dllexport)
#else
	#define ITR_COMMON_SHARED_API __declspec(dllimport)
#endif

#elif __GNUC__

#ifdef ITR_COMMON_SHARED_EXPORTS
	#define ITR_COMMON_SHARED_API __attribute__ ((visibility ("default")))
#else
	#define ITR_COMMON_SHARED_API
#endif

#endif

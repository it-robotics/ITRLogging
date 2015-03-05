#pragma once

#ifdef _MSC_VER

#ifdef ITR_COMMON_SHARED_EXPORTS
  #define ITR_COMMON_SHARED_API __declspec(dllexport)
#else
  #define ITR_COMMON_SHARED_API __declspec(dllimport)
#endif

#elif __GNUC__

#define ITR_COMMON_SHARED_API __attribute__ ((visibility ("default")))

#endif

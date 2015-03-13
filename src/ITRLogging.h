// Copyright (c) 2014 IT+Robotics Srl
// Copyright (c) 2015 Francesco Pretto
// This file is subject to the Apache License, Version 2.0

#pragma once

#include "libsdefs.h"

#ifdef __cplusplus

#include <string>

namespace ITR
{
  ITR_COMMON_SHARED_API std::string DemangleTypeName(const char *name);

  class ITR_COMMON_SHARED_API LoggingInit
  {
  public:
    LoggingInit();
  };

  extern ITR_COMMON_SHARED_API LoggingInit __LoggingInitObj;
}

#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef void * HLOGGER;

ITR_COMMON_SHARED_API HLOGGER NewITRLogger(const char* name);
ITR_COMMON_SHARED_API void FreeITRLogger(HLOGGER logger);
ITR_COMMON_SHARED_API void ITRLogVisualization(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API void ITRLogFlow(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API void ITRLogMoreDetail(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API void ITRLogDetail(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API void ITRLogWarn(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API void ITRLogError(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API void ITRLogVisualizationForced(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API void ITRLogFlowForced(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API void ITRLogMoreDetailForced(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API void ITRLogDetailForced(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API void ITRLogWarnForced(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API void ITRLogErrorForced(HLOGGER logger, const char* message);
ITR_COMMON_SHARED_API int ITREnabledVisualization(HLOGGER logger);
ITR_COMMON_SHARED_API int ITREnabledFlow(HLOGGER logger);
ITR_COMMON_SHARED_API int ITREnabledMoreDetail(HLOGGER logger);
ITR_COMMON_SHARED_API int ITREnabledDetail(HLOGGER logger);
ITR_COMMON_SHARED_API int ITREnabledWarn(HLOGGER logger);
ITR_COMMON_SHARED_API int ITREnabledError(HLOGGER logger);

#ifdef __cplusplus
}
#endif

#ifdef ITR_LOG_DISABLED

#define ITR_DECLARE_GLOBAL_LOGGER(logger)
#define ITR_DEFINE_GLOBAL_LOGGER(logger)
#define ITR_DEFINE_STATIC_LOGGER(logger)

#define __ITR_GET_LOGGER_0() logger
#define __ITR_GET_LOGGER_1(logger) logger

#define __ITR_LOG_VISUALIZATION_FORCED_ACTUAL __ITR_LOG_DISABLED
#define __ITR_LOG_FLOW_FORCED_ACTUAL __ITR_LOG_DISABLED
#define __ITR_LOG_MOREDETAIL_FORCED_ACTUAL __ITR_LOG_DISABLED
#define __ITR_LOG_DETAIL_FORCED_ACTUAL __ITR_LOG_DISABLED
#define __ITR_LOG_WARN_FORCED_ACTUAL __ITR_LOG_DISABLED
#define __ITR_LOG_ERROR_FORCED_ACTUAL __ITR_LOG_DISABLED

#define __ITR_LOG_DISABLED(logger, message)

#define __ITR_ENABLED_VISUALIZATION_ACTUAL(logger) false
#define __ITR_ENABLED_FLOW_ACTUAL(logger) false
#define __ITR_ENABLED_MOREDETAIL_ACTUAL(logger) false
#define __ITR_ENABLED_DETAIL_ACTUAL(logger) false
#define __ITR_ENABLED_WARN_ACTUAL(logger) false
#define __ITR_ENABLED_ERROR_ACTUAL(logger) false

#elif defined(__cplusplus) & !defined(ITR_LOGGING_C)

// Logger getter macros
#include <string>
#include <typeinfo>
#include "xlogger.h"

static inline log4cxx::XLoggerPtr __getITRLogger(const char *logger)
{
  return log4cxx::XLogger::getLogger(logger);
};

#define ITR_DECLARE_GLOBAL_LOGGER(name) \
  extern log4cxx::XLoggerPtr p_LocalLogger;\
  inline static log4cxx::XLoggerPtr & __getITRLogger()\
  {\
    return p_LocalLogger;\
  };\

#define ITR_DEFINE_GLOBAL_LOGGER(name) \
  log4cxx::XLoggerPtr p_LocalLogger = log4cxx::XLogger::getLogger(name);

#define ITR_DEFINE_STATIC_LOGGER(name) \
  static log4cxx::XLoggerPtr p_LocalLogger = log4cxx::XLogger::getLogger(name);\
  inline static log4cxx::XLoggerPtr & __getITRLogger()\
  {\
    return p_LocalLogger;\
  };

#define ITR_DECLARE_CLASS_LOGGER(typeinfo) \
  class ITRClassLogger\
  {\
  public:\
    log4cxx::LoggerPtr p_Logger;\
    ITRClassLogger()\
    {\
      std::string type = ::ITR::DemangleTypeName(typeid(typeinfo).name());\
      p_Logger = log4cxx::XLogger::getLogger(type);\
    }\
  };\
  static ITRClassLogger __ITRLogger;\
  static inline log4cxx::XLoggerPtr & __getITRLogger()\
  {\
    return __ITRLogger.p_Logger;\
  };

#define ITR_DEFINE_CLASS_LOGGER(typeinfo) \
  typeinfo::ITRClassLogger typeinfo::__ITRLogger;

#define __ITR_GET_LOGGER_0() __getITRLogger()
#define __ITR_GET_LOGGER_1(logger) __getITRLogger(logger)

// Log and test macros
#define __ITR_LOG_VISUALIZATION_FORCED_ACTUAL(logger, message, freemsg) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getVisualization(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define __ITR_LOG_FLOW_FORCED_ACTUAL(logger, message, freemsg) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getFlow(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define __ITR_LOG_MOREDETAIL_FORCED_ACTUAL(logger, message, freemsg) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getMoreDetail(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define __ITR_LOG_DETAIL_FORCED_ACTUAL(logger, message, freemsg) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getDetail(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define __ITR_LOG_WARN_FORCED_ACTUAL(logger, message, freemsg) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getWarn(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define __ITR_LOG_ERROR_FORCED_ACTUAL(logger, message, freemsg) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getError(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define __ITR_ENABLED_VISUALIZATION_ACTUAL(logger) logger->isVisualizationEnabled()
#define __ITR_ENABLED_FLOW_ACTUAL(logger) logger->isFlowEnabled()
#define __ITR_ENABLED_MOREDETAIL_ACTUAL(logger) logger->isMoreDetailEnabled()
#define __ITR_ENABLED_DETAIL_ACTUAL(logger) logger->isDetailEnabled()
#define __ITR_ENABLED_WARN_ACTUAL(logger) logger->isWarnEnabled()
#define __ITR_ENABLED_ERROR_ACTUAL(logger) logger->isErrorEnabled()

#else // ITR_LOGGING_C

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Eval functions

inline static int __evalITRLog1(int (*fun)(HLOGGER), HLOGGER logger, const char *name)
{
  if (logger == NULL)
  {
    logger = NewITRLogger(name);
    int ret = fun(logger);
    FreeITRLogger(logger);
    return ret;
  }

   return fun(logger);
}

inline static void __evalITRLog2(void (*fun)(HLOGGER, const char*), HLOGGER logger,
                          const char *name, const char *message, int freemsg)
{
  if (logger == NULL)
  {
    logger = NewITRLogger(name);
    fun(logger, message);
    FreeITRLogger(logger);
  }

  fun(logger, message);
  if (freemsg)
    free((char *)message);
}

inline static char * __evalITRStr(const char *format, ...)
{
  va_list list;
  va_start (list, format);
  size_t size = vsprintf(NULL, format, list);
  va_end(list);

  char *ret = (char *)malloc(size + 1);

  va_start (list, format);
  vsprintf(ret, format, list);
  va_end(list);

  return ret;
}

#define __LSTR_1(string) string, 0, 0
#define __LSTR_2(format, _1) __evalITRStr(format, _1), 1, 1
#define __LSTR_3(format, _1, _2) __evalITRStr(format, _1, _2), 1, 1
#define __LSTR_4(format, _1, _2, _3) __evalITRStr(format, _1, _2, _3), 1, 1
#define __LSTR_5(format, _1, _2, _3, _4) __evalITRStr(format, _1, _2, _3, _4), 1, 1
#define __LSTR_6(format, _1, _2, _3, _4, _5) __evalITRStr(format, _1, _2, _3, _4, _5), 1, 1
#define __LSTR_7(format, _1, _2, _3, _4, _5, _6) __evalITRStr(format, _1, _2, _3, _4, _5, _6), 1, 1
#define __LSTR_8(format, _1, _2, _3, _4, _5, _6, _7) __evalITRStr(format, _1, _2, _3, _4, _5, _6, _7), 1, 1
#define __LSTR_9(format, _1, _2, _3, _4, _5, _6, _7, _8) __evalITRStr(format, _1, _2, _3, _4, _5, _6, _7, _8), 1, 1
#define __LSTR_10(format, _1, _2, _3, _4, _5, _6, _7, _8, _9) __evalITRStr(format, _1, _2, _3, _4, _5, _6, _7, _8, _9), 1, 1
#define __LSTR_11(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) __evalITRStr(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), 1, 1
#define __LSTR_12(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) __evalITRStr(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), 1, 1
#define __LSTR_13(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) __evalITRStr(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), 1, 1
#define __LSTR_14(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) __evalITRStr(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), 1, 1
#define __LSTR_15(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) __evalITRStr(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), 1, 1
#define __LSTR_16(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) __evalITRStr(format, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), 1, 1
#define _LSTR(...) ITR_EXPAND(ITR_CONCAT(__LSTR_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))

// Logger getter macros
#define ITR_DECLARE_GLOBAL_LOGGER(name) \
  extern HLOGGER __ITRLogger;\
  inline static HLOGGER __getITRLogger()\
  {\
    return __ITRLogger;\
  };

#define ITR_DEFINE_GLOBAL_LOGGER(name) \
  HLOGGER __ITRLogger;

#define ITR_INIT_GLOBAL_LOGGER(name)\
  __ITRLogger = NewITRLogger(name);

#define ITR_DESTROY_GLOBAL_LOGGER(logger)\
  FreeITRLogger(__ITRLogger);

#define __ITR_GET_LOGGER_0() __getITRLogger(), NULL
#define __ITR_GET_LOGGER_1(name) NULL, name

// Log and test macros
#define __ITR_ENABLED_VISUALIZATION_ACTUAL(logger, name) __evalITRLog1(ITREnabledVisualization, logger, name)
#define __ITR_ENABLED_FLOW_ACTUAL(logger, name) __evalITRLog1(ITREnabledFlow, logger, name)
#define __ITR_ENABLED_MOREDETAIL_ACTUAL(logger, name) __evalITRLog1(ITREnabledMoreDetail, logger, name)
#define __ITR_ENABLED_DETAIL_ACTUAL(logger, name) __evalITRLog1(ITREnabledDetail, logger, name)
#define __ITR_ENABLED_WARN_ACTUAL(logger, name) __evalITRLog1(ITREnabledWarn, logger, name)
#define __ITR_ENABLED_ERROR_ACTUAL(logger, name) __evalITRLog1(ITREnabledError, logger, name)

#define __ITR_LOG_VISUALIZATION_FORCED_ACTUAL(logger, name, message, freemsg) \
  __evalITRLog2(ITRLogVisualizationForced, logger, name, message, freemsg);

#define __ITR_LOG_FLOW_FORCED_ACTUAL(logger, name, message, freemsg) \
  __evalITRLog2(ITRLogFlowForced, logger, name, message, freemsg);

#define __ITR_LOG_MOREDETAIL_FORCED_ACTUAL(logger, name, message, freemsg) \
  __evalITRLog2(ITRLogMoreDetailForced, logger, name, message, freemsg);

#define __ITR_LOG_DETAIL_FORCED_ACTUAL(logger, name, message, freemsg) \
  __evalITRLog2(ITRLogDetailForced, logger, name, message, freemsg);

#define __ITR_LOG_WARN_FORCED_ACTUAL(logger, name, message, freemsg) \
  __evalITRLog2(ITRLogWarnForced, logger, name, message, freemsg);

#define __ITR_LOG_ERROR_FORCED_ACTUAL(logger, name, message, freemsg) \
  __evalITRLog2(ITRLogErrorForced, logger, name, message, freemsg);

// Counted macros for log macros with variadic arguments
// ex. ITR_LOG_DETAIL(logger, _LSTR(format, ...))
#define __ITR_LOG_VISUALIZATION_4(logger, message, freemsg, dummy) __ITR_LOG_VISUALIZATION_GENERIC(__ITR_GET_LOGGER(logger), message, freemsg)
#define __ITR_LOG_FLOW_4(logger, message, freemsg, dummy) __ITR_LOG_FLOW_GENERIC(__ITR_GET_LOGGER(logger), message, freemsg)
#define __ITR_LOG_MOREDETAIL_4(logger, message, freemsg, dummy) __ITR_LOG_MOREDETAIL_GENERIC(__ITR_GET_LOGGER(logger), message, freemsg)
#define __ITR_LOG_DETAIL_4(logger, message, freemsg, dummy) __ITR_LOG_DETAIL_GENERIC(__ITR_GET_LOGGER(logger), message, freemsg)
#define __ITR_LOG_WARN_4(logger, message, freemsg, dummy) __ITR_LOG_WARN_GENERIC(__ITR_GET_LOGGER(logger), message, freemsg)
#define __ITR_LOG_ERROR_4(logger, message, freemsg, dummy) __ITR_LOG_ERROR_GENERIC(__ITR_GET_LOGGER(logger), message, freemsg)

#define __ITR_LOG_VISUALIZATION_3(message, freemsg, dummy) __ITR_LOG_VISUALIZATION_GENERIC(__ITR_GET_LOGGER(), message, freemsg)
#define __ITR_LOG_FLOW_3(message, freemsg, dummy) __ITR_LOG_FLOW_GENERIC(__ITR_GET_LOGGER(), message, freemsg)
#define __ITR_LOG_MOREDETAIL_3(message, freemsg, dummy) __ITR_LOG_MOREDETAIL_GENERIC(__ITR_GET_LOGGER(), message, freemsg)
#define __ITR_LOG_DETAIL_3(message, freemsg, dummy) __ITR_LOG_DETAIL_GENERIC(__ITR_GET_LOGGER(), message, freemsg)
#define __ITR_LOG_WARN_3(message, freemsg, dummy) __ITR_LOG_WARN_GENERIC(__ITR_GET_LOGGER(), message, freemsg)
#define __ITR_LOG_ERROR_3(message, freemsg, dummy) __ITR_LOG_ERROR_GENERIC(__ITR_GET_LOGGER(), message, freemsg)

#define __ITR_LOG_VISUALIZATION_FORCED_4(logger, message, freemsg, dummy) __ITR_LOG_VISUALIZATION_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, freemsg)
#define __ITR_LOG_FLOW_FORCED_4(logger, message, freemsg, dummy) __ITR_LOG_FLOW_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, freemsg)
#define __ITR_LOG_MOREDETAIL_FORCED_4(logger, message, freemsg, dummy) __ITR_LOG_MOREDETAIL_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, freemsg)
#define __ITR_LOG_DETAIL_FORCED_4(logger, message, freemsg, dummy) __ITR_LOG_DETAIL_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, freemsg)
#define __ITR_LOG_WARN_FORCED_4(logger, message, freemsg, dummy) __ITR_LOG_WARN_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, freemsg)
#define __ITR_LOG_ERROR_FORCED_4(logger, message, freemsg, dummy) __ITR_LOG_ERROR_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, freemsg)

#define __ITR_LOG_VISUALIZATION_FORCED_3(message, freemsg, dummy) __ITR_LOG_VISUALIZATION_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, freemsg)
#define __ITR_LOG_FLOW_FORCED_3(message, freemsg, dummy) __ITR_LOG_FLOW_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, freemsg)
#define __ITR_LOG_MOREDETAIL_FORCED_3(message, freemsg, dummy) __ITR_LOG_MOREDETAIL_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, freemsg)
#define __ITR_LOG_DETAIL_FORCED_3(message, freemsg, dummy) __ITR_LOG_DETAIL_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, freemsg)
#define __ITR_LOG_WARN_FORCED_3(message, freemsg, dummy) __ITR_LOG_WARN_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, freemsg)
#define __ITR_LOG_ERROR_FORCED_3(message, freemsg, dummy) __ITR_LOG_ERROR_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, freemsg)

#endif

#define ITR_QUOTE(arg) #arg
#define ITR_EXPAND_AND_QUOTE(x) ITR_QUOTE(x)
#define ITR_EXPAND(x) x
#define __ITR_CONCAT(x, y) x ## y
#define ITR_CONCAT(x, y) __ITR_CONCAT(x, y)
#define ITR_AUGMENTER(...) unused, __VA_ARGS__

#ifdef __GNUC__

#define ITR_TUPLE_SIZE(...) __ITR_TUPLE_SIZE(0, ## __VA_ARGS__, 32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#define __ITR_TUPLE_SIZE(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,N,...) N

#endif // __GNUC__

#ifdef _MSC_VER

#define __ITR_TUPLE_SIZE(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,VAL,...) VAL
#define ITR_TUPLE_SIZE_1(...) ITR_EXPAND(__ITR_TUPLE_SIZE(__VA_ARGS__,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
#define ITR_TUPLE_SIZE(...) ITR_TUPLE_SIZE_1(ITR_AUGMENTER(__VA_ARGS__))

#endif // _MSC_VER

#ifdef __cplusplus

#define ITR_FUNC_DESC_BEGIN_STR __FUNCTION__ << " Begins"
#define ITR_FUNC_DESC_END_STR __FUNCTION__ << " Ends"

#else // C

#define ITR_FUNC_DESC_BEGIN_STR __FUNCTION__ " Begins"
#define ITR_FUNC_DESC_END_STR __FUNCTION__ " Ends"

#endif

// Private common macros
#define __ITR_ENABLED_VISUALIZATION_GENERIC(logger)\
  __ITR_ENABLED_VISUALIZATION_ACTUAL(logger)

#define __ITR_ENABLED_FLOW_GENERIC(logger)\
  __ITR_ENABLED_FLOW_ACTUAL(logger)

#define __ITR_ENABLED_MOREDETAIL_GENERIC(logger)\
  __ITR_ENABLED_MOREDETAIL_ACTUAL(logger)

#define __ITR_ENABLED_DETAIL_GENERIC(logger)\
  __ITR_ENABLED_DETAIL_ACTUAL(logger)

#define __ITR_ENABLED_WARN_GENERIC(logger)\
  __ITR_ENABLED_WARN_ACTUAL(logger)

#define __ITR_ENABLED_ERROR_GENERIC(logger)\
  __ITR_ENABLED_ERROR_ACTUAL(logger)

#define __ITR_LOG_VISUALIZATION_GENERIC(logger, message, freemsg) do {\
  if (__ITR_ENABLED_VISUALIZATION_ACTUAL(logger)) {\
    __ITR_LOG_VISUALIZATION_FORCED_ACTUAL(logger, message, freemsg);\
  }} while (0)

#define __ITR_LOG_FLOW_GENERIC(logger, message, freemsg) do {\
  if (__ITR_ENABLED_FLOW_ACTUAL(logger)) {\
    __ITR_LOG_FLOW_FORCED_ACTUAL(logger, message, freemsg);\
  }} while (0)

#define __ITR_LOG_MOREDETAIL_GENERIC(logger, message, freemsg) do {\
  if (__ITR_ENABLED_MOREDETAIL_ACTUAL(logger)) {\
    __ITR_LOG_MOREDETAIL_FORCED_ACTUAL(logger, message, freemsg);\
  }} while (0)

#define __ITR_LOG_DETAIL_GENERIC(logger, message, freemsg) do {\
  if (__ITR_ENABLED_DETAIL_ACTUAL(logger)) {\
    __ITR_LOG_DETAIL_FORCED_ACTUAL(logger, message, freemsg);\
  }} while (0)

#define __ITR_LOG_WARN_GENERIC(logger, message, freemsg) do {\
  if (__ITR_ENABLED_WARN_ACTUAL(logger)) {\
    __ITR_LOG_WARN_FORCED_ACTUAL(logger, message, freemsg);\
  }} while (0)

#define __ITR_LOG_ERROR_GENERIC(logger, message, freemsg) do {\
  if (__ITR_ENABLED_ERROR_ACTUAL(logger)) {\
    __ITR_LOG_ERROR_FORCED_ACTUAL(logger, message, freemsg);\
  }} while (0)

// Private counted macros
#define __ITR_GET_LOGGER(...) ITR_EXPAND(ITR_CONCAT(__ITR_GET_LOGGER_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))

#define __ITR_LOG_FLOW_BEGIN_1(logger) __ITR_LOG_FLOW_GENERIC(__ITR_GET_LOGGER(logger), ITR_FUNC_DESC_BEGIN_STR, 0)
#define __ITR_LOG_FLOW_END_1(logger) __ITR_LOG_FLOW_GENERIC(__ITR_GET_LOGGER(logger), ITR_FUNC_DESC_END_STR, 0)

#define __ITR_LOG_FLOW_BEGIN_0() __ITR_LOG_FLOW_GENERIC(__ITR_GET_LOGGER(), ITR_FUNC_DESC_BEGIN_STR, 0)
#define __ITR_LOG_FLOW_END_0() __ITR_LOG_FLOW_GENERIC(__ITR_GET_LOGGER(), ITR_FUNC_DESC_END_STR, 0)

#define __ITR_LOG_VISUALIZATION_2(logger, message) __ITR_LOG_VISUALIZATION_GENERIC(__ITR_GET_LOGGER(logger), message, 0)
#define __ITR_LOG_FLOW_2(logger, message) __ITR_LOG_FLOW_GENERIC(__ITR_GET_LOGGER(logger), message, 0)
#define __ITR_LOG_MOREDETAIL_2(logger, message) __ITR_LOG_MOREDETAIL_GENERIC(__ITR_GET_LOGGER(logger), message, 0)
#define __ITR_LOG_DETAIL_2(logger, message) __ITR_LOG_DETAIL_GENERIC(__ITR_GET_LOGGER(logger), message, 0)
#define __ITR_LOG_WARN_2(logger, message) __ITR_LOG_WARN_GENERIC(__ITR_GET_LOGGER(logger), message, 0)
#define __ITR_LOG_ERROR_2(logger, message) __ITR_LOG_ERROR_GENERIC(__ITR_GET_LOGGER(logger), message, 0)

#define __ITR_LOG_VISUALIZATION_1(message) __ITR_LOG_VISUALIZATION_GENERIC(__ITR_GET_LOGGER(), message, 0)
#define __ITR_LOG_FLOW_1(message) __ITR_LOG_FLOW_GENERIC(__ITR_GET_LOGGER(), message, 0)
#define __ITR_LOG_MOREDETAIL_1(message) __ITR_LOG_MOREDETAIL_GENERIC(__ITR_GET_LOGGER(), message, 0)
#define __ITR_LOG_DETAIL_1(message) __ITR_LOG_DETAIL_GENERIC(__ITR_GET_LOGGER(), message, 0)
#define __ITR_LOG_WARN_1(message) __ITR_LOG_WARN_GENERIC(__ITR_GET_LOGGER(), message, 0)
#define __ITR_LOG_ERROR_1(message) __ITR_LOG_ERROR_GENERIC(__ITR_GET_LOGGER(), message, 0)

#define __ITR_LOG_VISUALIZATION_FORCED_2(logger, message) __ITR_LOG_VISUALIZATION_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, 0)
#define __ITR_LOG_FLOW_FORCED_2(logger, message) __ITR_LOG_FLOW_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, 0)
#define __ITR_LOG_MOREDETAIL_FORCED_2(logger, message) __ITR_LOG_MOREDETAIL_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, 0)
#define __ITR_LOG_DETAIL_FORCED_2(logger, message) __ITR_LOG_DETAIL_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, 0)
#define __ITR_LOG_WARN_FORCED_2(logger, message) __ITR_LOG_WARN_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, 0)
#define __ITR_LOG_ERROR_FORCED_2(logger, message) __ITR_LOG_ERROR_FORCED_ACTUAL(__ITR_GET_LOGGER(logger), message, 0)

#define __ITR_LOG_VISUALIZATION_FORCED_1(message) __ITR_LOG_VISUALIZATION_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, 0)
#define __ITR_LOG_FLOW_FORCED_1(message) __ITR_LOG_FLOW_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, 0)
#define __ITR_LOG_MOREDETAIL_FORCED_1(message) __ITR_LOG_MOREDETAIL_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, 0)
#define __ITR_LOG_DETAIL_FORCED_1(message) __ITR_LOG_DETAIL_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, 0)
#define __ITR_LOG_WARN_FORCED_1(message) __ITR_LOG_WARN_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, 0)
#define __ITR_LOG_ERROR_FORCED_1(message) __ITR_LOG_ERROR_FORCED_ACTUAL(__ITR_GET_LOGGER(), message, 0)

#define __ITR_ENABLED_VISUALIZATION_1(logger) __ITR_ENABLED_VISUALIZATION_GENERIC(__ITR_GET_LOGGER(logger))
#define __ITR_ENABLED_FLOW_1(logger) __ITR_ENABLED_FLOW_GENERIC(__ITR_GET_LOGGER(logger))
#define __ITR_ENABLED_MOREDETAIL_1(logger) __ITR_ENABLED_MOREDETAIL_GENERIC(__ITR_GET_LOGGER(logger))
#define __ITR_ENABLED_DETAIL_1(logger) __ITR_ENABLED_DETAIL_GENERIC(__ITR_GET_LOGGER(logger))
#define __ITR_ENABLED_WARN_1(logger) __ITR_ENABLED_WARN_GENERIC(__ITR_GET_LOGGER(logger))
#define __ITR_ENABLED_ERROR_1(logger) __ITR_ENABLED_ERROR_GENERIC(__ITR_GET_LOGGER(logger))

#define __ITR_ENABLED_VISUALIZATION_0() __ITR_ENABLED_VISUALIZATION_GENERIC(__ITR_GET_LOGGER())
#define __ITR_ENABLED_FLOW_0() __ITR_ENABLED_FLOW_GENERIC(__ITR_GET_LOGGER())
#define __ITR_ENABLED_MOREDETAIL_0() __ITR_ENABLED_MOREDETAIL_GENERIC(__ITR_GET_LOGGER())
#define __ITR_ENABLED_DETAIL_0() __ITR_ENABLED_DETAIL_GENERIC(__ITR_GET_LOGGER())
#define __ITR_ENABLED_WARN_0() __ITR_ENABLED_WARN_GENERIC(__ITR_GET_LOGGER())
#define __ITR_ENABLED_ERROR_0() __ITR_ENABLED_ERROR_GENERIC(__ITR_GET_LOGGER())

// Public macros
#define ITR_LOG_FLOW_BEGIN(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_FLOW_BEGIN_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_FLOW_END(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_FLOW_END_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))

#define ITR_LOG_VISUALIZATION(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_VISUALIZATION_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_FLOW(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_FLOW_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_MOREDETAIL(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_MOREDETAIL_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_DETAIL(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_DETAIL_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_WARN(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_WARN_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_ERROR(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_ERROR_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))

#define ITR_ENABLED_VISUALIZATION(...) ITR_EXPAND(ITR_CONCAT(__ITR_ENABLED_VISUALIZATION_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_ENABLED_FLOW(...) ITR_EXPAND(ITR_CONCAT(__ITR_ENABLED_FLOW_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_ENABLED_MOREDETAIL(...) ITR_EXPAND(ITR_CONCAT(__ITR_ENABLED_MOREDETAIL_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_ENABLED_DETAIL(...) ITR_EXPAND(ITR_CONCAT(__ITR_ENABLED_DETAIL_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_ENABLED_WARN(...) ITR_EXPAND(ITR_CONCAT(__ITR_ENABLED_WARN_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_ENABLED_ERROR(...) ITR_EXPAND(ITR_CONCAT(__ITR_ENABLED_ERROR_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))

#define ITR_LOG_VISUALIZATION_FORCED(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_VISUALIZATION_FORCED_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_FLOW_FORCED(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_FLOW_FORCED_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_MOREDETAIL_FORCED(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_MOREDETAIL_FORCED_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_DETAIL_FORCED(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_DETAIL_FORCED_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_WARN_FORCED(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_WARN_FORCED_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_ERROR_FORCED(...) ITR_EXPAND(ITR_CONCAT(__ITR_LOG_ERROR_FORCED_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))

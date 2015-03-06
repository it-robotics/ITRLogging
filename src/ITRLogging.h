// Copyright (c) 2014 IT+Robotics Srl
// Copyright (c) 2015 Francesco Pretto
// This file is subject to the Apache License, Version 2.0

#pragma once

#include "ITRCommon_Config.h"

#ifdef ITR_LOG4XX_ABSENT

// TODO

#define ITR_ENABLED_VISUALIZATION_ACTUAL(logger) true
#define ITR_ENABLED_FLOW_ACTUAL(logger) true
#define ITR_ENABLED_MOREDETAIL_ACTUAL(logger) true
#define ITR_ENABLED_DETAIL_ACTUAL(logger) true
#define ITR_ENABLED_WARN_ACTUAL(logger) true
#define ITR_ENABLED_ERROR_ACTUAL(logger) true

#else // ITR_LOG4XX_PRESENT

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

#define ITR_GET_LOGGER_0() logger
#define ITR_GET_LOGGER_1(logger) logger

#define __ITR_LOG_DISABLED(logger, message)

#define ITR_LOG_VISUALIZATION_FORCED __ITR_LOG_DISABLED
#define ITR_LOG_FLOW_FORCED __ITR_LOG_DISABLED
#define ITR_LOG_MOREDETAIL_FORCED __ITR_LOG_DISABLED
#define ITR_LOG_DETAIL_FORCED __ITR_LOG_DISABLED
#define ITR_LOG_WARN_FORCED __ITR_LOG_DISABLED
#define ITR_LOG_ERROR_FORCED __ITR_LOG_DISABLED

#define ITR_ENABLED_VISUALIZATION_ACTUAL(logger) false
#define ITR_ENABLED_FLOW_ACTUAL(logger) false
#define ITR_ENABLED_MOREDETAIL_ACTUAL(logger) false
#define ITR_ENABLED_DETAIL_ACTUAL(logger) false
#define ITR_ENABLED_WARN_ACTUAL(logger) false
#define ITR_ENABLED_ERROR_ACTUAL(logger) false

#elif defined(__cplusplus) & !defined(ITR_LOGGING_C)

// Logger getter macros
#include <string>
#include <typeinfo>
#include "xlogger.h"

#define ITR_GET_LOGGER_0() __getITRLogger()
#define ITR_GET_LOGGER_1(logger) __getITRLogger(logger)

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

// Log and test macros
#define ITR_LOG_VISUALIZATION_FORCED(logger, message) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getVisualization(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define ITR_LOG_FLOW_FORCED(logger, message) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getFlow(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define ITR_LOG_MOREDETAIL_FORCED(logger, message) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getMoreDetail(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define ITR_LOG_DETAIL_FORCED(logger, message) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getDetail(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define ITR_LOG_WARN_FORCED(logger, message) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getWarn(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define ITR_LOG_ERROR_FORCED(logger, message) \
  ::log4cxx::helpers::MessageBuffer oss_; \
  logger->forcedLog(::log4cxx::XLevel::getError(), oss_.str(oss_ << message), LOG4CXX_LOCATION)

#define ITR_ENABLED_VISUALIZATION_ACTUAL(logger) logger->isVisualizationEnabled()
#define ITR_ENABLED_FLOW_ACTUAL(logger) logger->isFlowEnabled()
#define ITR_ENABLED_MOREDETAIL_ACTUAL(logger) logger->isMoreDetailEnabled()
#define ITR_ENABLED_DETAIL_ACTUAL(logger) logger->isDetailEnabled()
#define ITR_ENABLED_WARN_ACTUAL(logger) logger->isWarnEnabled()
#define ITR_ENABLED_ERROR_ACTUAL(logger) logger->isErrorEnabled()

#else // ITR_LOGGING_C

#include <string.h>
#include <stdlib.h>

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

// Logger getter macros
#define ITR_GET_LOGGER_0() __getITRLogger(), NULL
#define ITR_GET_LOGGER_1(logger) NULL, logger

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

// Log and test macros
#define ITR_ENABLED_VISUALIZATION_ACTUAL(logger) __evalITRLog1(ITREnabledVisualization, logger)
#define ITR_ENABLED_FLOW_ACTUAL(logger) __evalITRLog1(ITREnabledFlow, logger)
#define ITR_ENABLED_MOREDETAIL_ACTUAL(logger) __evalITRLog1(ITREnabledMoreDetail, logger)
#define ITR_ENABLED_DETAIL_ACTUAL(logger) __evalITRLog1(ITREnabledDetail, logger)
#define ITR_ENABLED_WARN_ACTUAL(logger) __evalITRLog1(ITREnabledWarn, logger)
#define ITR_ENABLED_ERROR_ACTUAL(logger) __evalITRLog1(ITREnabledError, logger)

#define ITR_LOG_VISUALIZATION_FORCED(logger, message) \
  __evalITRLog2(ITRLogVisualizationForced, logger, message);

#define ITR_LOG_FLOW_FORCED(logger, message) \
  __evalITRLog2(ITRLogFlowForced, logger, message);

#define ITR_LOG_MOREDETAIL_FORCED(logger, message) \
  __evalITRLog2(ITRLogMoreDetailForced, logger, message);

#define ITR_LOG_DETAIL_FORCED(logger, message) \
  __evalITRLog2(ITRLogDetailForced, logger, message);

#define ITR_LOG_WARN_FORCED(logger, message) \
  __evalITRLog2(__evalITRLog2, ITRLogWarnForced(logger, message);

#define ITR_LOG_ERROR_FORCED(logger, message) \
  __evalITRLog2(ITRLogErrorForced, logger, message);

#endif

#endif // ITR_LOG4XX_ABSENT

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

#define ITR_LOG_VISUALIZATION_GENERIC(logger, message) do {\
  if (ITR_ENABLED_VISUALIZATION_ACTUAL(logger)) {\
    ITR_LOG_VISUALIZATION_FORCED(logger, message);\
  }} while (0)

#define ITR_LOG_FLOW_GENERIC(logger, message) do {\
  if (ITR_ENABLED_FLOW_ACTUAL(logger)) {\
    ITR_LOG_FLOW_FORCED(logger, message);\
  }} while (0)

#define ITR_LOG_MOREDETAIL_GENERIC(logger, message) do {\
  if (ITR_ENABLED_MOREDETAIL_ACTUAL(logger)) {\
    ITR_LOG_MOREDETAIL_FORCED(logger, message);\
  }} while (0)

#define ITR_LOG_DETAIL_GENERIC(logger, message) do {\
  if (ITR_ENABLED_DETAIL_ACTUAL(logger)) {\
    ITR_LOG_DETAIL_FORCED(logger, message);\
  }} while (0)

#define ITR_LOG_WARN_GENERIC(logger, message) do {\
  if (ITR_ENABLED_WARN_ACTUAL(logger)) {\
    ITR_LOG_WARN_FORCED(logger, message);\
  }} while (0)

#define ITR_LOG_ERROR_GENERIC(logger, message) do {\
  if (ITR_ENABLED_ERROR_ACTUAL(logger)) {\
    ITR_LOG_ERROR_FORCED(logger, message);\
  }} while (0)

#define ITR_GET_LOGGER(...) ITR_EXPAND(ITR_CONCAT(ITR_GET_LOGGER_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))

#define ITR_LOG_VISUALIZATION_2(logger, message) ITR_LOG_VISUALIZATION_GENERIC(ITR_GET_LOGGER(logger), message)
#define ITR_LOG_FLOW_BEGIN_1(logger) ITR_LOG_FLOW_GENERIC(ITR_GET_LOGGER(logger), ITR_FUNC_DESC_BEGIN_STR)
#define ITR_LOG_FLOW_END_1(logger) ITR_LOG_FLOW_GENERIC(ITR_GET_LOGGER(logger), ITR_FUNC_DESC_END_STR)
#define ITR_LOG_FLOW_2(logger, message) ITR_LOG_FLOW_GENERIC(ITR_GET_LOGGER(logger), message)
#define ITR_LOG_MOREDETAIL_2(message, logger) ITR_LOG_MOREDETAIL_GENERIC(ITR_GET_LOGGER(logger), message)
#define ITR_LOG_DETAIL_2(message, logger) ITR_LOG_DETAIL_GENERIC(ITR_GET_LOGGER(logger), message)
#define ITR_LOG_WARN_2(message, logger) ITR_LOG_WARN_GENERIC(ITR_GET_LOGGER(logger), message)
#define ITR_LOG_ERROR_2(message, logger) ITR_LOG_ERROR_GENERIC(ITR_GET_LOGGER(logger), message)

#define ITR_LOG_VISUALIZATION_1(message) ITR_LOG_VISUALIZATION_GENERIC(ITR_GET_LOGGER(), message)
#define ITR_LOG_FLOW_BEGIN_0() ITR_LOG_FLOW_GENERIC(ITR_GET_LOGGER(), ITR_FUNC_DESC_BEGIN_STR)
#define ITR_LOG_FLOW_END_0() ITR_LOG_FLOW_GENERIC(ITR_GET_LOGGER(), ITR_FUNC_DESC_END_STR)
#define ITR_LOG_FLOW_1(message) ITR_LOG_FLOW_GENERIC(ITR_GET_LOGGER(), message)
#define ITR_LOG_MOREDETAIL_1(message) ITR_LOG_MOREDETAIL_GENERIC(ITR_GET_LOGGER(), message)
#define ITR_LOG_DETAIL_1(message) ITR_LOG_DETAIL_GENERIC(ITR_GET_LOGGER(), message)
#define ITR_LOG_WARN_1(message) ITR_LOG_WARN_GENERIC(ITR_GET_LOGGER(), message)
#define ITR_LOG_ERROR_1(message) ITR_LOG_ERROR_GENERIC(ITR_GET_LOGGER(), message)

#define ITR_ENABLED_VISUALIZATION_1(logger) ITR_ENABLED_VISUALIZATION_ACTUAL(ITR_GET_LOGGER(logger))
#define ITR_ENABLED_FLOW_1(logger) ITR_ENABLED_FLOW_ACTUAL(ITR_GET_LOGGER(logger))
#define ITR_ENABLED_MOREDETAIL_1(logger) ITR_ENABLED_MOREDETAIL_ACTUAL(ITR_GET_LOGGER(logger))
#define ITR_ENABLED_DETAIL_1(logger) ITR_ENABLED_DETAIL_ACTUAL(ITR_GET_LOGGER(logger))
#define ITR_ENABLED_WARN_1(logger) ITR_ENABLED_WARN_ACTUAL(ITR_GET_LOGGER(logger))
#define ITR_ENABLED_ERROR_1(logger) ITR_ENABLED_ERROR_ACTUAL(ITR_GET_LOGGER(logger))

#define ITR_ENABLED_VISUALIZATION_0() ITR_ENABLED_VISUALIZATION_ACTUAL(ITR_GET_LOGGER())
#define ITR_ENABLED_FLOW_0() ITR_ENABLED_FLOW_ACTUAL(ITR_GET_LOGGER())
#define ITR_ENABLED_MOREDETAIL_0() ITR_ENABLED_MOREDETAIL_ACTUAL(ITR_GET_LOGGER())
#define ITR_ENABLED_DETAIL_0() ITR_ENABLED_DETAILACTUAL(ITR_GET_LOGGER())
#define ITR_ENABLED_WARN_0() ITR_ENABLED_WARN_ACTUAL(ITR_GET_LOGGER())
#define ITR_ENABLED_ERROR_0() ITR_ENABLED_ERROR_GENERIC(ITR_GET_LOGGER())

#define ITR_LOG_VISUALIZATION(...) ITR_EXPAND(ITR_CONCAT(ITR_LOG_VISUALIZATION_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_FLOW_BEGIN(...) ITR_EXPAND(ITR_CONCAT(ITR_LOG_FLOW_BEGIN_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_FLOW_END(...) ITR_EXPAND(ITR_CONCAT(ITR_LOG_FLOW_END_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_FLOW(...) ITR_EXPAND(ITR_CONCAT(ITR_LOG_FLOW_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_MOREDETAIL(...) ITR_EXPAND(ITR_CONCAT(ITR_LOG_MOREDETAIL_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_DETAIL(...) ITR_EXPAND(ITR_CONCAT(ITR_LOG_DETAIL_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_WARN(...) ITR_EXPAND(ITR_CONCAT(ITR_LOG_WARN_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_LOG_ERROR(...) ITR_EXPAND(ITR_CONCAT(ITR_LOG_ERROR_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))

#define ITR_ENABLED_VISUALIZATION(...) ITR_EXPAND(ITR_CONCAT(ITR_ENABLED_VISUALIZATION_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_ENABLED_FLOW(...) ITR_EXPAND(ITR_CONCAT(ITR_ENABLED_FLOW_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_ENABLED_MOREDETAIL(...) ITR_EXPAND(ITR_CONCAT(ITR_ENABLED_MOREDETAIL_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_ENABLED_DETAIL(...) ITR_EXPAND(ITR_CONCAT(ITR_ENABLED_DETAIL_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_ENABLED_WARN(...) ITR_EXPAND(ITR_CONCAT(ITR_ENABLED_WARN_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))
#define ITR_ENABLED_ERROR(...) ITR_EXPAND(ITR_CONCAT(ITR_ENABLED_ERROR_, ITR_TUPLE_SIZE(__VA_ARGS__))(__VA_ARGS__))

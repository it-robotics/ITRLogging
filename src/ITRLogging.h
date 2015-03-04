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
#include <typeinfo>
#include "xlogger.h"

typedef void * HLOGGER;

inline log4cxx::XLoggerPtr __getITRLogger(const char *logger)
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

#else // C
  inline static HLOGGER __getITRLogger(const char *logger)\
  {\
    return __ITRLogger;\
  };

#define ITR_DECLARE_GLOBAL_LOGGER(name) \
  extern HLOGGER __ITRLogger;\
  inline static log4cxx::XLoggerPtr __getDefaultITRLogger()\
  {\
    return __ITRLogger;\
  };

#define ITR_DECLARE_GLOBAL_LOGGER(name)
#define ITR_INIT_GLOBAL_LOGGER(name)

#endif

#ifdef ITR_LOG_DISABLED

// TODO Remove MessageBuffer
#define __ITR_LOG_DISABLED(logger, message) { \
        if (false) {\
           ::log4cxx::helpers::MessageBuffer oss_; \
           oss_.str(oss_ << message); }}

#define ITR_LOG_VISUALIZATION_LOG4CXX __ITR_LOG_DISABLED
#define ITR_LOG_FLOW_LOG4CXX __ITR_LOG_DISABLED
#define ITR_LOG_MOREDETAIL_LOG4CXX __ITR_LOG_DISABLED
#define ITR_LOG_DETAIL_LOG4CXX __ITR_LOG_DISABLED
#define ITR_LOG_WARN_LOG4CXX __ITR_LOG_DISABLED
#define ITR_LOG_ERROR_LOG4CXX __ITR_LOG_DISABLED

#define ITR_ENABLED_VISUALIZATION_ACTUAL(logger) false
#define ITR_ENABLED_FLOW_ACTUAL(logger) false
#define ITR_ENABLED_MOREDETAIL_ACTUAL(logger) false
#define ITR_ENABLED_DETAIL_ACTUAL(logger) false
#define ITR_ENABLED_WARN_ACTUAL(logger) false
#define ITR_ENABLED_ERROR_ACTUAL(logger) false

#elif ITR_LOGGING_C

// CHECK-ME Test and verify

#define ITR_ENABLED_VISUALIZATION_ACTUAL(logger) ITREnabledVisualization(logger)
#define ITR_ENABLED_FLOW_ACTUAL(logger) ITREnabledFlow(logger)
#define ITR_ENABLED_MOREDETAIL_ACTUAL(logger) ITREnabledMoreDetail(logger)
#define ITR_ENABLED_DETAIL_ACTUAL(logger) ITREnabledDetail(logger)
#define ITR_ENABLED_WARN_ACTUAL(logger) ITREnabledWarn(logger)
#define ITR_ENABLED_ERROR_ACTUAL(logger) ITREnabledError(logger)

#define ITR_LOG_VISUALIZATION_FORCED(logger, message) \
  ITRLogVisualizationForced(logger, message);

#define ITR_LOG_FLOW_FORCED(logger, message) \
  ITRLogFlowForced(logger, message);

#define ITR_LOG_MOREDETAIL_FORCED(logger, message) \
  ITRLogMoreDetailForced(logger, message);

#define ITR_LOG_DETAIL_FORCED(logger, message) \
  ITRLogDetailForced(logger, message);

#define ITR_LOG_WARN_FORCED(logger, message) \
  ITRLogWarnForced(logger, message);

#define ITR_LOG_ERROR_FORCED(logger, message) \
  ITRLogErrorForced(logger, message);

#else // ITR_LOGGING_CPP

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

#endif

#ifdef __cplusplus

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

extern "C"
{
#endif
  
ITR_COMMON_SHARED_API void * NewITRLogger(const char* name);
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

#endif // ITR_LOG4XX_ABSENT

#define ITR_QUOTE(arg) #arg
#define ITR_EXPAND_AND_QUOTE(x) ITR_QUOTE(x)
#define ITR_EXPAND(x) x
#define __ITR_CONCAT(x, y) x ## y
#define ITR_CONCAT(x, y) __ITR_CONCAT(x, y)
#define ITR_AUGMENTER(...) unused, __VA_ARGS__

#ifdef __GNUG__

#define ITR_TUPLE_SIZE(...) __ITR_TUPLE_SIZE(0, ## __VA_ARGS__, 32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#define __ITR_TUPLE_SIZE(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,N,...) N

#endif // __GNUG__

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
  if (ITR_ENABLED_VISUALIZATION(logger)) {\
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

#define ITR_LOG_VISUALIZATION_2(logger, message) ITR_LOG_VISUALIZATION_GENERIC(__getITRLogger(logger), message)
#define ITR_LOG_FLOW_BEGIN_1(logger) ITR_LOG_FLOW_GENERIC(__getITRLogger(logger), ITR_FUNC_DESC_BEGIN_STR)
#define ITR_LOG_FLOW_END_1(logger) ITR_LOG_FLOW_GENERIC(__getITRLogger(logger), ITR_FUNC_DESC_END_STR)
#define ITR_LOG_FLOW_2(logger, message) ITR_LOG_FLOW_GENERIC(__getITRLogger(logger), message)
#define ITR_LOG_MOREDETAIL_2(message, logger) ITR_LOG_MOREDETAIL_GENERIC(__getITRLogger(logger), message)
#define ITR_LOG_DETAIL_2(message, logger) ITR_LOG_DETAIL_GENERIC(__getITRLogger(logger), message)
#define ITR_LOG_WARN_2(message, logger) ITR_LOG_WARN_GENERIC(__getITRLogger(logger), message)
#define ITR_LOG_ERROR_2(message, logger) ITR_LOG_ERROR_GENERIC(__getITRLogger(logger), message)

#define ITR_LOG_VISUALIZATION_1(message) ITR_LOG_VISUALIZATION_GENERIC(__getITRLogger(), message)
#define ITR_LOG_FLOW_BEGIN_0() ITR_LOG_FLOW_GENERIC(__getITRLogger(), ITR_FUNC_DESC_BEGIN_STR)
#define ITR_LOG_FLOW_END_0() ITR_LOG_FLOW_GENERIC(__getITRLogger(), ITR_FUNC_DESC_END_STR)
#define ITR_LOG_FLOW_1(message) ITR_LOG_FLOW_GENERIC(__getITRLogger(), message)
#define ITR_LOG_MOREDETAIL_1(message) ITR_LOG_MOREDETAIL_GENERIC(__getITRLogger(), message)
#define ITR_LOG_DETAIL_1(message) ITR_LOG_DETAIL_GENERIC(__getITRLogger(), message)
#define ITR_LOG_WARN_1(message) ITR_LOG_WARN_GENERIC(__getITRLogger(), message)
#define ITR_LOG_ERROR_1(message) ITR_LOG_ERROR_GENERIC(__getITRLogger(), message)

#define ITR_ENABLED_VISUALIZATION_1(logger) ITR_ENABLED_VISUALIZATION_ACTUAL(logger)
#define ITR_ENABLED_FLOW_1(logger) ITR_ENABLED_FLOW_ACTUAL(logger)
#define ITR_ENABLED_MOREDETAIL_1(logger) ITR_ENABLED_MOREDETAIL_ACTUAL(logger)
#define ITR_ENABLED_DETAIL_1(logger) ITR_ENABLED_DETAIL_ACTUAL(logger)
#define ITR_ENABLED_WARN_1(logger) ITR_ENABLED_WARN_ACTUAL(logger)
#define ITR_ENABLED_ERROR_1(logger) ITR_ENABLED_ERROR_ACTUAL(logger)

#define ITR_ENABLED_VISUALIZATION_0() ITR_ENABLED_VISUALIZATION_ACTUAL(__getITRLogger())
#define ITR_ENABLED_FLOW_0() ITR_ENABLED_FLOW_ACTUAL(__getITRLogger())
#define ITR_ENABLED_MOREDETAIL_0() ITR_ENABLED_MOREDETAIL_ACTUAL(__getITRLogger())
#define ITR_ENABLED_DETAIL_0() ITR_ENABLED_DETAILACTUAL(__getITRLogger())
#define ITR_ENABLED_WARN_0() ITR_ENABLED_WARN_ACTUAL(__getITRLogger())
#define ITR_ENABLED_ERROR_0() ITR_ENABLED_ERROR_GENERIC(__getITRLogger())

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

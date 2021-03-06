// Copyright (c) 2004-2014 The Apache Software Foundation
// Copyright (c) 2015 Francesco Pretto
// This file is subject to the MIT license

#pragma once

#include "libsdefs.h"
#include <log4cxx/logger.h>
#include <log4cxx/spi/loggerfactory.h>
#include "XLevel.h"
#include "XFactory.h"

namespace log4cxx
{
  namespace spi
  {
    namespace location
    {
      class LocationInfo;
    }
  }

  class XLogger;
  typedef helpers::ObjectPtrT<XLogger> XLoggerPtr;

  /**
  A simple example showing Logger sub-classing. It shows the
  minimum steps necessary to implement one's {@link LoggerFactory}.
  Note that sub-classes follow the hierarchy even if its loggers
  belong to different classes.
  */
  class ITR_COMMON_SHARED_API XLogger : public Logger
  {

#ifdef _MSC_VER
    #pragma warning ( push )
    #pragma warning ( disable: 4251 )
#endif

    LogString suffix;

#ifdef _MSC_VER
    #pragma warning ( pop )
#endif

  public:
    DECLARE_ABSTRACT_LOG4CXX_OBJECT(XLogger)
    BEGIN_LOG4CXX_CAST_MAP()
      LOG4CXX_CAST_ENTRY(XLogger)
      LOG4CXX_CAST_ENTRY_CHAIN(Logger)
    END_LOG4CXX_CAST_MAP()

    XLogger(log4cxx::helpers::Pool& pool, const LogString& name1);

  private:
    static XFactoryPtr getFactory();

  public:
    static XLoggerPtr getLoggerLS(const LogString& name);
    static XLoggerPtr getLogger(const std::string& name);
    static XLoggerPtr getLogger(const char* const name);
#if LOG4CXX_WCHAR_T_API
    static XLoggerPtr getLogger(const std::wstring& name);
    static XLoggerPtr getLogger(const wchar_t* const name);
#endif

    void activateOptions();

    LogString getSuffix() const;
    void setSuffix(const LogString& suffix1);

    void maxdetail(const LogString& message, const log4cxx::spi::LocationInfo& location);
    void maxdetail(const LogString& message);
    void flow(const LogString& message, const log4cxx::spi::LocationInfo& location);
    void flow(const LogString& message);
    void moredetail(const LogString& message, const log4cxx::spi::LocationInfo& location);
    void moredetail(const LogString& message);
    void detail(const LogString& message, const log4cxx::spi::LocationInfo& location);
    void detail(const LogString& message);
    void warn(const LogString& message, const log4cxx::spi::LocationInfo& location);
    void warn(const LogString& message);
    void error(const LogString& message, const log4cxx::spi::LocationInfo& location);
    void error(const LogString& message);

    bool isMaxDetailEnabled() const;
    bool isFlowEnabled() const;
    bool isMoreDetailEnabled() const;
    bool isDetailEnabled() const;
    bool isWarnEnabled() const;
    bool isErrorEnabled() const;
  };
}

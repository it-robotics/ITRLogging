// Copyright (c) 2004-2014 The Apache Software Foundation
// Copyright (c) 2015 Francesco Pretto
// This file is subject to the MIT license

#pragma once

#include <log4cxx/logger.h>
#include <log4cxx/spi/loggerfactory.h>

namespace log4cxx
{ 
  class XFactory;

  typedef helpers::ObjectPtrT<XFactory> XFactoryPtr;

  // Any sub-class of Logger must also have its own implementation of LoggerFactory.
  // NB: Fixed "inherits via dominance" warnings https://issues.apache.org/jira/browse/LOGCXX-219
  class XFactory :
    public virtual spi::LoggerFactory,
    public virtual helpers::ObjectImpl
  {
  public:
    // NB: This has to be declared non abstract so it can be
    // instantiated by the class loader
    DECLARE_LOG4CXX_OBJECT(XFactory)
    BEGIN_LOG4CXX_CAST_MAP()
      LOG4CXX_CAST_ENTRY(XFactory)
      LOG4CXX_CAST_ENTRY(spi::LoggerFactory)
    END_LOG4CXX_CAST_MAP()

    XFactory();
    virtual LoggerPtr makeNewLoggerInstance(
      log4cxx::helpers::Pool& pool,
      const LogString& name) const;
    void addRef() const;
    void releaseRef() const;
  };
}

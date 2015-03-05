// Copyright (c) 2004-2014 The Apache Software Foundation
// Copyright (c) 2015 Francesco Pretto
// This file is subject to the MIT license

#pragma once

#include <log4cxx/level.h>

namespace log4cxx
{
  class XLevel : public log4cxx::Level
  {
    DECLARE_LOG4CXX_LEVEL(XLevel)

  public:
    enum
    {
      VISUALIZATION_INT = 10,
      FLOW_INT = 20,
      MOREDETAIL_INT = 30,
      DETAIL_INT = 40,
      WARN_INT = 50,
      ERROR_INT = 60
    };

    static LevelPtr getVisualization();
    static LevelPtr getFlow();
    static LevelPtr getMoreDetail();
    static LevelPtr getDetail();
    static LevelPtr getWarn();
    static LevelPtr getError();

    XLevel(int level, const LogString& name, int syslogEquivalent);
    /**
    Convert the string passed as argument to a level. If the
    conversion fails, then this method returns #DEBUG.
    */
    static LevelPtr toLevelLS(const LogString& sArg);

    /**
    Convert an integer passed as argument to a level. If the
    conversion fails, then this method returns #DEBUG.

    */
    static LevelPtr toLevel(int val);

    /**
    Convert an integer passed as argument to a level. If the
    conversion fails, then this method returns the specified default.
    */
    static LevelPtr toLevel(int val, const LevelPtr& defaultLevel);


    /**
    Convert the string passed as argument to a level. If the
    conversion fails, then this method returns the value of
    <code>defaultLevel</code>.
    */
    static LevelPtr toLevelLS(const LogString& sArg,
      const LevelPtr& defaultLevel);
  };
}

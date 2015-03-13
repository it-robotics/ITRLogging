// Copyright (c) 2004-2014 The Apache Software Foundation
// Copyright (c) 2015 Francesco Pretto
// This file is subject to the MIT license

#include "precmp.h"
#include "XLevel.h"
#include <log4cxx/helpers/stringhelper.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

XLevel::XLevel(int level1, const LogString& name1, int syslogEquivalent1)
  : Level(level1, name1, syslogEquivalent1)
{
}

LevelPtr XLevel::getMaxDetail() {
  static const LevelPtr maxdetail(new XLevel(XLevel::MAXDETAIL_INT, LOG4CXX_STR("MAXDETAIL"), 7));
  return maxdetail;
}

LevelPtr XLevel::getFlow() {
  static const LevelPtr flow(new XLevel(XLevel::FLOW_INT, LOG4CXX_STR("FLOW"), 7));
  return flow;
}

LevelPtr XLevel::getMoreDetail() {
  static const LevelPtr moredetail(new XLevel(XLevel::MOREDETAIL_INT, LOG4CXX_STR("MOREDETAIL"), 6));
  return moredetail;
}

LevelPtr XLevel::getDetail() {
  static const LevelPtr detail(new XLevel(XLevel::DETAIL_INT, LOG4CXX_STR("DETAIL"), 4));
  return detail;
}

LevelPtr XLevel::getWarn() {
  static const LevelPtr warn(new XLevel(XLevel::WARN_INT, LOG4CXX_STR("WARN"), 3));
  return warn;
}

LevelPtr XLevel::getError() {
  static const LevelPtr error(new XLevel(XLevel::ERROR_INT, LOG4CXX_STR("ERROR"), 0));
  return error;
}

LevelPtr XLevel::toLevelLS(const LogString& sArg)
{
  return toLevelLS(sArg, getWarn());
}


LevelPtr XLevel::toLevel(int val)
{
  return toLevel(val, getWarn());
}

LevelPtr XLevel::toLevel(int val, const LevelPtr& defaultLevel)
{
  switch(val)
  {
  case MAXDETAIL_INT: return getMaxDetail();
  case FLOW_INT: return getFlow();
  case MOREDETAIL_INT: return getMoreDetail();
  case DETAIL_INT: return getDetail();
  case WARN_INT: return getWarn();
  case ERROR_INT: return getError();
  default: return defaultLevel;
  }
}

LevelPtr XLevel::toLevelLS(const LogString& sArg, const LevelPtr& defaultLevel)
{
  if (sArg.empty())
  {
    return defaultLevel;
  }

  if (StringHelper::equalsIgnoreCase(sArg,
    LOG4CXX_STR("MAXDETAIL"), LOG4CXX_STR("maxdetail"))) {
      return getMaxDetail();
  }

  if (StringHelper::equalsIgnoreCase(sArg,
    LOG4CXX_STR("FLOW"), LOG4CXX_STR("flow"))) {
      return getFlow();
  }

  if (StringHelper::equalsIgnoreCase(sArg,
    LOG4CXX_STR("MOREDETAIL"), LOG4CXX_STR("moredetail"))) {
      return getMoreDetail();
  }

  if (StringHelper::equalsIgnoreCase(sArg,
    LOG4CXX_STR("DETAIL"), LOG4CXX_STR("detail"))) {
      return getDetail();
  }

  if (StringHelper::equalsIgnoreCase(sArg,
    LOG4CXX_STR("WARN"), LOG4CXX_STR("warn"))) {
      return getWarn();
  }

  if (StringHelper::equalsIgnoreCase(sArg,
    LOG4CXX_STR("ERROR"), LOG4CXX_STR("error"))) {
      return getError();
  }

  return Level::toLevel(sArg, defaultLevel);
}

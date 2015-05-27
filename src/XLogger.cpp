// Copyright (c) 2004-2014 The Apache Software Foundation
// Copyright (c) 2015 Francesco Pretto
// This file is subject to the MIT license

#include "precmp.h"
#include "XLogger.h"
#include <log4cxx/logstring.h>
#include <log4cxx/level.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/spi/location/locationinfo.h>
#include <log4cxx/spi/loggerrepository.h>

using namespace log4cxx;
using namespace log4cxx::spi;

XLogger::XLogger(log4cxx::helpers::Pool& pool, const LogString& name1)
  : Logger(pool, name1) { }

XFactoryPtr XLogger::getFactory()
{
  static XFactoryPtr factory = new XFactory();
  return factory;
}

void XLogger::activateOptions()
{
  // Nothing to activate
}

XLoggerPtr XLogger::getLoggerLS(const LogString& name)
{
  return LogManager::getLogger(name, getFactory());
}

XLoggerPtr XLogger::getLogger(const std::string& name)
{
  return LogManager::getLogger(name, getFactory());
}

XLoggerPtr XLogger::getLogger(const char* const name)
{
  return LogManager::getLogger(name, getFactory());
}

#if LOG4CXX_WCHAR_T_API

XLoggerPtr XLogger::getLogger(const std::wstring& name)
{
  return LogManager::getLogger(name, getFactory());
}
XLoggerPtr XLogger::getLogger(const wchar_t* const name)
{
  return LogManager::getLogger(name, getFactory());
}

#endif

LogString XLogger::getSuffix() const
{
  return suffix;
}

void XLogger::setSuffix(const LogString& suffix1)
{
  this->suffix = suffix1;
}

void XLogger::maxdetail(const LogString& message, const LocationInfo& locationInfo)
{
  if (repository->isDisabled(XLevel::MAXDETAIL_INT))
  {
    return;
  }

  if (XLevel::getMaxDetail()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getMaxDetail(), message, locationInfo);
  }
}

void XLogger::maxdetail(const LogString& message)
{
  if (repository->isDisabled(XLevel::MAXDETAIL_INT))
  {
    return;
  }

  if (XLevel::getMaxDetail()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getMaxDetail(), message, LocationInfo::getLocationUnavailable());
  }
}

void XLogger::flow(const LogString& message, const LocationInfo& locationInfo)
{
  if (repository->isDisabled(XLevel::FLOW_INT))
  {
    return;
  }

  if (XLevel::getFlow()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getFlow(), message, locationInfo);
  }
}

void XLogger::flow(const LogString& message)
{
  if (repository->isDisabled(XLevel::FLOW_INT))
  {
    return;
  }

  if (XLevel::getFlow()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getFlow(), message, LocationInfo::getLocationUnavailable());
  }
}

void XLogger::moredetail(const LogString& message, const LocationInfo& locationInfo)
{
  if (repository->isDisabled(XLevel::MOREDETAIL_INT))
  {
    return;
  }

  if (XLevel::getMoreDetail()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getMoreDetail(), message, locationInfo);
  }
}

void XLogger::moredetail(const LogString& message)
{
  if (repository->isDisabled(XLevel::MOREDETAIL_INT))
  {
    return;
  }

  if (XLevel::getMoreDetail()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getMoreDetail(), message, LocationInfo::getLocationUnavailable());
  }
}

void XLogger::detail(const LogString& message, const LocationInfo& locationInfo)
{
  if (repository->isDisabled(XLevel::DETAIL_INT))
  {
    return;
  }

  if (XLevel::getDetail()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getDetail(), message, locationInfo);
  }
}

void XLogger::detail(const LogString& message)
{
  if (repository->isDisabled(XLevel::DETAIL_INT))
  {
    return;
  }

  if (XLevel::getDetail()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getDetail(), message, LocationInfo::getLocationUnavailable());
  }
}

void XLogger::warn(const LogString& message, const LocationInfo& locationInfo)
{
  if (repository->isDisabled(XLevel::WARN_INT))
  {
    return;
  }

  if (XLevel::getWarn()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getWarn(), message, locationInfo);
  }
}

void XLogger::warn(const LogString& message)
{
  if (repository->isDisabled(XLevel::WARN_INT))
  {
    return;
  }

  if (XLevel::getWarn()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getWarn(), message, LocationInfo::getLocationUnavailable());
  }
}

void XLogger::error(const LogString& message, const LocationInfo& locationInfo)
{
  if (repository->isDisabled(XLevel::ERROR_INT))
  {
    return;
  }

  if (XLevel::getError()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getError(), message, locationInfo);
  }
}

void XLogger::error(const LogString& message)
{
  if (repository->isDisabled(XLevel::ERROR_INT))
  {
    return;
  }

  if (XLevel::getError()->isGreaterOrEqual(this->getEffectiveLevel()))
  {
    forcedLog(XLevel::getError(), message, LocationInfo::getLocationUnavailable());
  }
}

bool XLogger::isMaxDetailEnabled() const
{
  if(repository == 0 || repository->isDisabled(XLevel::MAXDETAIL_INT))
  {
    return false;
  }

  return getEffectiveLevel()->toInt() <= XLevel::MAXDETAIL_INT;
}

bool XLogger::isFlowEnabled() const
{
  if(repository == 0 || repository->isDisabled(XLevel::FLOW_INT))
  {
    return false;
  }

  return getEffectiveLevel()->toInt() <= XLevel::FLOW_INT;
}

bool XLogger::isMoreDetailEnabled() const
{
  if(repository == 0 || repository->isDisabled(XLevel::MOREDETAIL_INT))
  {
    return false;
  }

  return getEffectiveLevel()->toInt() <= XLevel::MOREDETAIL_INT;
}

bool XLogger::isDetailEnabled() const
{
  if(repository == 0 || repository->isDisabled(XLevel::DETAIL_INT))
  {
    return false;
  }

  return getEffectiveLevel()->toInt() <= XLevel::DETAIL_INT;
}

bool XLogger::isWarnEnabled() const
{
  if(repository == 0 || repository->isDisabled(XLevel::WARN_INT))
  {
    return false;
  }

  return getEffectiveLevel()->toInt() <= XLevel::WARN_INT;
}

bool XLogger::isErrorEnabled() const
{
  if(repository == 0 || repository->isDisabled(XLevel::ERROR_INT))
  {
    return false;
  }

  return getEffectiveLevel()->toInt() <= XLevel::ERROR_INT;
}

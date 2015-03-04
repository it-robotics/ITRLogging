// Copyright (c) 2004-2014 The Apache Software Foundation
// Copyright (c) 2015 Francesco Pretto
// This file is subject to the MIT license

#include "precmp.h"
#include "XFactory.h"
#include "XLogger.h"

using namespace log4cxx;

XFactory::XFactory() { }

LoggerPtr XFactory::makeNewLoggerInstance(log4cxx::helpers::Pool& pool, 
  const LogString& name) const
{
  return new XLogger(pool, name);
}

void XFactory::addRef() const
{
  ObjectImpl::addRef();
}

void XFactory::releaseRef() const
{
  ObjectImpl::releaseRef();
}

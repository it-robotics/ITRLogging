// Copyright (c) 2014 IT+Robotics Srl
// Copyright (c) 2015 Francesco Pretto
// This file is subject to the MIT license

#include "precmp.h"
#include "ITRLogging.h"
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include "xfactory.h"
#include "xlogger.h"
#include "xlevel.h"

#ifdef __linux__
#include <unistd.h>
#endif

using namespace std;
using namespace ITR;
using namespace log4cxx;
using namespace log4cxx::helpers;

#define ITR_CONFIG_FILE "itr-logging.conf"
#define UPDATE_CONFIG_FILE_DELAY 5000 // 5s

static void replace_all(string &s, const string &search, const string &replace);
static string demangle(const char* name);

// NB: These has to be done before first configuration so the
// log4cxx class loader will work
IMPLEMENT_LOG4CXX_OBJECT(XFactory);
IMPLEMENT_LOG4CXX_OBJECT(XLogger)
IMPLEMENT_LOG4CXX_LEVEL(XLevel)

LoggingInit::LoggingInit()
{
  char * config_file_dir = NULL;
  char * config_file = NULL;
  char * config_file_delay = NULL;

#ifdef _WIN32
  char config_file_dir_[1024] = { 0 };
  char config_file_[1024] = { 0 };
  char config_file_delay_[1024] = { 0 };
  GetEnvironmentVariableA("ITR_LOGGING_CONFIG_FILE_DIR",
    config_file_dir_, sizeof(config_file_dir_));
  GetEnvironmentVariableA("ITR_LOGGING_CONFIG_FILE",
    config_file_, sizeof(config_file_));
  GetEnvironmentVariableA("ITR_LOGGING_CONFIG_FILE_DELAY",
    config_file_delay_, sizeof(config_file_delay_));
  if (strlen(config_file_dir_) != 0)
    config_file_dir = config_file_dir_;
  if (strlen(config_file_) != 0)
    config_file = config_file_;
  if (strlen(config_file_delay_) != 0)
    config_file_delay = config_file_delay_;
#else
  config_file_dir = getenv("ITR_LOGGING_CONFIG_FILE_DIR");
  config_file = getenv("ITR_LOGGING_CONFIG_FILE");
  config_file_delay = getenv("ITR_LOGGING_CONFIG_FILE_DELAY");
#endif

  string configFileDir;

  // TODO Mac and BSD
  char exe[1024];
  memset(exe, 0, sizeof(exe));
#ifdef __linux
  readlink("/proc/self/exe", exe, sizeof(exe));
#elif _WIN32
  GetModuleFileNameA(NULL, exe, sizeof(exe));
#endif

  configFileDir = exe;
  configFileDir = configFileDir.substr(0, configFileDir.find_last_of("\\/") + 1);

  string configFile = ITR_CONFIG_FILE;
  long configFileDelay = UPDATE_CONFIG_FILE_DELAY;

  if (config_file_dir != NULL)
  {
    configFileDir = config_file_dir;
    char last = *configFileDir.rbegin();
#ifdef _WIN32
    if (last != '\\')
      configFileDir + '\\';
#else // Unix
    if (last != '/')
      configFileDir + '/';
#endif
  }

  if (config_file != NULL)
    configFile = config_file;

  if (config_file_delay != NULL)
  {
    char *invalid;
    long delay = strtol(config_file_delay, &invalid, 10);
    if (invalid != NULL)
      configFileDelay = delay;
  }

  string configFilePath = configFileDir + configFile;

  PropertyConfigurator::configureAndWatch(configFilePath, configFileDelay);
}

namespace ITR
{
  LoggingInit __LoggingInitObj;

  std::string DemangleTypeName(const char *name)
  {
    return demangle(name);
  }

  class ITRLogger
  {
  private:
    log4cxx::XLoggerPtr p_Logger;
  public:
    ITRLogger(const char *name)
    {
      p_Logger = log4cxx::XLogger::getLogger(name);
    }

    log4cxx::XLoggerPtr & operator->()
    {
      return p_Logger;
    }
  };
}

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

struct handle
{
    char* p;
    handle(char* ptr) : p(ptr) { }
    ~handle() { std::free(p); }
};

string demangle(const char* name)
{
  int status = -1;
  handle result( abi::__cxa_demangle(name, NULL, NULL, &status) );

  if (status == 0)
  {
    string type = result.p;
    replace_all(type, "::", ".");
    return type;
  }
  else
  {
    return name;
  }
}

#endif

#ifdef _MSC_VER

std::string demangle(const char* name)
{
  std::string type = name;
  if (type[0] == 'c')
    type = type.substr(6);
  else if (type[0] == 's')
    type = type.substr(7);

  replace_all(type, "::", ".");
  return type;
}

#endif

void replace_all(string &s, const string &search, const string &replace)
{
  for( size_t pos = 0; ; pos += replace.length() )
  {
    // Locate the substring to replace
    pos = s.find( search, pos );
    if( pos == string::npos )
      break;

    // Replace by erasing and inserting
    s.erase( pos, search.length() );
    s.insert( pos, replace );
  }
}

extern "C"
{
  HLOGGER NewITRLogger(const char* name)
  {
    return new ITRLogger(name);
  }

  void FreeITRLogger(HLOGGER logger_)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    delete logger;
  }

  void ITRLogVisualization(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_VISUALIZATION_GENERIC((*logger), message, false);
  }

  void ITRLogFlow(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_FLOW_GENERIC((*logger), message, false);
  }

  void ITRLogMoreDetail(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_MOREDETAIL_GENERIC((*logger), message, false);
  }

  void ITRLogDetail(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_DETAIL_GENERIC((*logger), message, false);
  }

  void ITRLogWarn(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_WARN_GENERIC((*logger), message, false);
  }

  void ITRLogError(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_ERROR_GENERIC((*logger), message, false);
  }

  void ITRLogVisualizationForced(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_VISUALIZATION_FORCED((*logger), message, false);
  }

  void ITRLogFlowForced(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_FLOW_FORCED((*logger), message, false);
  }

  void ITRLogMoreDetailForced(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_MOREDETAIL_FORCED((*logger), message, false);
  }

  void ITRLogDetailForced(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_DETAIL_FORCED((*logger), message, false);
  }

  void ITRLogWarnForced(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_WARN_FORCED((*logger), message, false);
  }

  void ITRLogErrorForced(HLOGGER logger_, const char* message)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    __ITR_LOG_ERROR_FORCED((*logger), message, false);
  }

  int ITREnabledVisualization(HLOGGER logger_)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    return __ITR_ENABLED_VISUALIZATION_ACTUAL((*logger));
  }

  int ITREnabledFlow(HLOGGER logger_)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    return __ITR_ENABLED_FLOW_ACTUAL((*logger));
  }

  int ITREnabledMoreDetail(HLOGGER logger_)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    return __ITR_ENABLED_MOREDETAIL_ACTUAL((*logger));
  }

  int ITREnabledDetail(HLOGGER logger_)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    return __ITR_ENABLED_DETAIL_ACTUAL((*logger));
  }

  int ITREnabledWarn(HLOGGER logger_)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    return __ITR_ENABLED_WARN_ACTUAL((*logger));
  }

  int ITREnabledError(HLOGGER logger_)
  {
    ITRLogger *logger = (ITRLogger *)logger_;
    return __ITR_ENABLED_ERROR_ACTUAL((*logger));
  }
}

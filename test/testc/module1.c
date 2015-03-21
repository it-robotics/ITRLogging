#include "module1.h"

#include <stdio.h>
#include <ITRLogging.h>

// Static loggers are needed in every c file
ITR_DEFINE_STATIC_LOGGER(module1);

static void foo2();

void foo1()
{
  ITR_LOG_FLOW_BEGIN();

  printf("Enabled MAXDETAIL module1 = %s\n", ITR_ENABLED_MAXDETAIL() ? "True" : "False");
  printf("Enabled DETAIL module1 = %s\n", ITR_ENABLED_FLOW() ? "True" : "False");

  // Will use module1 logger
  ITR_LOG_MAXDETAIL("Test log");
  ITR_LOG_MAXDETAIL_FORCED("Test log");
  ITR_LOG_DETAIL("Test log");
  ITR_LOG_DETAIL(_LSTR("Test log with integer : %d", 1));   // To use variadic arguments
                                                            // The string has to to be
                                                            // enclosed in _LSTR("format", ...) macro

  // Will use module1_cust logger
  ITR_LOG_MAXDETAIL("module1_cust", "Test log");
  ITR_LOG_MAXDETAIL_FORCED("Test log");
  ITR_LOG_DETAIL("module1_cust", "Test log");
  ITR_LOG_DETAIL("module1_cust", _LSTR("Test log with integer : %d", 1));   // To use variadic arguments
                                                                            // The string has to to be
                                                                            // enclosed in _LSTR("format", ...) macro

  foo2();

  ITR_LOG_FLOW_END();
}

void foo2()
{
  // Function loggers overrides any other static or class logger
  ITR_DEFINE_FUNCTION_LOGGER(module1_func);

  // Will use module1_func logger
  ITR_LOG_MAXDETAIL("Test log");
  ITR_LOG_DETAIL("Test log");
}

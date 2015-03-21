#include "Class1.h"

#include <iostream>

using namespace std;
using namespace NS1;

// Class loggers need to be defined in compilation units,
// also need to be declared with ITR_DECLARE_CLASS_LOGGER
ITR_DEFINE_CLASS_LOGGER(Class1);

// Static loggers are needed for free methods
ITR_DEFINE_STATIC_LOGGER(Class1Static);

static void foo_free();

void Class1::foo1()
{
  ITR_LOG_FLOW_BEGIN();

  cout << "Enabled MAXDETAIL Class2 = " << (ITR_ENABLED_MAXDETAIL() ? "True" : "False") << endl;
  cout << "Enabled DETAIL Class1 = " << (ITR_ENABLED_DETAIL() ? "True" : "False") << endl;

  // Will use Class1 logger
  ITR_LOG_MAXDETAIL("Test log");
  ITR_LOG_MAXDETAIL_FORCED("Test log");
  ITR_LOG_DETAIL("Test log");
  ITR_LOG_DETAIL("Test log with integer : " << 1);

  // Will use Class1Cust logger
  ITR_LOG_MAXDETAIL("Class1Cust", "Test log");
  ITR_LOG_MAXDETAIL_FORCED("Test log");
  ITR_LOG_DETAIL("Class1Cust", "Test log");
  ITR_LOG_DETAIL("Class1Cust", "Test log with integer : " << 1);

  foo_static();

  ITR_LOG_FLOW_END();
}

void Class1::foo2()
{
  // Function loggers overrides any other static or class logger
  ITR_DEFINE_FUNCTION_LOGGER(Class1Func);

  // Will use Class1Func logger
  ITR_LOG_MAXDETAIL("Test log");
  ITR_LOG_DETAIL("Test log");

  foo_free();
}

void Class1::foo_static()
{
  // Will use Class1 logger
  ITR_LOG_MAXDETAIL("Test log");
  ITR_LOG_DETAIL("Test log");
}

void foo_free()
{
  // Will use Class1Static logger
  ITR_LOG_MAXDETAIL("Test log");
  ITR_LOG_DETAIL("Test log");
}

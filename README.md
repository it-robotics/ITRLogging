## ITRLogging

ITRLogging is an extension to log4cxx with a simplified macro
based interface. It provides several enhancements over
[recommended](http://logging.apache.org/log4cxx/usage.html)
log4cxx usage. It:

 * supports a new level layout (DETAIL, MOREDETAIL, FLOW ...);
 * supports hierarchical default logger caching: static, class,
   and function;
 * provides a C macro and API wrapper;
 * supports a configuration method (properties file based) enabled
   by default with watch, configurable with environment variables;
 * can be fully disabled.

Because of the very guided approach (e.g. configuration enabled by default),
ITRLogging may suits you or not in certain parts. Also you may not like the
new levels layout, until log4cxx properly supports custom levels addition
(and it's unclear when this will happen). The good is that you can just edit
it: the recommended way to use it is embedding in a common shared library.

The default layout has been chosen to settle one of our long standing
incomprehension about log4cxx: what's the difference between ERROR
and FATAL? What's the difference between INFO and DETAIL? The chosen
layout is the following (lower to higher):

 * MAXDETAIL
 * FLOW
 * MOREDETAIL
 * DETAIL
 * WARN
 * ERROR
 
Of the above, probably only FLOW needs explanation: you can use it to
add functions begin/end spamming or just to separate text from visual
logging, that can go to MAXDETAIL. You can also forget about it.

Custom levels have been added using hidden but properly working
features of log4cxx: "log4j.loggerFactory"[1] and "LEVEL#Factory"[2]
syntax. For the usage: just look at the provided
[properties file](https://github.com/it-robotics/ITRLogging/blob/master/resources/itr-logging.conf).

### Hierarchical default logger caching

The recommended log4cxx usage with LOG4CXX_INFO(logger, "message") style
macros it's not bad but it requires you to remind the name of the logger
and it works only with RAII. The latter is ok if you just do C++ logging
but it's not if you supports C, and ITRLogging supports C logging. With
ITRLogging you can log without providing a logger by previous declaring
a static << class << function logger (at your choice). Just look at the
following example:

```cpp
#include "Class1.h"
#include <iostream>

using namespace std;

// Class loggers need to be defined in compilation units and
// declared in headers.
ITR_DEFINE_CLASS_LOGGER(Class1);

// Static loggers are needed for free functions
ITR_DEFINE_STATIC_LOGGER(Class1Static);

static void foo_free();

void Class1::foo1()
{
  // Will use Class1 logger
  ITR_LOG_DETAIL("Test log with integer : " << 1);
  
  foo_static();
}

void Class1::foo2()
{
  // Function loggers overrides any other static or class logger
  ITR_DEFINE_FUNCTION_LOGGER(Class1Func);
  // Will use Class1Func logger
  ITR_LOG_DETAIL("Test log");
  
  foo_free();
}

void Class1::foo_static()
{
  // Will use Class1 logger
  ITR_LOG_DETAIL("Test log");
  
  // You can also override providing logger name. It will use Class1Cust logger
  ITR_LOG_DETAIL("Class1Cust", "Test log with integer : " << 1);
}

void foo_free()
{
  // Will use Class1Static logger
  ITR_LOG_DETAIL("Test log");
}

});
```

You can find a C style logging example [here](https://github.com/it-robotics/ITRLogging/blob/master/test/testc/module1.c).

### Documentation

Just learn it by examples, [C++](https://github.com/it-robotics/ITRLogging/tree/master/test/testcpp)
style logging and [C](https://github.com/it-robotics/ITRLogging/tree/master/test/testc).
Also look look at the provided [properties file](https://github.com/it-robotics/ITRLogging/blob/master/resources/itr-logging.conf)
for custom levels enabling. The properties file has to be named
"itr-logging.conf" by default and reside in executable directory.
To customize properties file loading you can early set these
environment variables:

 * ITR_LOGGING_CONFIG_FILE_DIR: base path for the properties file;
 * ITR_LOGGING_CONFIG_FILE: properties file name;
 * ITR_LOGGING_CONFIG_FILE_DELAY: file watch delay.
 
### Usage and compilation

The recommended way to use ITRLogging is by embedding it in a shared
library (.so/.dll). In gcc, compile it with "-Wno-unknown-pragmas"
to have less warnings. Also you can define ITR_LOGGING_C to use C
style logging on C++ compiler.

You can define ITR_LOGGING_DISABLED to fully disable any runtime call
to log4cxx.

### Language, compiler and OS support

C++ and C (gnuc89) headers. It was tested with MSVC10 and gcc 4.8.
On the latter it needs non standard extensions to be left enabled
as variadic macros counting is not supported in standard C yet. Probably
it works perfectly also with clang as the more problematic macros were
also tested there.

OS: Tested on Windows and linux. Probably needs some fixes in
OSX and bsd during log4cxx configuration.

### Links

[1] http://svn.apache.org/viewvc/incubator/log4cxx/trunk/src/main/cpp/propertyconfigurator.cpp?view=markup<br />
[2] http://svn.apache.org/viewvc/incubator/log4cxx/trunk/src/main/cpp/optionconverter.cpp?view=markup
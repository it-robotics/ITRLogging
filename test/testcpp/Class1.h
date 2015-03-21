#pragma once

#include <ITRLogging.h>

namespace NS1
{
  class Class1
  {
    // Class loggers needs to be declared in the class and defined
    // with ITR_DEFINE_CLASS_LOGGER
    ITR_DECLARE_CLASS_LOGGER(Class1);
  public:
    void foo1();
    void foo2();
    static void foo_static();
  };
}

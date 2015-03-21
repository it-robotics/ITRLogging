#pragma once

#include <ITRLogging.h>

namespace NS2
{
  class Class2
  {
    // Class loggers needs to be declared in the class and defined
    // with ITR_DEFINE_CLASS_LOGGER
    ITR_DECLARE_CLASS_LOGGER(Class2);
  public:
    void foo3();
  };
}

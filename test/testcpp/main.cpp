#include <ITRLogging.h>

ITR_DEFINE_STATIC_LOGGER(MyLogger);

#include "Test.h"

ITR_DEFINE_CLASS_LOGGER(Test);

void Test::foo()
{
  ITR_DEFINE_FUNCTION_LOGGER(MyLogger);
  bool test = ITR_ENABLED_MOREDETAIL();
  (void)test;
}

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  bool test = ITR_ENABLED_MOREDETAIL();
  (void)test;
  ITR_LOG_MOREDETAIL("Hello" << "");
  ITR_LOG_FLOW_FORCED("Hello" << "");
  test = ITR_ENABLED_MOREDETAIL("");
  return 0;
}

#ifdef __cplusplus
#define ITR_LOGGING_C
#endif

#include <ITRLogging.h>

ITR_DECLARE_GLOBAL_LOGGER(MyLogger);
ITR_DECLARE_GLOBAL_LOGGER(Other);

ITR_DEFINE_STATIC_LOGGER(MyLogger);

void foo()
{
  ITR_DEFINE_FUNCTION_LOGGER(Other);
  ITR_ENABLED_MOREDETAIL();
  ITR_LOG_MOREDETAIL("", _LSTR("", 1));
}

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  int test = ITR_ENABLED_MOREDETAIL();
  (void)test;

  ITR_LOG_MOREDETAIL("", _LSTR("", 1));
  ITR_LOG_MOREDETAIL(_LSTR("", 1));
  ITR_ENABLED_MOREDETAIL("");
  return 0;
}

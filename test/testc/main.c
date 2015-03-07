#include <ITRLogging.h>

ITR_DECLARE_GLOBAL_LOGGER("MyLogger");
ITR_DEFINE_GLOBAL_LOGGER("MyLogger");

int main(int argc, char *argv[])
{
  int test = ITR_ENABLED_MOREDETAIL();
  (void)test;

  ITR_LOG_MOREDETAIL("", _LSTR("", 1));
  ITR_LOG_MOREDETAIL(_LSTR("", 1));
  ITR_ENABLED_MOREDETAIL("");
  return 0;
}

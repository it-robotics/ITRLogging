#include <ITRLogging.h>

ITR_DECLARE_GLOBAL_LOGGER("MyLogger");
ITR_DEFINE_GLOBAL_LOGGER("MyLogger");

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  bool test = ITR_ENABLED_MOREDETAIL();
  (void)test;
  ITR_LOG_MOREDETAIL("Hello" << "");
  ITR_LOG_MOREDETAIL("", "Hello" << "");
  ITR_ENABLED_MOREDETAIL("");
	return 0;
}

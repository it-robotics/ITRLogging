#include <ITRLogging.h>
#include <boost/concept_check.hpp>

ITR_DECLARE_GLOBAL_LOGGER("MyLogger");
ITR_DEFINE_GLOBAL_LOGGER("MyLogger");

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  bool test = ITR_ENABLED_MOREDETAIL();
  (void)test;
  ITR_LOG_MOREDETAIL("Hello");
	return 0;
}

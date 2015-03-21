#include <ITRLogging.h>
#include "module1.h"
#include "module2.h"

// All global loggers have to be defined and inited in a executable
// or shared library main(). To be used, a global logger need a static
// entry point with ITR_DEFINE_STATIC_LOGGER
ITR_DEFINE_GLOBAL_LOGGER(module1);
ITR_DEFINE_GLOBAL_LOGGER(module1_cust);
ITR_DEFINE_GLOBAL_LOGGER(module1_func);
ITR_DEFINE_GLOBAL_LOGGER(module2);
ITR_DEFINE_GLOBAL_LOGGER(module2_other);

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  ITR_INIT_GLOBAL_LOGGER(module1);
  ITR_INIT_GLOBAL_LOGGER(module1_cust);
  ITR_INIT_GLOBAL_LOGGER(module1_func);
  ITR_INIT_GLOBAL_LOGGER(module2);
  ITR_INIT_GLOBAL_LOGGER(module2_other);

  foo1();
  foo3();

  ITR_DESTROY_GLOBAL_LOGGER(module1);
  ITR_DESTROY_GLOBAL_LOGGER(module1_cust);
  ITR_DESTROY_GLOBAL_LOGGER(module1_func);
  ITR_DESTROY_GLOBAL_LOGGER(module2);
  ITR_DESTROY_GLOBAL_LOGGER(module2_other);

  return 0;
}

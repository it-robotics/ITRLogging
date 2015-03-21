#include <ITRLogging.h>

#include "Class1.h"
#include "Class2.h"

using namespace NS1;
using namespace NS2;

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  Class1 class1;
  Class2 class2;

  class1.foo1();
  class1.foo2();
  class2.foo3();

  return 0;
}

#include "Class2.h"

#include <iostream>

using namespace std;
using namespace NS2;

ITR_DEFINE_CLASS_LOGGER(Class2);

void Class2::foo3()
{
  ITR_LOG_FLOW_BEGIN();
  ITR_LOG_FLOW_BEGIN("NS2.Class2Other");

  cout << "Enabled MAXDETAIL Class2 = " << (ITR_ENABLED_MAXDETAIL() ? "True" : "False") << endl;
  cout << "Enabled FLOW Class2 = " << (ITR_ENABLED_FLOW() ? "True" : "False") << endl;
  cout << "Enabled MOREDETAIL Class2 = " << (ITR_ENABLED_MOREDETAIL() ? "True" : "False") << endl;
  cout << "Enabled DETAIL Class2 = " << (ITR_ENABLED_DETAIL() ? "True" : "False") << endl;
  cout << "Enabled WARN Class2 = " << (ITR_ENABLED_WARN() ? "True" : "False") << endl;
  cout << "Enabled ERROR Class2 = " << (ITR_ENABLED_ERROR() ? "True" : "False") << endl;

  cout << "Enabled MAXDETAIL Class2 = " << (ITR_ENABLED_MAXDETAIL("NS2.Class2Other") ? "True" : "False") << endl;
  cout << "Enabled FLOW Class2 = " << (ITR_ENABLED_FLOW("NS2.Class2Other") ? "True" : "False") << endl;
  cout << "Enabled MOREDETAIL Class2 = " << (ITR_ENABLED_MOREDETAIL("NS2.Class2Other") ? "True" : "False") << endl;
  cout << "Enabled DETAIL Class2 = " << (ITR_ENABLED_DETAIL("NS2.Class2Other") ? "True" : "False") << endl;
  cout << "Enabled WARN Class2 = " << (ITR_ENABLED_WARN("NS2.Class2Other") ? "True" : "False") << endl;
  cout << "Enabled ERROR Class2 = " << (ITR_ENABLED_ERROR("NS2.Class2Other") ? "True" : "False") << endl;

  ITR_LOG_MAXDETAIL("Test log");
  ITR_LOG_FLOW("Test log");
  ITR_LOG_MOREDETAIL("Test log");
  ITR_LOG_DETAIL("Test log");
  ITR_LOG_WARN("Test log");
  ITR_LOG_ERROR("Test log");

  ITR_LOG_MAXDETAIL("NS2.Class2Other", "Test log");
  ITR_LOG_FLOW("NS2.Class2Other", "Test log");
  ITR_LOG_MOREDETAIL("NS2.Class2Other", "Test log");
  ITR_LOG_DETAIL("NS2.Class2Other", "Test log");
  ITR_LOG_WARN("NS2.Class2Other", "Test log");
  ITR_LOG_ERROR("NS2.Class2Other", "Test log");

  ITR_LOG_MAXDETAIL_FORCED("Test log");
  ITR_LOG_FLOW_FORCED("Test log");
  ITR_LOG_MOREDETAIL_FORCED("Test log");
  ITR_LOG_DETAIL_FORCED("Test log");
  ITR_LOG_WARN_FORCED("Test log");
  ITR_LOG_ERROR_FORCED("Test log");

  ITR_LOG_MAXDETAIL_FORCED("NS2.Class2Other", "Test log");
  ITR_LOG_FLOW_FORCED("NS2.Class2Other", "Test log");
  ITR_LOG_MOREDETAIL_FORCED("NS2.Class2Other", "Test log");
  ITR_LOG_DETAIL_FORCED("NS2.Class2Other", "Test log");
  ITR_LOG_WARN_FORCED("NS2.Class2Other", "Test log");
  ITR_LOG_ERROR_FORCED("NS2.Class2Other", "Test log");

  ITR_LOG_FLOW_END();
  ITR_LOG_FLOW_END("NS2.Class2Other");
}

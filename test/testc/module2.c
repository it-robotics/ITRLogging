#include "module2.h"

#include <stdio.h>
#include <ITRLogging.h>

ITR_DEFINE_STATIC_LOGGER(module2);

void foo3()
{
  ITR_LOG_FLOW_BEGIN();
  ITR_LOG_FLOW_BEGIN("module2_other");

  printf("Enabled MAXDETAIL module2 = %s\n", ITR_ENABLED_MAXDETAIL() ? "True" : "False");
  printf("Enabled FLOW module2 = %s\n", ITR_ENABLED_FLOW() ? "True" : "False");
  printf("Enabled MOREDETAIL module2 = %s\n", ITR_ENABLED_MOREDETAIL() ? "True" : "False");
  printf("Enabled DETAIL module2 = %s\n", ITR_ENABLED_DETAIL() ? "True" : "False");
  printf("Enabled WARN module2 = %s\n", ITR_ENABLED_WARN() ? "True" : "False");
  printf("Enabled ERROR module2 = %s\n", ITR_ENABLED_ERROR() ? "True" : "False");

  printf("Enabled MAXDETAIL = module2_other %s\n", ITR_ENABLED_MAXDETAIL("module2_other") ? "True" : "False");
  printf("Enabled FLOW module2_other = %s\n", ITR_ENABLED_FLOW("module2_other") ? "True" : "False");
  printf("Enabled MOREDETAIL module2_other = %s\n", ITR_ENABLED_MOREDETAIL("module2_other") ? "True" : "False");
  printf("Enabled DETAIL module2_other = %s\n", ITR_ENABLED_DETAIL("module2_other") ? "True" : "False");
  printf("Enabled WARN module2_other = %s\n", ITR_ENABLED_WARN("module2_other") ? "True" : "False");
  printf("Enabled ERROR module2_other = %s\n", ITR_ENABLED_ERROR("module2_other") ? "True" : "False");

  ITR_LOG_MAXDETAIL("Test log");
  ITR_LOG_FLOW("Test log");
  ITR_LOG_MOREDETAIL("Test log");
  ITR_LOG_DETAIL("Test log");
  ITR_LOG_WARN("Test log");
  ITR_LOG_ERROR("Test log");

  ITR_LOG_MAXDETAIL("module2_other", "Test log");
  ITR_LOG_FLOW("module2_other", "Test log");
  ITR_LOG_MOREDETAIL("module2_other", "Test log");
  ITR_LOG_DETAIL("module2_other", "Test log");
  ITR_LOG_WARN("module2_other", "Test log");
  ITR_LOG_ERROR("module2_other", "Test log");

  ITR_LOG_MAXDETAIL_FORCED("Test log");
  ITR_LOG_FLOW_FORCED("Test log");
  ITR_LOG_MOREDETAIL_FORCED("Test log");
  ITR_LOG_DETAIL_FORCED("Test log");
  ITR_LOG_WARN_FORCED("Test log");
  ITR_LOG_ERROR_FORCED("Test log");

  ITR_LOG_MAXDETAIL_FORCED("module2_other", "Test log");
  ITR_LOG_FLOW_FORCED("module2_other", "Test log");
  ITR_LOG_MOREDETAIL_FORCED("module2_other", "Test log");
  ITR_LOG_DETAIL_FORCED("module2_other", "Test log");
  ITR_LOG_WARN_FORCED("module2_other", "Test log");
  ITR_LOG_ERROR_FORCED("module2_other", "Test log");

  ITR_LOG_FLOW_END();
  ITR_LOG_FLOW_END("module2_other");
}

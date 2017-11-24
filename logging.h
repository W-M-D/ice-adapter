#pragma once

#include <string>

#include <webrtc/rtc_base/logging.h>

namespace faf
{

void logging_init(std::string const& verbosity);
void logging_init_log_dir(std::string const& verbosity,
                          std::string const& log_directory);

#define FAF_LOG_TRACE LOG(LS_SENSITIVE)
#define FAF_LOG_DEBUG LOG(LS_VERBOSE)
#define FAF_LOG_INFO LOG(LS_INFO)
#define FAF_LOG_WARN LOG(LS_WARNING)
#define FAF_LOG_ERROR LOG(LS_ERROR)

}
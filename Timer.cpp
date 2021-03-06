#include "Timer.h"

#include <webrtc/rtc_base/bind.h>
#include <webrtc/rtc_base/thread.h>

#include "logging.h"

#ifdef WEBRTC_POSIX /* dirty fix for linker errors */
namespace rtc
{
MessageHandler::~MessageHandler()
{
  MessageQueueManager::Clear(this);
}
}
#endif

namespace faf {

Timer::Timer():
  _interval(0)
{
}

Timer::~Timer()
{
  stop();
}

void Timer::start(int intervalMs, std::function<void()> callback)
{
  stop();
  _interval = intervalMs;
  _callback = callback;
  rtc::Thread::Current()->Clear(this);
  rtc::Thread::Current()->PostDelayed(RTC_FROM_HERE, _interval, this);
}

bool Timer::started() const
{
  return static_cast<bool>(_callback);
}

void Timer::stop()
{
  _callback = std::function<void()>();
  rtc::Thread::Current()->Clear(this);
}

void Timer::OnMessage(rtc::Message* msg)
{
  if (_callback)
  {
    _callback();
    rtc::Thread::Current()->PostDelayed(RTC_FROM_HERE, _interval, this);
  }
}

} // namespace faf

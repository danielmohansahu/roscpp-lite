/*
 *
 */

// roscpp_lite
#include "roscpp_lite/subscriber.h"

namespace roscpp_lite
{

Subscriber::Subscriber(const std::string& topic, std::function<void(const std::any&)>& callback)
 : _topic(topic), _callback(callback)
{
  // I am a stub
}

} // namespace roscpp_lite

/*
 *
 */

// roscpp_lite
#include "roscpp_lite/subscriber.h"

namespace roscpp_lite
{

Subscriber::Subscriber(const std::string& id_, const std::string& topic, std::function<void(const std::any&)> callback)
 : _id(id_), _topic(topic), _callback(callback), _master(new MasterClient(id_))
{
  // attempt to insert ourselves into the ros graph
  // @TODO make this nonblocking (?)
  _connected = register_();
}

bool Subscriber::register_()
{
  // attempt to register with the ROS master
  // @TODO the third argument is wrong... what should it be?
  const auto publishers = _master->registerSubscriber(_topic, "*", _id);
  if (!publishers)
    return false;

  // if we succeeded, negotiate a connection with each publisher.
  for ([[maybe_unused]] const auto& pub : *publishers)
  {
    // @TODO
  }

  // I am a stub
  return false;
}

} // namespace roscpp_lite

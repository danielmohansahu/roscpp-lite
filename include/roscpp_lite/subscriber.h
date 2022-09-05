/*
 *
 */

#pragma once

// STL
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <any>

// XmlRpc
#include <xmlrpcpp/XmlRpc.h>

// roscpp_lite
#include "client_wrapper.h"

namespace roscpp_lite
{

/* Analog to a ros::Subscriber object in roscpp.
 */
class Subscriber
{
 private:
  // the topic we're interested in
  const std::string _topic;

  // persistent connection to the 'roscore'
  std::unique_ptr<ClientWrapper> _roscore;

  // list of all connections to publishing nodes
  std::vector<std::unique_ptr<ClientWrapper>> _publishers;

  // user supplied callback
  const std::function<void(const std::any&)> _callback;

 public:
  // no default constructor
  Subscriber() = delete;

  // expected constructor
  Subscriber(const std::string& topic, std::function<void(const std::any&)>& callback);

 private:

  /* Register as a new subscriber, and negotiate a connection with existing publishers.
   */
  void initialize();

}; // class Subscriber

} // namespace roscpp_lite

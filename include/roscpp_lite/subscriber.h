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
#include "master_client.h"

namespace roscpp_lite
{

/* Analog to a ros::Subscriber object in roscpp.
 */
class Subscriber
{
 private:
  // the unique ID of our process (like node name)
  const std::string _id;

  // the topic we're interested in
  const std::string _topic;

  // connection status
  bool _connected {false};

  // user supplied callback
  const std::function<void(const std::any&)> _callback;

  // persistent connection to the 'roscore'
  std::unique_ptr<MasterClient> _master;

  // list of all connections to publishing nodes
  std::vector<std::unique_ptr<ClientWrapper>> _publishers;

 public:
  // no default constructor
  Subscriber() = delete;

  // expected constructor
  Subscriber(const std::string& id_, const std::string& topic, std::function<void(const std::any&)> callback);

  // check if we're actually connected
  bool connected() const { return _connected; };

  // _temporary_ method to externally trigger callbacks until threading model is added
  void process();

 private:

  /* Register as a new subscriber, and negotiate a connection with existing publishers.
   */
  bool register_();

}; // class Subscriber

} // namespace roscpp_lite

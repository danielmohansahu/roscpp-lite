/*
 *
 */

#pragma once

// STL
#include <string>
#include <memory>
#include <optional>

// XmlRpc
#include <xmlrpcpp/XmlRpc.h>

// roscpp_lite
#include "uri.h"

namespace roscpp_lite
{

/* Encapsulation of an XmlRpc Client for ROS Communication.
 */
class ClientWrapper
{
 public:
  // convenience typdefs
  using XmlRpcClient = XmlRpc::XmlRpcClient;
  using XmlRpcValue = XmlRpc::XmlRpcValue;

 private:

  // identification information
  const URI _uri;

  // persistent underlying xml client
  std::unique_ptr<XmlRpcClient> _client;

 public:
  /* Construct a client wrapper for connection to the given URI.
   */
  explicit ClientWrapper(const std::string& uri);

  /* send the specified command to our client
   *
   * Adapted from:
   *  https://github.com/ros/ros_comm/blob/f5fa3a168760d62e9693f10dcb9adfffc6132d22/clients/roscpp/src/libros/master.cpp
   */
  bool execute(const std::string& method, const XmlRpcValue& request, XmlRpcValue& response, XmlRpcValue& payload);

}; // class ClientWrapper

} // namespace roscpp_lite

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

  // persistent underlying xml client
  std::unique_ptr<XmlRpcClient> _client;

 public:
  // constructor via URI
  explicit ClientWrapper(const std::optional<std::string>& uri = std::nullopt);

  // send the specified command to our client
  bool execute(const std::string_view& method, const XmlRpcValue& request, XmlRpcValue& response, XmlRpcValue& payload);

}; // class ClientWrapper

} // namespace roscpp_lite

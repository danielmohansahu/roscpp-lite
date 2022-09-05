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

/* Encapsulation of an XmlRpc Server for ROS Communication.
 */
class ServerWrapper
{
 public:
  // convenience typdefs
  using XmlRpcServer = XmlRpc::XmlRpcServer;
  using XmlRpcValue = XmlRpc::XmlRpcValue;

 private:

  // persistent underlying xml client
  std::unique_ptr<XmlRpcServer> _server;

  // identification information
  URI _uri;

 public:
  /* Construct an XmlRpc server wrapper.
   */
  explicit ServerWrapper();

}; // class ClientWrapper

} // namespace roscpp_lite

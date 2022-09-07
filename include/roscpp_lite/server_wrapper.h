/*
 *
 */

#pragma once

// STL
#include <string>
#include <memory>
#include <optional>

// xmlrpc-c
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

// roscpp_lite
#include "uri.h"

namespace roscpp_lite
{

/* Encapsulation of an XmlRpc Server for ROS Communication.
 */
class ServerWrapper
{
 private:

  // persistent underlying xml server objects
  std::unique_ptr<xmlrpc_c::registry> _registry;
  std::unique_ptr<xmlrpc_c::serverAbyss> _server;

  // identification information
  std::unique_ptr<URI> _uri;

 public:
  /* Construct an XmlRpc server wrapper.
   */
  explicit ServerWrapper();

}; // class ClientWrapper

} // namespace roscpp_lite

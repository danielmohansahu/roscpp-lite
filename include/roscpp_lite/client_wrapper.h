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
#include <xmlrpc-c/client_simple.hpp>

// roscpp_lite
#include "uri.h"

namespace roscpp_lite
{

/* Encapsulation of an XmlRpc Client for ROS Communication.
 */
class ClientWrapper
{
 private:

  // identification information
  const std::unique_ptr<URI> _uri;

  // persistent underlying xml client
  std::unique_ptr<xmlrpc_c::clientSimple> _client;

 public:
  /* Construct a client wrapper for connection to the given URI.
   */
  explicit ClientWrapper(const std::string& uri);

  /* send the specified command to our client
   *
   * Adapted from:
   *  https://github.com/ros/ros_comm/blob/f5fa3a168760d62e9693f10dcb9adfffc6132d22/clients/roscpp/src/libros/master.cpp
   */
  bool execute(const std::string& method, const xmlrpc_c::paramList& request, xmlrpc_c::value& response, xmlrpc_c::value& payload);

}; // class ClientWrapper

} // namespace roscpp_lite

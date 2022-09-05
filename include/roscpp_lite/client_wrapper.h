/*
 *
 */

#pragma once

// STL
#include <string>
#include <memory>
#include <regex>
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

  // identification information
  const std::string _uri;
  std::string _host;
  size_t _port;

  // regex used to validate URIs
  static inline std::regex _uri_re {"^http://(\\w+):([0-9]+)$"};

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

  /* Accessor for client URI.
   */
  std::string uri() const { return _uri; };

  /* Accessor for client host.
   */
  std::string host() const { return _host; };

  /* Accessor for client port.
   */
  size_t port() const { return _port; };

 private:

  // validate the given URI and split it into component parts.
  static bool split_uri(const std::string uri, std::string& host, size_t& port);

}; // class ClientWrapper

} // namespace roscpp_lite

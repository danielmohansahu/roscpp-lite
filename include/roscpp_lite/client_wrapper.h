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
  // constructor via URI
  explicit ClientWrapper(const std::string& uri);

  // send the specified command to our client
  bool execute(const std::string_view& method, const XmlRpcValue& request, XmlRpcValue& response, XmlRpcValue& payload);

  // accessor for URI
  std::string uri() const { return _uri; };

  // accessor for host
  std::string host() const { return _host; };

  // accessor for port
  size_t port() const { return _port; };

 private:

  // validate the given URI and split it into component parts.
  static bool split_uri(const std::string uri, std::string& host, size_t& port);

}; // class ClientWrapper

} // namespace roscpp_lite

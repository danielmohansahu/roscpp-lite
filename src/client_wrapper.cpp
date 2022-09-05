/*
 *
 */

// roscpp_lite
#include "roscpp_lite/client_wrapper.h"

namespace roscpp_lite
{

ClientWrapper::ClientWrapper(const std::string& uri)
 : _uri(uri)
{
  // Validate URI and extract host / port information
  if (!split_uri(uri, _host, _port))
    throw std::runtime_error("Cannot process invalid URI '" + uri + "'.");
}

bool ClientWrapper::execute(const std::string_view& method, const XmlRpcValue& request, XmlRpcValue& response, XmlRpcValue& payload)
{
  // I am a stub
  return false;
}

bool ClientWrapper::split_uri(const std::string uri, std::string& host, size_t& port)
{
  // don't bother if this isn't a valid format for the URI
  if (!std::regex_match(uri, _uri_re))
    return false;

  // split into component parts
  auto tmp = std::string(uri.begin() + 7, uri.end());
  host = tmp.substr(0, tmp.find(":"));
  port = std::stoi(tmp.substr(uri.find(":") + 1, tmp.size()));

  // indicate success
  return true;
}

} // namespace roscpp_lite

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

  // connect to the core client
  _client = std::make_unique<XmlRpcClient>(_host.c_str(), _port, "/");
}

bool ClientWrapper::execute(const std::string& method, const XmlRpcValue& request, XmlRpcValue& response, XmlRpcValue& payload)
{
  // execute call
  if (!_client->execute(method.c_str(), request, response))
    return false;

  // validate result
  if (   (response.getType() != XmlRpcValue::TypeArray)
      || (response.size() != 2 && response.size() != 3)
      || (response[0].getType() != XmlRpcValue::TypeInt)
      || (response[1].getType() != XmlRpcValue::TypeString) )
    return false;

  // get response component information
  const int status_code = response[0];
  const std::string status_string = response[1];

  // continue validation
  if (status_code != 1)
    return false;

  // format response
  if (response.size() > 2)
  {
    payload = response[2];
  }
  else
  {
    std::string empty_array = "<value><array><data></data></array></value>";
    int offset = 0;
    payload = XmlRpcValue(empty_array, &offset);
  }

  // indicate success, if we got this far
  return true;
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

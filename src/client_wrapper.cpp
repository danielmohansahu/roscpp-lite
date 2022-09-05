/*
 *
 */

// STL
#include <iostream>

// roscpp_lite
#include "roscpp_lite/client_wrapper.h"

namespace roscpp_lite
{

ClientWrapper::ClientWrapper(const std::string& uri)
 : _uri(uri), _client(new XmlRpcClient(_uri.host.c_str(), _uri.port, "/"))
{
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

  std::cout << "  execute(" << method << ") returned " << status_code << ", msg: " << status_string << std::endl;

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

} // namespace roscpp_lite

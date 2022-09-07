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
 : _uri(new URI(uri)), _client(new xmlrpc_c::clientSimple{})
{
}

bool ClientWrapper::execute(const std::string& method,
                            const xmlrpc_c::paramList& request,
                            xmlrpc_c::value& response,
                            xmlrpc_c::value& payload)
{
  // execute call and validate response
  try
  {
    // perform call
    _client->call(_uri->uri, method, request, &response);

    // extract response sub-information
    const std::vector<xmlrpc_c::value> res = xmlrpc_c::value_array(response).vectorValueValue();
    const int status_code = xmlrpc_c::value_int(res[0]);
    const std::string status_string = xmlrpc_c::value_string(res[1]);

    std::cout << "  execute(" << method << ") returned " << status_code << ", msg: " << status_string << std::endl;

    // continue validation
    if (status_code != 1)
      return false;

    // format response
    if (res.size() > 2)
      payload = res[2];
    else
      payload = xmlrpc_c::value_string("<value><array><data></data></array></value>");
  }
  catch (const girerr::error&)
  {
    return false;
  }

  // indicate success, if we got this far
  return true;
}

} // namespace roscpp_lite

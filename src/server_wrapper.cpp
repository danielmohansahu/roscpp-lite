/*
 *
 */

// STL
#include <iostream>
#include <assert.h>

// roscpp_lite
#include "roscpp_lite/server_wrapper.h"

namespace roscpp_lite
{

ServerWrapper::ServerWrapper()
 : _registry(new xmlrpc_c::registry()), _server(new XmlRpcServer(*_registry))
{
  // get port and host
  struct sockaddr * listenNameP;
  sockaddr_len listenNameLen;
  _server->getListenName(&listenNameP, &listenNameLen);

  // update URI with server info
  _uri = std::make_unique<URI>("localhost", _server->get_port());
}

} // namespace roscpp_lite

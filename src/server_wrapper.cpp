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
 : _server(new XmlRpcServer())
{
  // initialize server
  const bool bound = _server->bindAndListen(0);
  assert(bound);
}

} // namespace roscpp_lite

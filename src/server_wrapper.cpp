/*
 *
 */

// STL
#include <iostream>

// roscpp_lite
#include "roscpp_lite/client_wrapper.h"

namespace roscpp_lite
{

ClientWrapper::ClientWrapper()
 : _server(new XmlRpcServer()
{
}

} // namespace roscpp_lite

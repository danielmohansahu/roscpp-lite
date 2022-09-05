/*
 */

// STL
#include <stdlib.h>

// roscpp_lite
#include "roscpp_lite/master_client.h"

namespace roscpp_lite
{

MasterClient::MasterClient(const std::string& id_)
 : _id(id_)
{
  // check if environment variables override ROS_MASTER_URI
  if (const char* master_uri = getenv("ROS_MASTER_URI"); master_uri)
    _uri = std::string(master_uri);

  // construct client (it will throw if URI is invalid)
  _client = std::make_unique<ClientWrapper>(_uri);
}

std::optional<std::vector<std::string>>
MasterClient::registerSubscriber(const std::string& topic, const std::string& topic_type, const std::string& caller_api)
{
  // I am a stub.
  return std::nullopt;
}

bool MasterClient::unregisterSubscriber(const std::string& topic, const std::string& caller_api)
{
  // I am a stub.
  return false;
}

std::optional<std::string> MasterClient::lookupNode(const std::string& node_name)
{
  // I am a stub.
  return std::nullopt;
}

std::optional<std::vector<std::pair<std::string,std::string>>> MasterClient::getPublishedTopics(const std::string& subgraph)
{
  // I am a stub.
  return std::nullopt;
}

std::optional<std::vector<std::pair<std::string,std::string>>> MasterClient::getTopicTypes()
{
  // I am a stub.
  return std::nullopt;
}

std::optional<std::vector<std::pair<std::string,std::vector<std::string>>>> MasterClient::getSystemState()
{
  // I am a stub.
  return std::nullopt;
}

std::optional<std::string> MasterClient::getUri()
{
  // I am a stub.
  return std::nullopt;
}

std::optional<std::string> MasterClient::lookupService(const std::string& service)
{
  // I am a stub.
  return std::nullopt;
}

std::optional<std::vector<std::pair<std::string,std::string>>> MasterClient::getParam(const std::string& key)
{
  // I am a stub.
  return std::nullopt;
}

std::optional<std::vector<std::string>> MasterClient::getParamNames()
{
  // I am a stub.
  return std::nullopt;
}

} // namespace roscpp_lite
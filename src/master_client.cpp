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
  // construct input arguments and result structures
  XmlRpc::XmlRpcValue args, result, payload;
  args[0] = _id;
  args[1] = topic;
  args[2] = topic_type;
  args[3] = caller_api;

  // perform call to (hopefully available) master
  if (!_client->execute("registerSubscriber", args, result, payload))
    return std::nullopt;

  // call succeded; convert to STL and return
  return xml_to_stl<std::vector<std::string>>(payload);
}

bool MasterClient::unregisterSubscriber(const std::string& topic, const std::string& caller_api)
{
  // construct input arguments and result structures
  XmlRpc::XmlRpcValue args, result, payload;
  args[0] = _id;
  args[1] = topic;
  args[2] = caller_api;

  // perform call to (hopefully available) master
  return _client->execute("unregisterSubscriber", args, result, payload);
}

std::optional<std::string> MasterClient::lookupNode(const std::string& node_name)
{
  // construct input arguments and result structures
  XmlRpc::XmlRpcValue args, result, payload;
  args[0] = _id;
  args[1] = node_name;

  // perform call to (hopefully available) master
  if (!_client->execute("lookupNode", args, result, payload))
    return std::nullopt;

  // call succeded; convert to STL and return
  return xml_to_stl<std::string>(payload);
}

std::optional<std::vector<std::pair<std::string,std::string>>> MasterClient::getPublishedTopics(const std::string& subgraph)
{
  // construct input arguments and result structures
  XmlRpc::XmlRpcValue args, result, payload;
  args[0] = _id;
  args[1] = subgraph;

  // perform call to (hopefully available) master
  if (!_client->execute("getPublishedTopics", args, result, payload))
    return std::nullopt;

  // call succeded; convert to STL and return
  return xml_to_stl<std::vector<std::pair<std::string,std::string>>>(payload);
}

std::optional<std::vector<std::pair<std::string,std::string>>> MasterClient::getTopicTypes()
{
  // construct input arguments and result structures
  XmlRpc::XmlRpcValue args, result, payload;
  args[0] = _id;

  // perform call to (hopefully available) master
  if (!_client->execute("getTopicTypes", args, result, payload))
    return std::nullopt;

  // call succeded; convert to STL and return
  return xml_to_stl<std::vector<std::pair<std::string,std::string>>>(payload);
}

std::optional<std::vector<std::pair<std::string,std::vector<std::string>>>> MasterClient::getSystemState()
{
  // construct input arguments and result structures
  XmlRpc::XmlRpcValue args, result, payload;
  args[0] = _id;

  // perform call to (hopefully available) master
  if (!_client->execute("getSystemState", args, result, payload))
    return std::nullopt;

  // call succeded; convert to STL and return
  return xml_to_stl<std::vector<std::pair<std::string,std::vector<std::string>>>>(payload);
}

std::optional<std::string> MasterClient::getUri()
{
  // construct input arguments and result structures
  XmlRpc::XmlRpcValue args, result, payload;
  args[0] = _id;

  // perform call to (hopefully available) master
  if (!_client->execute("getUri", args, result, payload))
    return std::nullopt;

  // call succeded; convert to STL and return
  return xml_to_stl<std::string>(payload);
}

std::optional<std::string> MasterClient::lookupService(const std::string& service)
{
  // construct input arguments and result structures
  XmlRpc::XmlRpcValue args, result, payload;
  args[0] = _id;
  args[1] = service;

  // perform call to (hopefully available) master
  if (!_client->execute("lookupService", args, result, payload))
    return std::nullopt;

  // call succeded; convert to STL and return
  return xml_to_stl<std::string>(payload);
}

std::optional<std::vector<std::pair<std::string,std::string>>> MasterClient::getParam(const std::string& key)
{
  // construct input arguments and result structures
  XmlRpc::XmlRpcValue args, result, payload;
  args[0] = _id;
  args[1] = key;

  // perform call to (hopefully available) master
  if (!_client->execute("getParam", args, result, payload))
    return std::nullopt;

  // I am a stub.
  //  @TODO - this is a bit more complicated, since it returns a hierarchical tree which we want to flatten.
  return std::nullopt;
}

std::optional<std::vector<std::string>> MasterClient::getParamNames()
{
  // construct input arguments and result structures
  XmlRpc::XmlRpcValue args, result, payload;
  args[0] = _id;

  // perform call to (hopefully available) master
  if (!_client->execute("getParamNames", args, result, payload))
    return std::nullopt;

  // call succeded; convert to STL and return
  return xml_to_stl<std::vector<std::string>>(payload);
}

} // namespace roscpp_lite
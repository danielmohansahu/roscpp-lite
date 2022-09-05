/*
 */

#pragma once

// STL
#include <string>
#include <memory>
#include <optional>

// XmlRpc
#include <xmlrpcpp/XmlRpc.h>

// roscpp_lite
#include "client_wrapper.h"
#include "utils.h"

namespace roscpp_lite
{

/* Access to the underlying ROS Master XmlRpc API methods.
 *
 * References:
 *  http://wiki.ros.org/ROS/Master_API
 */
class MasterClient
{
 private:
  // our identification
  const std::string _id;

  // our unique underyling XML client
  std::unique_ptr<ClientWrapper> _client;

 public:
  /* Construct a master client given an identifier.
   *
   * There's a *very rough* analog here to a ros::NodeHandle.
   */
  MasterClient(const std::string& id_);

  /* Attempt to register a new subscriber in a running ROS graph.
   *
   * Args:
   *    topic: The absolute namespace of the desired topic.
   *    topic_type: The message type we expect.
   *    caller_api: The URI of the new subscriber.
   *
   * Returns 'std::nullopt' if call failed, or a vector of existing publishers
   *  if call was successful.
   */
  std::optional<std::vector<std::string>> registerSubscriber(const std::string& topic, const std::string& topic_type, const std::string& caller_api);

  /* Remove an existing subscriber from a running ROS graph.
   *
   * Args:
   *    topic: The absolutely qualified name of the desired topic.
   *    caller_api: The URI of the current subscriber.
   *
   * Returns True if successful (or if subscriber doesn't exist).
   */
  bool unregisterSubscriber(const std::string& topic, const std::string& caller_api);

  /* Return the URI of the given node.
   *
   * Args:
   *    node_name: The absolute namespace of the node.
   *
   * Returns 'std::nullopt' if the node doesn't exist, otherwise the URI.
   */
  std::optional<std::string> lookupNode(const std::string& node_name);

  /* Get a list of published (not advertised!) topics.
   *
   * Args:
   *    subgraph: Optional argument to restrict the results to a particular namespace.
   *
   * Returns 'std::nullopt' if the call failed, otherwise a vector of string pairs (topic, type).
   */
  std::optional<std::vector<std::pair<std::string,std::string>>> getPublishedTopics(const std::string& subgraph = "");

  /* Get a list of topic names and types.
   *
   * Returns 'std::nullopt' if the call failed, otherwise a vector of string pairs (topic, type).
   */
  std::optional<std::vector<std::pair<std::string,std::string>>> getTopicTypes();

  /* Get a synopsis of the full system state.
   *
   * Returns 'std::nullopt' if the call failed, otherwise a 3 element vector. The elements are:
   *  0 : A vector of pairs of topic name / all publishers.
   *  1 : A vector of pairs of topic name / all subscribers.
   *  2 : A vector of pairs of service name / all advertisers.
   */
  std::optional<std::vector<std::pair<std::string,std::vector<std::string>>>> getSystemState();

  /* Get the URI of the current ROS master.
   *
   * Returns 'std::nullopt' if the call failed, otherwise the URI.
   */
  std::optional<std::string> getUri();

  /* Return the URI of the given service.
   *
   * Args:
   *    service: The absolutely qualified name of the service.
   *
   * Returns 'std::nullopt' if the service doesn't exist, otherwise the URI.
   */
  std::optional<std::string> lookupService(const std::string& service);

  /* Get all parameters in the given namespace, or a specific param.
   *
   * Args:
   *    key: The namespace or specific param we want.
   *
   * Returns 'std::nullopt' if the call failed, otherwise a vector of pairs of (key, value).
   * Note that if a single parameter is requested we will still return a (one element) vector.
   */
  std::optional<std::vector<std::pair<std::string,std::string>>> getParam(const std::string& key);

  /* Get a list of all parameter names.
   *
   * Returns 'std::nullopt' if the call failed, otherwise a vector of strings.
   */
  std::optional<std::vector<std::string>> getParamNames();

}; // class MasterClient

} // namespace roscpp_lite
/* Object-Oriented encapsulation of a Uniform Resource Identifier (URI)
 */

#pragma once

// STL
#include <string>
#include <regex>

namespace roscpp_lite
{

/* A single validated URI definition.
 */
struct URI
{
  // regex for validating URIs
  static inline std::regex _uri_re {"^http://(\\w+):([0-9]+)$"};

  // struct-like access to port / uri / hostname
  const std::string uri;
  std::string host;
  size_t port;

  // no default constructor allowed
  URI() = delete;

  // construct via URI (will throw if invalid)
  URI(const std::string& uri_) : uri(uri_)
  {
    // Validate URI and extract host / port information
    if (!split_uri(uri, host, port))
      throw std::runtime_error("Cannot process invalid URI '" + uri + "'.");
  }

  // validation method (static, for convenient external use)
  static bool split_uri(const std::string uri, std::string& host, size_t& port)
  {
    // don't bother if this isn't a valid format for the URI
    if (!std::regex_match(uri, _uri_re))
      return false;

    // split into component parts
    auto tmp = std::string(uri.begin() + 7, uri.end());
    host = tmp.substr(0, tmp.find(":"));
    port = std::stoi(tmp.substr(tmp.find(":") + 1, tmp.size()));

    // indicate success
    return true;
  }
}; // struct URI

} // namespace roscpp_lite
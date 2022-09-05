/* General utility functions used throughout the project.
 */

#pragma once

// STL
#include <string>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <assert.h>

// XmlRpc
#include <xmlrpcpp/XmlRpc.h>

namespace roscpp_lite
{

// convenience definition of an "always false" for constexpr asserts
template <typename...> inline constexpr bool always_false = false;

// default false evaluations for constexpr type handling
template<typename T> struct is_vector : public std::false_type {};
template<typename T> struct is_pair : public std::false_type {};
template<typename T> struct is_unordered_map : public std::false_type {};

// specialization to check if something is a std::vector
template<typename T, typename A>
struct is_vector<std::vector<T, A>> : public std::true_type {};

// specialization to check if something is a std::pair
template<typename T1, typename T2>
struct is_pair<std::pair<T1, T2>> : public std::true_type {};

// specialization to check if something is a std::unordered_map
template<typename K, typename T, typename H, typename KE, typename A>
struct is_unordered_map<std::unordered_map<K, T, H, KE, A>> : public std::true_type {};

/* Convert the given XML representation to the STL equivalent.
  */
template <typename T>
T xml_to_stl(XmlRpc::XmlRpcValue xml)
{
  // convenience typedef
  using XmlRpcValue = XmlRpc::XmlRpcValue;

  // check what type we want to cast this as
  if constexpr (std::is_same_v<T, std::string>)
  {
    // if this can be cast a string directly, do that
    if (xml.getType() == XmlRpcValue::TypeString)
      return static_cast<std::string>(xml);
    else if (xml.getType() == XmlRpcValue::TypeBoolean)
      return std::to_string(static_cast<bool>(xml));
    else if (xml.getType() == XmlRpcValue::TypeInt)
      return std::to_string(static_cast<int>(xml));
    else if (xml.getType() == XmlRpcValue::TypeDouble)
      return std::to_string(static_cast<double>(xml));

    // otherwise, we expect it to be a nested structure, which we'll resolve recursively
    assert(xml.getType() == XmlRpcValue::TypeStruct);
    return static_cast<std::string>(xml.begin()->first) + "/" + xml_to_stl<std::string>(xml.begin()->second);
  }
  else if constexpr (is_pair<T>::value)
  {
    // pairs can only be created from TypeArrays of size 2
    assert(xml.getType() == XmlRpcValue::TypeArray && xml.size() == 2);

    // cast as a pair
    return std::pair(xml_to_stl<typename T::first_type>(xml[0]), xml_to_stl<typename T::second_type>(xml[1]));
  }
  else if constexpr (is_vector<T>::value)
  {
    // vectors are a little more complicated - we can only conver them from TypeArrays
    assert(xml.getType() == XmlRpcValue::TypeArray);

    // initialize result
    T result;
    result.reserve(xml.size());

    // recursively populate this vector
    for (size_t i = 0; i != static_cast<size_t>(xml.size()); ++i)
      result.emplace_back(xml_to_stl<typename T::value_type>(xml[i]));
    return result;
  }
  else if constexpr (is_unordered_map<T>::value)
  {
    // maps can only be created from TypeStructs
    assert(xml.getType() == XmlRpcValue::TypeStruct);

    // initialize result
    T result;
    result.reserve(xml.size());

    // // recursively populate this struct
    for (auto it = xml.begin(); it != xml.end(); ++it)
      result.emplace(xml_to_stl<typename T::key_type>(it->first), xml_to_stl<typename T::mapped_type>(it->second));
    return result;
  }
  else
  {
    static_assert(always_false<T>, "Invalid XML type conversion requested.");
  }
}

} // namespace roscpp_lite
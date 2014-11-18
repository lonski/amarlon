#ifndef XMLUTILS_H
#define XMLUTILS_H

#include <sstream>
#include "xml/rapidxml.hpp"

namespace amarlon {

// ===
template<typename T>
T getNodeValue(rapidxml::xml_node<>* node)
{
  T result(0);

  if (node != nullptr)
  {
    std::string value = node->value();

    std::stringstream ss;
    ss << value;
    ss >> result;
  }

  return result;
}

template<>
inline std::string getNodeValue<std::string>(rapidxml::xml_node<>* node)
{
  return node != nullptr ? node->value() : "";
}
// ~~~

// ===
template<typename T>
T getAttribute(rapidxml::xml_node<>* node, const std::string& attribute)
{
  T result(0);
  rapidxml::xml_attribute<>* nodeAtr = node->first_attribute(attribute.c_str());

  if (nodeAtr != nullptr)
  {
    std::string value = nodeAtr->value();

    std::stringstream ss;
    ss << value;
    ss >> result;
  }

  return result;
}

template<>
inline std::string getAttribute<std::string>(rapidxml::xml_node<>* node, const std::string& attribute)
{
  rapidxml::xml_attribute<>* nodeAtr = node->first_attribute(attribute.c_str());
  return nodeAtr != nullptr ? nodeAtr->value() : "";
}
// ~~~

inline bool attributeExists(rapidxml::xml_node<>* node, const std::string& attribute)
{
  return node->first_attribute(attribute.c_str()) != nullptr;
}

}
#endif // XMLUTILS_H

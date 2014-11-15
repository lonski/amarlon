#ifndef XMLUTILS_H
#define XMLUTILS_H

#include <sstream>
#include "xml/rapidxml.hpp"

namespace amarlon {

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
  std::string value;

  if (nodeAtr != nullptr)
  {
    value = nodeAtr->value();
  }

  return value;
}

inline bool attributeExists(rapidxml::xml_node<>* node, const std::string& attribute)
{
  return node->first_attribute(attribute.c_str()) != nullptr;
}

}
#endif // XMLUTILS_H

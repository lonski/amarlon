#ifndef XMLUTILS_H
#define XMLUTILS_H

#include <sstream>
#include "xml/rapidxml.hpp"

namespace amarlon {

template<typename T>
T getAttribute(rapidxml::xml_node<>* node, std::string attribute)
{
  T result(0);
  rapidxml::xml_attribute<>* nodeAtr = node->first_attribute(attribute.c_str());

  if ( nodeAtr )
  {
    std::string value = nodeAtr->value();

    std::stringstream ss;
    ss << value;
    ss >> result;
  }

  return result;
}

template<>
std::string getAttribute<std::string>(rapidxml::xml_node<>* node, std::string attribute)
{
  rapidxml::xml_attribute<>* nodeAtr = node->first_attribute(attribute.c_str());
  std::string value;

  if ( nodeAtr )
  {
    value = nodeAtr->value();
  }

  return value;
}

}
#endif // XMLUTILS_H

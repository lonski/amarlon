#ifndef XMLUTILS_H
#define XMLUTILS_H

#include <sstream>
#include "xml/rapidxml.hpp"
#include <utils.h>

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

template<typename T>
inline void addAttribute(rapidxml::xml_node<>* node, const std::string& name,  const T& value)
{
  auto doc = node->document();
  assert(doc);
  auto attrVal = doc->allocate_string( toStr<T>(value).c_str() );
  auto attrName = doc->allocate_string( name.c_str() );
  auto attr = doc->allocate_attribute( attrName, attrVal );
  node->append_attribute( attr );

}

template<>
inline void addAttribute<std::string>(rapidxml::xml_node<>* node,
                                      const std::string& name,
                                      const std::string& value)
{
  auto doc = node->document();
  assert(doc);
  auto attrVal = doc->allocate_string( value.c_str() );
  auto attrName = doc->allocate_string( name.c_str() );
  auto attr = doc->allocate_attribute( attrName, attrVal );
  node->append_attribute( attr );
}

template<typename T>
inline void addAttributeEnum(rapidxml::xml_node<>* node,
                             const std::string& name,
                             const T& value)
{
  auto doc = node->document();
  if ( doc == nullptr ) throw std::runtime_error("XML::addAttribute: Document cant be null");
  auto attrVal = doc->allocate_string( toStr<int>(static_cast<int>(value)).c_str() );
  auto attrName = doc->allocate_string( name.c_str() );
  auto attr = doc->allocate_attribute( attrName, attrVal );
  node->append_attribute( attr );

}

template<typename T>
inline rapidxml::xml_node<>* createNode(rapidxml::xml_document<>* doc,
                                        const std::string& name,
                                        const T& value)
{
  auto allocatedName = doc->allocate_string( name.c_str() );
  auto allocatedValue = doc->allocate_string( toStr<T>(value).c_str() );
  return doc->allocate_node(rapidxml::node_element, allocatedName, allocatedValue );
}

template<>
inline rapidxml::xml_node<>* createNode<std::string>(rapidxml::xml_document<>* doc,
                                                     const std::string& name,
                                                     const std::string& value)
{
  auto allocatedName = doc->allocate_string( name.c_str() );
  auto allocatedValue = doc->allocate_string( value.c_str() );
  return doc->allocate_node(rapidxml::node_element, allocatedName, allocatedValue );
}


}
#endif // XMLUTILS_H

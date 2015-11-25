#ifndef PARSER_H
#define PARSER_H

#include <xml/rapidxml.hpp>

namespace amarlon {

class Parser
{
public:
  Parser()
    : _xml(nullptr)
  {}

  Parser(rapidxml::xml_node<>* xmlNode)
    : _xml(xmlNode)
  {}

  virtual ~Parser() {}

  /**
   * @brief sets the source of data to parse. Must be set
   *        in order to perform any successfull parse
   */
  virtual void setSource(rapidxml::xml_node<>* xmlNode)
  {
    _xml = xmlNode;
  }

protected:
  rapidxml::xml_node<>* _xml;

};

}

#endif // PARSER_H

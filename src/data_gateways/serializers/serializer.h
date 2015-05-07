#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "xml/rapidxml.hpp"

namespace amarlon {

class Serializer
{
public:
  Serializer()
    : _document(nullptr)
    , _xml(nullptr)
  {}

  Serializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
    : _document(document)
    , _xml(xmlNode)
  {}

  virtual ~Serializer() {}

  /**
   * @brief set the document to which data will be serializes
   *        set the node under wihich the maps will be serialized
   *        it is required in order to do any successfull serialization
   */
  virtual void setDestination(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  {
    _document = document;
    _xml = xmlNode;
  }

protected:
  rapidxml::xml_document<>* _document;
  rapidxml::xml_node<>* _xml;
};

}

#endif // SERIALIZER_H

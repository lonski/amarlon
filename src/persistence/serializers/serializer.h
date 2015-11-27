#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <memory>
#include "xml/rapidxml.hpp"

namespace amarlon {

struct Description;
typedef std::shared_ptr<Description> DescriptionPtr;

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
   *        set the node under wihich the contet will be serialized
   *        it is required in order to do any successfull serialization
   */
  virtual void setDestination(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  {
    _document = document;
    _xml = xmlNode;
  }

  virtual bool serialize(DescriptionPtr) = 0;

protected:
  rapidxml::xml_document<>* _document;
  rapidxml::xml_node<>* _xml;
};

typedef std::shared_ptr<Serializer> SerializerPtr;

}

#endif // SERIALIZER_H

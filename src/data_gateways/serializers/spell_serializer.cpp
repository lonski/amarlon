#include "spell_serializer.h"
#include <spell.h>
#include <utils.h>

using namespace rapidxml;

namespace amarlon {

SpellSerializer::SpellSerializer()
{
}

SpellSerializer::SpellSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : Serializer(document, xmlNode)
{
}

SpellSerializer::~SpellSerializer()
{
}

bool SpellSerializer::serialize(SpellPtr spell)
{
  bool serialized = false;

  if ( spell && _document && _xml )
  {
    xml_node<>* _spellNode = _document->allocate_node(node_element, "Spell");
    _xml->append_node( _spellNode );

    _spellNode->append_attribute( _document->allocate_attribute(
                                       "id",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(spell->getId())
                                                                     ).c_str()) ) );

    _spellNode->append_attribute( _document->allocate_attribute(
                                       "name",
                                       _document->allocate_string( spell->getName().c_str() )));

    _spellNode->append_attribute( _document->allocate_attribute(
                                       "level",
                                       _document->allocate_string( toStr(
                                                                     spell->getLevel()
                                                                     ).c_str()) ) );

    _spellNode->append_attribute( _document->allocate_attribute(
                                       "class",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(spell->getClass())
                                                                     ).c_str()) ) );

    _spellNode->append_attribute( _document->allocate_attribute(
                                       "targetType",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(spell->getTargetType())
                                                                     ).c_str()) ) );

    _spellNode->append_attribute( _document->allocate_attribute(
                                       "range",
                                       _document->allocate_string( toStr(
                                                                     spell->getRange()
                                                                     ).c_str()) ) );


    //Serialize Effects
    for ( auto& pair : spell->_effects )
    {
      xml_node<>* effectsNode = _document->allocate_node(node_element, "Effects");
      effectsNode->append_attribute(_document->allocate_attribute("level", _document->allocate_string(toStr<int>(pair.first).c_str())));

      _effectSerializer.setDestination( _document, effectsNode );
      for( auto e : pair.second )
      {
        _effectSerializer.serialize( e );
      }

      _spellNode->append_node( effectsNode );
    }

    //Serialize Animation
    _effectSerializer.setDestination( _document, _spellNode );
    _animationSerializer.serialize( spell->_animation );
  }

  return serialized;
}

}

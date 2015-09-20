#include "spell_serializer.h"
#include <spell.h>
#include <xml_utils.h>
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

    addAttributeEnum( _spellNode, "id",         spell->getId()         );
    addAttributeEnum( _spellNode, "class",      spell->getClass()      );
    addAttributeEnum( _spellNode, "targetType", spell->getTargetType() );
    addAttribute    ( _spellNode, "name",       spell->getName()       );
    addAttribute    ( _spellNode, "level",      spell->getLevel()      );
    addAttribute    ( _spellNode, "range",      spell->getRange()      );
    addAttribute    ( _spellNode, "radius",     spell->getRadius()     );
    addAttribute    ( _spellNode, "duration",   spell->getRadius()     );

    //Serialize Animation
    _effectSerializer.setDestination( _document, _spellNode );
    _animationSerializer.serialize( spell->_animation );
  }

  return serialized;
}

}

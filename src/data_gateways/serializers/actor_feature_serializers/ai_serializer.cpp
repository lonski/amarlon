#include "ai_serializer.h"

using namespace rapidxml;

namespace amarlon {

AiSerializer::AiSerializer()
  : AiSerializer(nullptr, nullptr)
{
}

AiSerializer::AiSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  : ActorFeatureSerializer(document, xmlNode)
{
}

AiSerializer::~AiSerializer()
{
}

}

#include "rpg_parser.h"
#include <race_description.h>
#include <character_class_description.h>
#include <xml_utils.h>

namespace amarlon {

RpgParser::RpgParser(rapidxml::xml_node<> *xmlNode)
  : Parser(xmlNode)
{
}

std::vector<CharacterClassDescriptionPtr> RpgParser::parseCharacterClasses()
{
  std::vector<CharacterClassDescriptionPtr> classes;

  if ( _xml != nullptr )
  {
    rapidxml::xml_node<>* classesNode = _xml->first_node("Classes");
    if ( classesNode != nullptr )
    {
      rapidxml::xml_node<>* classNode = classesNode->first_node("Class");
      while ( classNode != nullptr )
      {
        CharacterClassDescriptionPtr cClass(new CharacterClassDescription);

        //Parse attributes
        cClass->id          = getAttribute<int>(classNode, "id");
        cClass->name        = getAttribute<std::string>(classNode, "name");
        cClass->description = getAttribute<std::string>(classNode, "description");
        cClass->playable    = getAttribute<bool>(classNode, "playable");

        //Parse AbilityScoreRestrictions
        rapidxml::xml_node<>* asrNode = classNode->first_node("AbilityScoreRestrictions");
        if (asrNode != nullptr)
        {
          rapidxml::xml_node<>* scoreNode = asrNode->first_node("Score");
          while ( scoreNode != nullptr )
          {
            int id = getAttribute<int>(scoreNode, "id");
            MinMax vals( getAttribute<int>(scoreNode, "min"), getAttribute<int>(scoreNode, "max") );

            cClass->abilityScoreRestrictions.push_back(
                  std::make_pair(id,vals) );

            scoreNode = scoreNode->next_sibling();
          }
        }

        //Parse ItemTypeRestrictions
        rapidxml::xml_node<>* itrNode = classNode->first_node("ItemTypeRestrictions");
        if ( itrNode != nullptr )
        {
          rapidxml::xml_node<>* onlyNode = itrNode->first_node("Only");
          while ( onlyNode != nullptr )
          {
            ItemTypeDescription t;
            if ( attributeExists(onlyNode, "armor") ) t.armorType = getAttribute<int>(onlyNode, "armor");
            if ( attributeExists(onlyNode, "weapon") ) t.weaponType = getAttribute<int>(onlyNode, "weapon");
            if ( attributeExists(onlyNode, "amunition") ) t.amunitionType = getAttribute<int>(onlyNode, "amunition");
            if ( attributeExists(onlyNode, "category") ) t.category = getAttribute<int>(onlyNode, "category");

            cClass->itemTypeRestrictions.push_back( t );
            onlyNode = onlyNode->next_sibling();
          }
        }

        classes.push_back(cClass);
        classNode = classNode->next_sibling();
      }
    }
  }

  return classes;
}

std::vector<RaceDescriptionPtr> RpgParser::parseRaces()
{
  std::vector<RaceDescriptionPtr> races;

  if ( _xml != nullptr )
  {
    rapidxml::xml_node<>* racesNode = _xml->first_node("Races");
    if ( racesNode != nullptr )
    {
      rapidxml::xml_node<>* raceNode = racesNode->first_node("Race");
      while ( raceNode != nullptr )
      {
        RaceDescriptionPtr race(new RaceDescription);

        //Parse attributes
        race->id          = getAttribute<int>(raceNode, "id");
        race->name        = getAttribute<std::string>(raceNode, "name");
        race->description = getAttribute<std::string>(raceNode, "description");
        race->playable    = getAttribute<bool>(raceNode, "playable");

        //Parse possible classes
        rapidxml::xml_node<>* pcNode = raceNode->first_node("PossibleClasses");
        if ( pcNode != nullptr )
        {
          rapidxml::xml_node<>* cNode = pcNode->first_node("Class");
          while ( cNode != nullptr )
          {
            race->possibleClasses.push_back( getAttribute<int>( cNode, "id" ) );
            cNode = cNode->next_sibling();
          }
        }

        //Parse skills
        rapidxml::xml_node<>* skillsNode = raceNode->first_node("Skills");
        if ( skillsNode != nullptr )
        {
          rapidxml::xml_node<>* sNode = skillsNode->first_node("Skill");
          while ( sNode != nullptr )
          {
            race->skills.push_back(
                    std::make_pair( getAttribute<int>( sNode, "id" ),
                                    getAttribute<int>( sNode, "level" ) ) );
            sNode = sNode->next_sibling();
          }
        }

        //Parse AbilityScoreRestrictions
        rapidxml::xml_node<>* asrNode = raceNode->first_node("AbilityScoreRestrictions");
        if (asrNode != nullptr)
        {
            rapidxml::xml_node<>* scoreNode = asrNode->first_node("Score");
            while ( scoreNode != nullptr )
            {
              int id = getAttribute<int>(scoreNode, "id");
              MinMax vals( getAttribute<int>(scoreNode, "min"),
                           getAttribute<int>(scoreNode, "max") );

              race->abilityScoreRestrictions.push_back(
                    std::make_pair(id, vals) );

              scoreNode = scoreNode->next_sibling();
            }
        }

        races.push_back( race );
        raceNode = raceNode->next_sibling();
      }
    }
  }

  return races;
}


}

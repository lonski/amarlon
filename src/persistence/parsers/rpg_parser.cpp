#include "rpg_parser.h"
#include <xml_utils.h>
#include <skill.h>

namespace amarlon {

RpgParser::RpgParser(rapidxml::xml_node<> *xmlNode)
  : Parser(xmlNode)
{
}

std::vector<RacePtr> RpgParser::parseRaces()
{
  std::vector<RacePtr> races;

  if ( _xml != nullptr )
  {
    rapidxml::xml_node<>* racesNode = _xml->first_node("Races");
    if ( racesNode != nullptr )
    {
      rapidxml::xml_node<>* raceNode = racesNode->first_node("Race");
      while ( raceNode != nullptr )
      {
        RacePtr race(new Race);

        //Parse attributes
        race->_id = static_cast<RaceType>( getAttribute<int>(raceNode, "id") );
        race->_name = getAttribute<std::string>(raceNode, "name");
        race->_description = getAttribute<std::string>(raceNode, "description");
        race->_playable = getAttribute<bool>(raceNode, "playable");

        //Parse possible classes
        rapidxml::xml_node<>* pcNode = raceNode->first_node("PossibleClasses");
        if ( pcNode != nullptr )
        {
          rapidxml::xml_node<>* cNode = pcNode->first_node("Class");
          while ( cNode != nullptr )
          {
            CharacterClassType cId = static_cast<CharacterClassType>(getAttribute<int>( cNode, "id" ));
            race->_allowedClasses.push_back( cId );
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
            SkillId sId = static_cast<SkillId>(getAttribute<int>( sNode, "id" ));
            int level = getAttribute<int>( sNode, "level" );
            race->_skills.push_back( Skill::create(sId, level) );
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
              AbilityScore::Type id = static_cast<AbilityScore::Type>(getAttribute<int>(scoreNode, "id"));
              MinMax vals( getAttribute<int>(scoreNode, "min"), getAttribute<int>(scoreNode, "max") );
              race->_abilityScoreRestrictions[ id ] = vals;
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

std::vector<CharacterClassPtr> RpgParser::parseCharacterClasses()
{
  std::vector<CharacterClassPtr> classes;

  if ( _xml != nullptr )
  {
    rapidxml::xml_node<>* classesNode = _xml->first_node("Classes");
    if ( classesNode != nullptr )
    {
      rapidxml::xml_node<>* classNode = classesNode->first_node("Class");
      while ( classNode != nullptr )
      {
        CharacterClassPtr cClass(new CharacterClass);

        //Parse attributes
        cClass->_id = static_cast<CharacterClassType>( getAttribute<int>(classNode, "id") );
        cClass->_name = getAttribute<std::string>(classNode, "name");
        cClass->_description = getAttribute<std::string>(classNode, "description");
        cClass->_playable = getAttribute<bool>(classNode, "playable");

        //Parse AbilityScoreRestrictions
        rapidxml::xml_node<>* asrNode = classNode->first_node("AbilityScoreRestrictions");
        if (asrNode != nullptr)
        {
            rapidxml::xml_node<>* scoreNode = asrNode->first_node("Score");
            while ( scoreNode != nullptr )
            {
              AbilityScore::Type id = static_cast<AbilityScore::Type>(getAttribute<int>(scoreNode, "id"));
              MinMax vals( getAttribute<int>(scoreNode, "min"), getAttribute<int>(scoreNode, "max") );
              cClass->_abilityScoreRestrictions[ id ] = vals;
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
            ItemType t;
            t.armor = (ArmorType)getAttribute<int>(onlyNode, "armor");
            t.weapon = (WeaponType)getAttribute<int>(onlyNode, "weapon");
            t.amunition = (AmunitionType)getAttribute<int>(onlyNode, "amunition");
            t.category = (PickableCategory)getAttribute<int>(onlyNode, "category");
            cClass->_itemTypeRestrictions.push_back( ItemTypeRestriction(t) );
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


}

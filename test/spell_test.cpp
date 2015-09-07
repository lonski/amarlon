#include <gtest/gtest.h>
#include <spell.h>
#include <spell_description.h>
#include <spell_parser.h>
#include <xml/rapidxml.hpp>

using namespace rapidxml;

namespace amarlon {

class SpellTest : public ::testing::Test
{
public:
  SpellTest()
  {}

  virtual void SetUp()
  {
    Spell::Gateway.load("data/spells.xml");
  }

};

TEST_F(SpellTest, gatewayFetch)
{
  SpellPtr spell = Spell::Gateway.fetch(SpellId::CureLightWounds);
  ASSERT_FALSE( spell == nullptr );
  EXPECT_EQ( spell->getLevel(), 1 );
}

TEST_F(SpellTest, gatewayStore)
{
  Spell::Gateway.store("test_spells.xml");
}

TEST_F(SpellTest, spell_from_empty_description)
{
  SpellPtr spell = Spell::create( SpellDescriptionPtr() );
  ASSERT_TRUE( spell == nullptr );
}

TEST_F(SpellTest, spell_from_description)
{
  SpellDescriptionPtr dsc( new SpellDescription );
  dsc->level = 2;
  dsc->name = "Super spell";
  dsc->spellClass = static_cast<int>(CharacterClass::MagicUser);
  dsc->targetType = static_cast<int>(TargetType::AREA_RANGE);
  dsc->id = static_cast<int>(SpellId::CureLightWounds);

  SpellPtr spell = Spell::create( dsc );
  ASSERT_FALSE( spell == nullptr );
  EXPECT_EQ( spell->getName(), dsc->name );
  EXPECT_EQ( spell->getLevel(), dsc->level );
  EXPECT_EQ( static_cast<int>(spell->getTargetType()), dsc->targetType );
  EXPECT_EQ( static_cast<int>(spell->getClass()), dsc->spellClass );
  EXPECT_EQ( static_cast<int>(spell->getId()), dsc->id );
}

TEST_F(SpellTest, parseTest)
{
  SpellParser parser;
  xml_document<> xmlDoc;

  std::string xml = "<Spell id=\"1\" name=\"MySpell\" level=\"2\" class=\"1\" targetType=\"3\">"
                    "  <Effects level='0'>"
                    "    <Effect type=\"2\" heal=\"2\"/>"
                    "    <Effect type=\"1\" lockId=\"666\"/>"
                    "  </Effects>"
                    "  <Effects level='4'>"
                    "    <Effect type=\"2\" heal=\"2\"/>"
                    "    <Effect type=\"1\" lockId=\"666\"/>"
                    "  </Effects>"
                    "</Spell>";

  xmlDoc.parse<0>( const_cast<char*>(xml.c_str()) );
  parser.setSource( xmlDoc.first_node("Spell") );

  SpellDescriptionPtr dsc = parser.parseSpellDsc();

  EXPECT_EQ(dsc->name, "MySpell");
  EXPECT_EQ(dsc->level, 2);
  EXPECT_EQ(dsc->spellClass, 1);
  EXPECT_EQ(dsc->targetType, 3);
  EXPECT_EQ(dsc->id, 1);
  EXPECT_EQ(dsc->effects.size(), (size_t)2);

}

}

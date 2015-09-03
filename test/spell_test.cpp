#include <gtest/gtest.h>
#include <spell.h>
#include <spell_description.h>

namespace amarlon {

class SpellTest : public ::testing::Test
{
public:
  SpellTest()
  {}
};

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

  SpellPtr spell = Spell::create( dsc );
  ASSERT_FALSE( spell == nullptr );
  EXPECT_EQ( spell->getName(), dsc->name );
  EXPECT_EQ( spell->getLevel(), dsc->level );
  EXPECT_EQ( static_cast<int>(spell->getTargetType()), dsc->targetType );
  EXPECT_EQ( static_cast<int>(spell->getClass()), dsc->spellClass );
}

}

#include <gtest/gtest.h>
#include <engine.h>
#include <module.h>
#include <spell_db.h>
#include <spell.h>
#include <actor.h>
#include <status_effects_manager.h>

namespace amarlon {

class CharmPersonTest : public ::testing::Test
{
public:
  CharmPersonTest()
  {
  }

  virtual void SetUp()
  {
    Engine::instance().prologue();
    Engine::instance().loadModule( Module("testing") );
  }
  virtual void TearDown()
  {
  }

};

TEST_F(CharmPersonTest, spellAvailable)
{
  SpellPtr spell =
      Engine::instance().getSpellDB().fetch( SpellId::CharmPerson );
  ASSERT_FALSE( spell == nullptr );
}

TEST_F(CharmPersonTest, castable)
{
  ActorPtr player = Engine::instance().getPlayer();
  ActorPtr human = Actor::create( 5001 );

  SpellPtr spell =
      Engine::instance().getSpellDB().fetch( SpellId::CharmPerson );

  ASSERT_TRUE( spell->cast(player, human) != CastResult::Nok );
}

TEST_F(CharmPersonTest, whenNotRessisted_StatusEffectIsAdded)
{
  ActorPtr player = Engine::instance().getPlayer();
  ActorPtr human = Actor::create( 5001 );

  SpellPtr spell =
      Engine::instance().getSpellDB().fetch( SpellId::CharmPerson );

  bool cast_success = false;

  while ( !cast_success )
  {
    CastResult ret = spell->cast(player, human);

    bool hasEffect = human->getStatusEffects().hasEffect( spell->getName() );

    if ( ret == CastResult::Success )
    {
      ASSERT_TRUE(hasEffect);
      cast_success = true;
      break;
    }
    else if ( ret == CastResult::Ressisted )
    {
      ASSERT_FALSE(hasEffect);

      //Lower the saving roll to get into success branch
      CharacterPtr c = human->getFeature<Character>();
      Modifier m(-20);
      m.Type.savingThrow = SavingThrows::Spells;
      c->addModifier(m);
    }
  }

  ASSERT_TRUE(cast_success);
}

}


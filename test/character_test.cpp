#include <gtest/gtest.h>
#include <actor.h>
#include <character.h>
#include <playable_character.h>
#include <engine.h>
#include <actor_descriptions.h>
#include <race.h>
#include <character_type.h>
#include <module.h>

namespace amarlon {

class CharacterTest : public ::testing::Test
{
public:
  CharacterTest()
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

void clearInventory(ActorPtr actor)
{
  InventoryPtr inv = actor->getFeature<Inventory>();
  ASSERT_TRUE( inv != nullptr );
  for ( auto i : inv->items() )
    inv->remove(i);
}

void clearBody(ActorPtr actor)
{
  WearerPtr wearer = actor->getFeature<Wearer>();
  ASSERT_TRUE( wearer != nullptr );
  for ( auto s : ItemSlotType() )
    wearer->unequip(s);
}

TEST_F(CharacterTest, carryingLoad)
{
  ActorPtr ziomek = Actor::create(2 /*Orc*/);

  //clear all items carried by ziomek
  clearBody(ziomek);
  clearInventory(ziomek);

  //replace Character feature
  CharacterDescriptionPtr dsc(new CharacterDescription);
  dsc->race = (int)RaceType::Human;
  dsc->abilityScores[AbilityScore::STR] = 10;
  dsc->speed = 40;
  dsc->type = (int)CharacterType::PlayableCharacter;

  CharacterPtr pc_ch = std::dynamic_pointer_cast<Character>( Character::create(dsc) );
  ziomek->insertFeature( pc_ch );
  ASSERT_TRUE( pc_ch != nullptr);

  //ziomek should have light load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Light );
  ASSERT_EQ( pc_ch->getSpeed(), dsc->speed);

  //add some light item
  ActorPtr potka = Actor::create(24 /*Dagger*/);
  ASSERT_TRUE(ziomek->getFeature<Inventory>()->add(potka));

  //ziomek should have light load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Light );
  ASSERT_EQ( pc_ch->getSpeed(), dsc->speed);

  //create heavy item
  ActorPtr armor = Actor::create( 20 /*LeatherArmor*/);

  CarryingCapacity::Data cData = CarryingCapacity::get(pc_ch->getAbilityScore(AbilityScore::STR), pc_ch->getRace()->getType() );
  int count = (cData.heavy / armor->getFeature<Pickable>()->getWeight()) + 1;

  while ( count-- )
    ASSERT_TRUE(ziomek->getFeature<Inventory>()->add(armor->clone()));

  //ziomek should have heavy load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Heavy );
  ASSERT_EQ( pc_ch->getSpeed(), *dsc->speed - 10 );

}


}


#include <gtest/gtest.h>
#include <actor.h>
#include <character.h>
#include <playable_character.h>
#include <configuration.h>
#include <engine.h>

namespace amarlon {

class CharacterTest : public ::testing::Test
{
public:
  CharacterTest()
  {
  }

  virtual void SetUp()
  {
    cfg.load("config.cfg");
    Engine::instance().prologue(&cfg);
  }

  virtual void TearDown()
  {
  }

protected:
  Configuration cfg;
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
  ActorPtr ziomek = Actor::create(ActorType::Player);

  //clear all items carried by ziomek
  clearBody(ziomek);
  clearInventory(ziomek);

  //replace Character feature
  PlayableCharacterDescriptionPtr dsc(new PlayableCharacterDescription);
  dsc->race = Race::Human;
  dsc->abilityScores[AbilityScore::STR] = 10;
  dsc->speed = 40;

  PlayableCharacterPtr pc_ch = std::dynamic_pointer_cast<PlayableCharacter>( Character::create(dsc) );
  ziomek->insertFeature( pc_ch );

  //ziomek should have light load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Light );
  ASSERT_EQ( pc_ch->getSpeed(), dsc->speed);

  //add some light item
  ActorPtr potka = Actor::create(ActorType::Dagger);
  ASSERT_TRUE(ziomek->getFeature<Inventory>()->add(potka));

  //ziomek should have light load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Light );
  ASSERT_EQ( pc_ch->getSpeed(), dsc->speed);

  //create heavy item
  ActorPtr armor = Actor::create(ActorType::LeatherArmor);

  CarryingCapacity::Data cData = CarryingCapacity::get(pc_ch->getAbilityScore(AbilityScore::STR), pc_ch->getRace() );
  int count = (cData.heavy / armor->getFeature<Pickable>()->getWeight()) + 1;

  while ( count-- )
    ASSERT_TRUE(ziomek->getFeature<Inventory>()->add(armor->clone()));

  //ziomek should have heavy load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Heavy );
  ASSERT_EQ( pc_ch->getSpeed(), dsc->speed - 10 );

}


}

#include <gtest/gtest.h>
#include <actor.h>
#include <character.h>
#include <playable_character.h>
#include <engine.h>
#include <race.h>
#include <character_type.h>

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
  ActorPtr ziomek = Actor::create(ActorType::Orc);

  //clear all items carried by ziomek
  clearBody(ziomek);
  clearInventory(ziomek);

  //replace Character feature
  CharacterData dsc;
  dsc.set_racetype( (int)RaceType::Human );
  IntIntPair* as = dsc.mutable_abilityscores()->Add();
  as->set_first( (int)AbilityScore::STR );
  as->set_second( 10 );
  dsc.set_speed(40);
  dsc.set_charactertype( (int)CharacterType::PlayableCharacter );

  CharacterPtr pc_ch = Character::create(dsc);
  ziomek->insertFeature( pc_ch );
  ASSERT_TRUE( pc_ch != nullptr);

  //ziomek should have light load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Light );
  ASSERT_EQ( pc_ch->getSpeed(), dsc.speed());

  //add some light item
  ActorPtr potka = Actor::create(ActorType::Dagger);
  ASSERT_TRUE(ziomek->getFeature<Inventory>()->add(potka));

  //ziomek should have light load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Light );
  ASSERT_EQ( pc_ch->getSpeed(), dsc.speed());

  //create heavy item
  ActorPtr armor = Actor::create(ActorType::LeatherArmor);

  CarryingCapacity::Data cData = CarryingCapacity::get(pc_ch->getAbilityScore(AbilityScore::STR), pc_ch->getRace()->getType() );
  int count = (cData.heavy / armor->getFeature<Pickable>()->getWeight()) + 1;

  while ( count-- )
    ASSERT_TRUE(ziomek->getFeature<Inventory>()->add(armor->clone()));

  //ziomek should have heavy load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Heavy );
  ASSERT_EQ( pc_ch->getSpeed(), dsc.speed() - 10 );

}


}


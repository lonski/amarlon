#include <gtest/gtest.h>
#include <actor.h>
#include <character.h>
#include <playable_character.h>

namespace amarlon {

class CharacterTest : public ::testing::Test
{
public:
  CharacterTest()
  {
  }

  virtual void SetUp()
  {
    Actor::DB.loadActors("data/actors.xml");
  }

  virtual void TearDown()
  {
  }

};

void clearInventory(ActorPtr actor)
{
  ContainerPtr inv = actor->getFeature<Container>();
  ASSERT_TRUE( inv != nullptr );
  for ( auto i : inv->content() )
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

  PlayableCharacterPtr pc_ch = std::dynamic_pointer_cast<PlayableCharacter>( Character::create(dsc) );
  ziomek->insertFeature( pc_ch );

  //ziomek should have light load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Light );

  //add some light item
  ActorPtr potka = Actor::create(ActorType::Dagger);
  ASSERT_TRUE(ziomek->getFeature<Container>()->add(potka));

  //ziomek should have light load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Light );

  //create heavy item
  ActorPtr armor = Actor::create(ActorType::LeatherArmor);

  CarryingCapacity::Data cData = CarryingCapacity::get(pc_ch->getAbilityScore(AbilityScore::STR), pc_ch->getRace() );
  int count = (cData.heavy / armor->getFeature<Pickable>()->getWeight()) + 1;

  while ( count-- )
    ASSERT_TRUE(ziomek->getFeature<Container>()->add(armor->clone()));

  //ziomek should have heavy load
  ASSERT_TRUE( pc_ch->getLoadLevel() == CarryingCapacity::LoadLevel::Heavy );

}


}

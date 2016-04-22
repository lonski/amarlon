#include <gtest/gtest.h>
#include <item_type.h>
#include <actor.h>
#include <race.h>
#include <engine.h>
#include <module.h>
#include <equip_action.h>
#include <unequip_action.h>

namespace amarlon {

class EquipTest : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    Engine::instance().prologue();
    Engine::instance().loadModule( Module("testing") );
  }
  virtual void TearDown()
  {

  }

};

TEST_F(EquipTest, halflingCannotEquipLargeWeapon)
{
  ActorPtr halfling = Actor::create( 5000 /*Test Halfling*/ );

  //Create 2 handed weapon
  ActorPtr sword2H = Actor::create(92);

  //Equipping it should fail
  ASSERT_EQ( halfling->performAction( new EquipAction( sword2H ) ),
             ActorActionResult::Nok );
}

TEST_F(EquipTest, cannotEquipOnBlockedSlot)
{
  ActorPtr typek = Actor::create( 5001/*Test Human*/ );
  ActorPtr sword2H = Actor::create(92);
  ActorPtr shield = Actor::create(120);

  CharacterPtr c = typek->getFeature<Character>();
  ASSERT_TRUE( c != nullptr );

  //Equip 2H sword
  ASSERT_EQ( (int)typek->performAction( new EquipAction(sword2H) ),
             (int)ActorActionResult::Ok );

  //Equip shield should fail
  ASSERT_EQ( (int)typek->performAction( new EquipAction(shield) ),
             (int)ActorActionResult::SlotBlocked );

  //Unequip 2h weapon
  ASSERT_EQ( (int)typek->performAction( new UnEquipAction(sword2H) ),
             (int)ActorActionResult::Ok );

  //Now equipping shield should pass
  ASSERT_EQ( (int)typek->performAction( new EquipAction(shield) ),
             (int)ActorActionResult::Ok );
}

TEST_F(EquipTest, equipping2hWeaponRemovesOffhand)
{
  ActorPtr typek = Actor::create( 5001/*Test Human*/ );
  WearerPtr w = typek->getFeature<Wearer>();
  ActorPtr sword2H = Actor::create(92);
  ActorPtr shield = Actor::create(120);

  ASSERT_EQ( (int)typek->performAction( new EquipAction(shield) ),
             (int)ActorActionResult::Ok );

  ASSERT_EQ( (int)typek->performAction( new EquipAction(sword2H) ),
             (int)ActorActionResult::Ok );

  ASSERT_FALSE( w->isEquipped(ItemSlotType::Offhand) );

}

class EquipsLargeWeapons2H_WearerTest : public EquipTest
                                      , public ::testing::WithParamInterface< std::pair<int,WeaponSize> >
{
};

INSTANTIATE_TEST_CASE_P(ActorsWhoEquipWeaponsAs2h,
                        EquipsLargeWeapons2H_WearerTest,
                        ::testing::Values( std::make_pair(5001/*Human*/,    WeaponSize::Size_L),
                                           std::make_pair(5002/*Elf*/,      WeaponSize::Size_L),
                                           std::make_pair(5003/*Dwarf*/,    WeaponSize::Size_L),
                                           std::make_pair(5004/*Orc*/,      WeaponSize::Size_L),
                                           std::make_pair(5000/*Halfling*/, WeaponSize::Size_M)
                                           ));

TEST_P(EquipsLargeWeapons2H_WearerTest, EquipWeaponsAs2h)
{
  ActorPtr typek = Actor::create( GetParam().first );
  WearerPtr w = typek->getFeature<Wearer>();

  //Create a weapon and set its weapon size according to param
  ActorPtr sword = Actor::create(92);
  PickablePtr p = sword->getFeature<Pickable>();
  ItemType itype = p->getItemType();
  itype.weaponSize = GetParam().second;
  p->setItemType(itype);

  //Equipping should pass
  ASSERT_EQ( (int)typek->performAction( new EquipAction(sword) ),
             (int)ActorActionResult::Ok );

  //offhand should be blocked
  ASSERT_TRUE( w->isEquipped(ItemSlotType::MainHand) );
  ASSERT_TRUE( w->isBlocked(ItemSlotType::Offhand) );

  //Unequip unblocks slot
  ASSERT_EQ( (int)typek->performAction( new UnEquipAction(sword) ),
             (int)ActorActionResult::Ok );

  ASSERT_FALSE( w->isEquipped(ItemSlotType::MainHand) );
  ASSERT_FALSE( w->isBlocked(ItemSlotType::Offhand) );
}

}

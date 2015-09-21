#include <gtest/gtest.h>
#include <status_effects_manager.h>
#include <effect.h>

namespace amarlon {

class StatusEffectsManagerTest : public ::testing::Test
{
public:
  StatusEffectsManagerTest()
  {}

protected:
  StatusEffectsManager _effects;
};

TEST_F(StatusEffectsManagerTest, addPermamentEffect)
{
  EffectPtr e = Effect::create( EffectType::Damage );
  ASSERT_EQ( e->getTime(), -1 );

  ASSERT_EQ( _effects.getPermamentEffects().size(), (size_t)0 );
  ASSERT_EQ( _effects.getTemporaryEffects().size(), (size_t)0 );
  _effects.add(e);
  ASSERT_EQ( _effects.getTemporaryEffects().size(), (size_t)0 );

  auto pEffects = _effects.getPermamentEffects();
  ASSERT_EQ( pEffects.size(), (size_t)1 );
  ASSERT_EQ( pEffects[0], e );
}

TEST_F(StatusEffectsManagerTest, addTemporaryEffect)
{
  EffectPtr e = Effect::create( EffectType::Damage );
  ASSERT_EQ( e->getTime(), -1 );
  e->setTime(10);
  ASSERT_EQ( e->getTime(), 10 );

  ASSERT_EQ( _effects.getPermamentEffects().size(), (size_t)0 );
  ASSERT_EQ( _effects.getTemporaryEffects().size(), (size_t)0 );
  _effects.add(e);

  auto tEffects = _effects.getTemporaryEffects();
  ASSERT_EQ( tEffects.size(), (size_t)1 );
  ASSERT_EQ( tEffects[0], e );
}

TEST_F(StatusEffectsManagerTest, removePermamentEffect)
{
  auto e = Effect::create(EffectType::Damage);
  ASSERT_EQ( _effects.getPermamentEffects().size(), (size_t)0 );
  ASSERT_EQ( _effects.getTemporaryEffects().size(), (size_t)0 );
  _effects.add( e );
  ASSERT_EQ( _effects.getPermamentEffects().size(), (size_t)1 );
  ASSERT_EQ( _effects.getTemporaryEffects().size(), (size_t)0 );
  _effects.remove( e );
  ASSERT_EQ( _effects.getPermamentEffects().size(), (size_t)0 );
  ASSERT_EQ( _effects.getTemporaryEffects().size(), (size_t)0 );
}


TEST_F(StatusEffectsManagerTest, removeTemporaryEffect)
{
  auto e = Effect::create(EffectType::Damage);
  e->setTime(10);
  ASSERT_EQ( _effects.getPermamentEffects().size(), (size_t)0 );
  ASSERT_EQ( _effects.getTemporaryEffects().size(), (size_t)0 );
  _effects.add( e );
  ASSERT_EQ( _effects.getPermamentEffects().size(), (size_t)0 );
  ASSERT_EQ( _effects.getTemporaryEffects().size(), (size_t)1 );
  _effects.remove( e );
  ASSERT_EQ( _effects.getPermamentEffects().size(), (size_t)0 );
  ASSERT_EQ( _effects.getTemporaryEffects().size(), (size_t)0 );
}

TEST_F(StatusEffectsManagerTest, tick)
{
  auto eTmp1 = Effect::create(EffectType::Damage);
  eTmp1->setTime(15);
  auto eTmp2 = Effect::create(EffectType::Damage);
  eTmp2->setTime(8);

  auto ePerm = Effect::create(EffectType::Damage);
  ePerm->setTime(-1);

  _effects.add(eTmp1);
  _effects.add(eTmp2);
  _effects.add(ePerm);
  _effects.tick();

  ASSERT_EQ(eTmp1->getTime(), 14);
  ASSERT_EQ(eTmp2->getTime(), 7);
  ASSERT_EQ(ePerm->getTime(), -1);
}

TEST_F(StatusEffectsManagerTest, removeExpiredEffect)
{
  auto e1 = Effect::create(EffectType::Damage);
  e1->setTime(8);
  auto e2 = Effect::create(EffectType::Damage);
  e2->setTime(5);
  auto e3 = Effect::create(EffectType::Damage);
  e3->setTime(3);

  _effects.add(e1);
  _effects.add(e2);
  _effects.add(e3);

  _effects.tick(5);

  auto tEffects = _effects.getTemporaryEffects();
  ASSERT_EQ( tEffects.size(), (size_t)1 );
  ASSERT_EQ( tEffects[0], e1 );
}

}


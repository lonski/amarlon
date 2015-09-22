#include <gtest/gtest.h>
#include <status_effects_manager.h>
#include <effect.h>
#include <attack_roll_effect.h>
#include <actor.h>
#include <character.h>

namespace amarlon {

class DummyEffect : public Effect
{
public:
  DummyEffect() : _time(-1) {}
  virtual ~DummyEffect() {}
  EffectType getType() const { return EffectType::Null; }
  EffectPtr clone() { return EffectPtr( new DummyEffect(*this) );  }
  bool isEqual(EffectPtr rhs) { return std::dynamic_pointer_cast<DummyEffect>(rhs)->_time == _time; }
  bool apply(ActorPtr, const Target&) { return true; }
  bool revoke(ActorPtr, const Target&) { return true; }
  Params toParams() const { return {}; }
  void load(const Params&) {}
  int  getTime() const { return _time; }
  void setTime(int time) { _time = time; }

private:
  int _time;
};

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
  EffectPtr e( new DummyEffect );
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
  EffectPtr e( new DummyEffect );
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

TEST_F(StatusEffectsManagerTest, addZeroTimeEffect)
{
  EffectPtr e( new DummyEffect );
  e->setTime(0);

  _effects.add(e);
  ASSERT_EQ( _effects.getPermamentEffects().size(), (size_t)0 );
  ASSERT_EQ( _effects.getTemporaryEffects().size(), (size_t)0 );
}

TEST_F(StatusEffectsManagerTest, removePermamentEffect)
{
  EffectPtr e( new DummyEffect );
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
  EffectPtr e( new DummyEffect );
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
  EffectPtr eTmp1( new DummyEffect );
  eTmp1->setTime(15);
  EffectPtr eTmp2( new DummyEffect );
  eTmp2->setTime(8);

  EffectPtr ePerm( new DummyEffect );
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
  EffectPtr e1( new DummyEffect );
  e1->setTime(8);
  EffectPtr e2( new DummyEffect );
  e2->setTime(5);
  EffectPtr e3( new DummyEffect );
  e3->setTime(3);

  _effects.add(e1);
  _effects.add(e2);
  _effects.add(e3);

  _effects.tick(5);

  auto tEffects = _effects.getTemporaryEffects();
  ASSERT_EQ( tEffects.size(), (size_t)1 );
  ASSERT_EQ( tEffects[0], e1 );
}

TEST_F(StatusEffectsManagerTest, attackRollBuffTest)
{
  //create buff
  EffectPtr attackBonusEffect = Effect::create(EffectType::AttackRoll);
  attackBonusEffect->load( { {"time", "5"}, {"modifier", "2"} } );

  //create the actor
  ActorPtr orc = Actor::create(ActorType::Orc);

  //apply buff on actor
  attackBonusEffect->apply(nullptr, orc);
  attackBonusEffect.reset(); //delete, it should remain in avtor status mgr

  //check if applied
  CharacterPtr c = orc->getFeature<Character>();
  ASSERT_TRUE( c != nullptr );
  ASSERT_EQ( c->getExtraAttackBonus(), 2 );

  //tick the time to expire the effect
  int turns = 5;
  while ( turns-- ) orc->update();

  //check if effect is revoked
  ASSERT_EQ( c->getExtraAttackBonus(), 0 );

}

}


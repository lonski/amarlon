#include "shot_action.h"
#include <actor.h>
#include <dices.h>
#include <direct_path.h>
#include <map.h>
#include <console_utils.h>
#include <engine.h>
#include <chrono>
#include <thread>

namespace amarlon {

ShotAction::ShotAction(ActorPtr target)
  : _target(target)
{
}

ShotAction::~ShotAction()
{
}

bool ShotAction::perform(ActorPtr performer)
{
  _performer = performer;
  MapPtr map = _performer->getMap();
  bool success = false;

  if ( isTargetCorrect() && isReadyToShot() && map )
  {
    success = true;
    ActorPtr missile = pickOneMissile();
    DirectPathPtr path = calculatePath();
    path->extrapolate(5);

    Point previousPoint = path->current();
    while ( !path->isEmpty() )
    {
      Point currentPoint = path->walk();

      renderMissile(previousPoint, currentPoint, missile);
      std::this_thread::sleep_for(std::chrono::milliseconds(40));

      //end of path
      if ( path->isEmpty() && previousPoint.isNonZero() && !map->isBlocked(previousPoint) )
      {

        dropMissile(missile, previousPoint, 100);
        break;
      }
      else
      //obstacle on the path
      if ( currentPoint.isNonZero() && map->isBlocked(currentPoint)  )
      {
        ActorPtr hitActor = getTarget(currentPoint);
        if ( hitActor )
        {
          if ( rangeAttack(hitActor) )
          {
            dropMissile(missile, currentPoint, 60);
            break;
          }
          //else: actor dodged; continue along the path
        }
        else //non-alive object hit
        {
          dropMissile(missile, previousPoint, 40 );
          break;
        }
      }
      previousPoint = currentPoint;
    }
  }

  return success;
}

bool ShotAction::rangeAttack(ActorPtr actor)
{
  bool hit = false;
  int dieRoll = dices::roll( dices::D20 );

  if ( dieRoll != dices::NATURAL_ONE ) //natural one is always a failure
  {
    CharacterPtr attacker = _performer->getFeature<Character>();
    CharacterPtr attacked = actor->getFeature<Character>();

    int attackRoll = dieRoll +
                     attacker->getMissileAttackBonus() +
                     calculateAttackBonusModifier();

    if ( ( dieRoll == dices::NATURAL_TWENTY ) || //natural 20 is always a hit
         ( attackRoll >= attacked->getArmorClass()) ) //hit success
    {
      hit = true;
      attacked->takeDamage(attacker->getDamage(), _performer);
    }
  }

  if ( !hit )
  {
    _performer->notify(Event(EventId::Actor_Missed,{{"target",actor->getName()}}));
  }

  return hit;
}

void ShotAction::renderMissile(const Point& prev, const Point& current, ActorPtr missile)
{
  //determine the symbol
  int dx = current.x - prev.x;
  int dy = current.y - prev.y;

  char c = '-';
  if( (dx > 0 && dy > 0) || (dx < 0 && dy < 0) )
    c = '\\';
  else if( (dx < 0 && dy > 0) || (dx > 0 && dy < 0) )
    c = '/';
  else if ( dx == 0 )
    c = '|';

  Engine::instance().render();
  setTile(current, c, missile->getColor());
  TCODConsole::root->flush();
}

ActorPtr ShotAction::getTarget(const Point& p)
{
  MapPtr map = _performer->getMap();
  auto actors = map->getActors(p,[](ActorPtr a){
      return a->isAlive();
  });
  return actors.empty() ? nullptr : actors.front();
}

void ShotAction::dropMissile(ActorPtr missile, const Point &p, int chance = 100)
{
  if ( p.isNonZero() &&
       missile       &&
       dices::roll(dices::D100) > (100 - chance) )
  {
    MapPtr map = _performer->getMap();
    missile->setPosition(p);
    map->addActor(missile);
  }
}

ActorPtr ShotAction::pickOneMissile()
{
  ActorPtr missile = getAmunition()->spilt(1);
  if ( WearerPtr wearer = _performer->getFeature<Wearer>() )
  {
    wearer->unequip(missile);
  }
  return missile;
}

DirectPathPtr ShotAction::calculatePath()
{
  DirectPathPtr path(new DirectPath( _performer->getMap() ) );

  path->compute( Point(_performer->getX(), _performer->getY()),
                 Point(_target->getX(), _target->getY()), true);

  return path;
}

int ShotAction::calculateAttackBonusModifier()
{
  const int CLOSE_RANGE = 2;

  enum ModifierByRange
  {
    CLOSE  = -5,
    SHORT  = 1,
    MEDIUM = 0,
    LONG   = -2
  };

  int modifier = CLOSE;

  int distance = calculateDistance(_performer, _target);
  if ( distance > CLOSE_RANGE )
  {
    int range = getWeapon()->getRange();
    float relativeDistance = distance / (range > 0 ? range : 1);

    if ( relativeDistance < 0.5 )
      modifier = SHORT;
    else if ( relativeDistance > 1.5 )
      modifier = LONG;
    else
      modifier = MEDIUM;
  }

  return modifier;
}

bool ShotAction::isTargetCorrect()
{
  if ( _performer && _target )
  {
    CharacterPtr attacker = _performer->getFeature<Character>();
    CharacterPtr attacked = _target->getFeature<Character>();

    return attacker && attacked && attacker != attacked;
  }
  return false;
}

bool ShotAction::isReadyToShot()
{
  PickablePtr weapon = getWeapon();
  PickablePtr amunition = getAmunition();

  return weapon    &&
         amunition &&
         amunition->getAmount() > 0 &&
         amunition->getItemType().amunition == weapon->getItemType().amunition;
}

PickablePtr ShotAction::getWeapon()
{
  WearerPtr wearer = _performer->getFeature<Wearer>();
  if ( wearer )
  {
    ActorPtr weaponActor = wearer->equipped( ItemSlotType::MainHand );
    return weaponActor ? weaponActor->getFeature<Pickable>() : nullptr;
  }
  return nullptr;
}

PickablePtr ShotAction::getAmunition()
{
  WearerPtr wearer = _performer->getFeature<Wearer>();
  if (wearer)
  {
    ActorPtr amunitionActor = wearer->equipped( ItemSlotType::Amunition );
    return amunitionActor ? amunitionActor->getFeature<Pickable>() : nullptr;
  }
  return nullptr;
}

ActorActionUPtr ShotAction::clone()
{
  ShotActionUPtr cloned = std::make_unique<ShotAction>(_target);
  cloned->_performer = _performer;

  return std::move(cloned);
}

}


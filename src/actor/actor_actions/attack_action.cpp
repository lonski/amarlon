#include "attack_action.h"
#include <actor.h>
#include <directions.h>
#include <map.h>
#include <world_wirection_utils.h>

namespace amarlon {

class AttackAnimation
{
public:
  AttackAnimation()
    : _direction(WorldDirection::N)
    , _anim( Actor::create(ActorType::Animation) )
  {}

  ~AttackAnimation()
  {
    if ( _anim )
    {
      _anim->getMap()->removeActor(_anim);
    }
  }

  void start(ActorPtr actor, WorldDirection dir, int frames)
  {
    while( --frames ) --dir;
    _direction = dir;

    _actor = actor;
    _anim->setMap( _actor->getMap() );
  }

  void tick()
  {
    _anim->setChar( WorldDirectionUtils::getChar( _direction ) );
    _anim->setPosition( _actor->getX() + WorldDirectionUtils::getDX(_direction), _actor->getY() + WorldDirectionUtils::getDY(_direction) );

    ++_direction;

    std::cout << static_cast<int>(_direction);
    std::cout.flush();
  }

private:
  int _frames;
  WorldDirection _direction;
  ActorPtr _actor;
  ActorPtr _anim;

};

AttackAction::AttackAction(ActorPtr target)
  : _target(target)
  , _actionPoints(6)
  , _ticksLeft(0)
  , _running(false)
{
}

AttackAction::~AttackAction()
{
}

bool AttackAction::run(ActorPtr performer)
{
  if ( !isRunning() )
  {
    _performer = performer;
    _ticksLeft = _actionPoints;
    _running = true;
    _anim.reset( new AttackAnimation );

    _anim->start(_performer,
                 WorldDirectionUtils::getDirection( _target->getX() - _performer->getX(), _target->getY() - _performer->getY() ) ,
                 _actionPoints - 1);

    return true;
  }
  return false;
}

ActorActionUPtr AttackAction::clone()
{
  AttackActionUPtr cloned = std::make_unique<AttackAction>(_target);
  cloned->_performer = _performer;

  return std::move(cloned);
}

int AttackAction::getActionPointCount() const
{
  return _actionPoints;
}

bool AttackAction::isRunning() const
{
  return _running;
}

void AttackAction::tick()
{
  if ( isRunning() )
  {
    _anim->tick();
    if ( --_ticksLeft <= 0 )
    {
      perform();
      _running = false;
    }
  }
}

bool AttackAction::perform()
{
  bool attacked = false;

  if ( _performer && _target )
  {
    FighterPtr fighter = _performer->getFeature<Fighter>();
    if ( fighter )
    {
      fighter->attack(_target);
      attacked = true;
    }
  }

  return attacked;
}

}

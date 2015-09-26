#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <memory>
#include <libtcod.hpp>
#include <actor_type.h>
#include <amarlon_except.h>
#include <actor_feature.h>
#include <pickable.h>
#include <character.h>
#include <ai.h>
#include <openable.h>
#include <wearer.h>
#include <destroyable.h>
#include <inventory.h>
#include <subject.h>

namespace amarlon {

class Map;
class ActorAction;
class StatusEffectsManager;
typedef std::shared_ptr<StatusEffectsManager> StatusEffectsManagerPtr;
typedef std::shared_ptr<ActorAction> ActorActionPtr;
typedef std::shared_ptr<Map> MapPtr;
typedef std::weak_ptr<Map> MapWPtr;

class Actor : public std::enable_shared_from_this<Actor>
            , public Subject
{
public:
  static ActorPtr create(ActorType aId, int x = 0, int y = 0, MapPtr map = nullptr);
  ~Actor();

  ActorPtr clone();  
  bool operator==(const Actor& rhs) const;

  /**
   * Properties from general Actor Database
   */
  unsigned char getChar()       const;
  TCODColor     getColor()      const;
  std::string   getName()       const;
  bool          isBlocking()    const;
  bool          isTransparent() const;
  bool          isFovOnly()     const;

  /**
   * Instance properties
   */
  ActorType getType() const;
  void      setType(ActorType newType);
  MapPtr    getMap() const;
  void      setMap(MapPtr map);
  int       getX() const;
  int       getY() const;
  int       getTileRenderPriority() const;

  /**
   * @brief Changes the actors coordinates and sets its position on map
   *        (if the map is set)
   */
  void setPosition(int x, int y);

  /**
   * @brief Builds a string actor's description from all ActorFeatures
   *        and general properties.
   */
  std::string   getDescription();

  /**
   * @brief Changes the actor type, removes all ActorFeatures
   *        and loads new, default, features.
   */
  void morph(ActorType newType);

  /**
   * @brief Allows player to take its turn. Ticks the time
   *        - updates AI and updates the effects status
   */
  void update();

  /**
   * @brief Checks if the Character actor feature for alive status
   */
  bool isAlive() const;

  /**
   * @brief Checks if actor is in player's field of view
   */
  bool isInFov();

  /**
   * @brief Return true if given actor is allied
   */
  bool isAllyOf(ActorPtr actor);

  /**
   * @brief A Buff/Debuff manager
   */
  StatusEffectsManager& getStatusEffects() const;

  /**
   * @brief adds actor feature or overwrites existing one
   * @param feature to be inserted
   * @return overwriten feature if any, otherwise empty pointer
   */
  ActorFeaturePtr insertFeature(ActorFeaturePtr feature);

  /**
   * @param feature type enum
   * @return actor feature as base class pointer
   */
  ActorFeaturePtr getFeature(ActorFeature::Type afType) const;

  /**
   * @brief works similar to above getFeature, with the diference
   *        that it returns a pointer to derived class, not base
   *        example usage: getFeature<Pickable>()
   */
  template<typename T>
  std::shared_ptr<T> getFeature() const;

  /**
   * @return True if this instance of Actor contain given ActorFeature
   */
  template<typename T>
  bool hasFeature();

  /**
   * @brief ActorActions are general interface for actor manipulation
   * @param Action to be performed
   * @return True if action has been performed successfully
   */
  bool performAction(ActorActionPtr action);

private:
  ActorType _id;
  int _x, _y;
  MapWPtr _map;
  FeatureMap _features;
  StatusEffectsManagerPtr _effects;


  Actor(ActorType aId, int x = 0, int y = 0, MapPtr map = nullptr);
  void loadFeatures();

  friend class ActorSerializer;

};

typedef std::shared_ptr<Actor> ActorPtr;

template<typename T>
std::shared_ptr<T> Actor::getFeature() const
{
  auto it = _features.find( T::featureType );
  return it != _features.end() ? std::dynamic_pointer_cast<T>(it->second) : nullptr;
}

template<typename T>
bool Actor::hasFeature()
{
  return _features.find( T::featureType ) != _features.end();
}

}
#endif // ACTOR_H

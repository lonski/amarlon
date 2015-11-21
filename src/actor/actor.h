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
#include <bitset>
#include <point.h>
#include <actor_action_result.h>

namespace amarlon {

class Map;
class ActorAction;
class StatusEffectsManager;
struct ActorDescription;
typedef std::shared_ptr<StatusEffectsManager> StatusEffectsManagerPtr;
typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;
typedef std::shared_ptr<ActorAction> ActorActionPtr;
typedef std::shared_ptr<Map> MapPtr;
typedef std::weak_ptr<Map> MapWPtr;

class Actor : public std::enable_shared_from_this<Actor>
            , public Subject
{
public:
  /**
   * @brief Builds an actor basing on the description from ActorDatabase
   */
  static ActorPtr create(ActorType aId, int x = 0, int y = 0, MapPtr map = nullptr);
  /**
   * @brief Builds an actor from description structure.
   * @param dsc - description structure, on which base actor will be build.
   * @param prototyped - if true, actor will be build from default description from ActorDatabase
   *        and then its content will be overriden with passed description structure.
   *        Otherwise, actor will be build only basing on passed description scructure.
   */
  static ActorPtr create(ActorDescriptionPtr dsc, bool prototyped = true);

  /**
   * @brief Overrides actor's content with content from given description structure.
   *        Fuills only changed data. All other data remain unchanged.
   */
  void upgrade(ActorDescriptionPtr dsc);
  ~Actor();

  ActorPtr clone();  
  bool operator==(const Actor& rhs) const;
  Actor& operator=(const Actor& rhs);

  /**
   * Actor properties
   */
  ActorType getType() const;
  void setType(ActorType newType);

  unsigned char getSymbol() const;
  void setSymbol(unsigned char s);

  TCODColor getColor() const;
  void setColor( TCODColor c );

  std::string getName() const;
  void setName(std::string n);

  bool isBlocking() const;
  void setBlocking(bool b);

  bool isTransparent() const;
  void setTransparent(bool t);

  bool isFovOnly() const;
  void setFovOnly(bool f);

  int getX() const;
  int getY() const;
  int getTileRenderPriority() const;

  MapPtr getMap() const;
  void setMap(MapPtr map);

  /**
   * Non persistent status properties
   */

  bool isVisible() const;
  void setVisible(bool visible);

  /**
   * @brief Changes the actors coordinates and sets its position on map
   *        (if the map is set)
   */
  void setPosition(int x, int y);
  void setPosition(const Point& p);

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
   * @return Amount of turns the update took.
   *         Usable only for PLAYER_CONTROLLED actors
   */
  int update();

  /**
   * @brief Checks if the Character actor feature for alive status
   */
  bool isAlive() const;

  /**
   * @brief Checks if actor is in player's field of view
   */
  bool isInFov();

  /**
   * @brief Check if this actor can see the passed one
   */
  bool sees(ActorPtr actor);

  /**
   * @brief Return true if given actor is allied
   */
  bool isAllyOf(ActorPtr actor);

  /**
   * @brief Return true if given actor is hostile
   */
  bool isHostileTo(ActorPtr actor);

  /**
   * @brief Handles interraction between two actors. For example, when another actor
   *        is entering tile, where this actor is already.
   */
  void interract(ActorPtr actor);

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
  ActorActionResult performAction(ActorActionPtr action);
  ActorActionResult performAction(ActorAction* action);

  /**
   * @brief Draws actor symbol on console
   */
  virtual void render(TCODConsole* console);

  /**
   * @brief True if this actor handles player input.
   *        In specific, has AI and this AI is in state of
   *        PLAYER_CONTROL
   */
  bool isPlayerControlled() const;

  std::string debug(const std::string& linebreak = "\n");
  void printDebug();

private:
  ActorType _id;
  int _x, _y;
  MapWPtr _map;
  FeatureMap _features;
  StatusEffectsManagerPtr _effects;
  bool _fovOnly;
  bool _transparent;
  bool _blocks;
  int _priority;
  std::string _name;
  std::string _description;
  TCODColor _color;
  char _symbol;
  std::bitset<1> _flags;

  Actor(ActorType aId = ActorType::Null, int x = 0, int y = 0, MapPtr map = nullptr);
  Actor(const Actor& a);
  void applyPassiveSkills();

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

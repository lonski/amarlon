#ifndef ACTORFEATUREEDITPANEL_H
#define ACTORFEATUREEDITPANEL_H

#include <apanel.h>
#include <actor_descriptions.h>
#include "actors_database.h"

namespace amarlon { namespace map_editor {

class ActorFeatureEditPanel : public gui::APanel
{
public:
  ActorFeatureEditPanel(ActorsDatabase* db);
  virtual void handleInput(TCOD_mouse_t mouse, TCOD_key_t key);

  virtual ActorDescriptionPtr actor() const;
  virtual void setActor(const ActorDescriptionPtr &actor);

protected:
  ActorsDatabase* _db;
  ActorDescriptionPtr _actor;

  virtual void init();

  template<typename T, typename DscType>
  T getField( std::experimental::optional<T> DscType::*field, int feature_index )
  {
    std::shared_ptr<DscType> o = std::dynamic_pointer_cast<DscType>(
          _actor->features[ feature_index ] );

    ActorDescriptionPtr prototype = _db->fetch( *_actor->id );
    std::shared_ptr<DscType> o_proto = std::dynamic_pointer_cast<DscType>(
          prototype->features[ feature_index ] );

    if (!o && !o_proto) return T();

    return o && *o.*field ? *(*o.*field)
                          : ( *o_proto.*field ? *(*o_proto.*field) : T() );

  }

  template<typename T, typename DscType>
  void saveField( std::experimental::optional<T> DscType::*field, int feature_index, T val )
  {
    std::shared_ptr<DscType> o = std::dynamic_pointer_cast<DscType>(
          _actor->features[ feature_index ] );

    ActorDescriptionPtr prototype = _db->fetch( *_actor->id );
    std::shared_ptr<DscType> o_proto = std::dynamic_pointer_cast<DscType>(
          prototype->features[ feature_index ] );

    if ( !o )
    {
      o.reset( new DscType );
      _actor->features [ feature_index ] = o;
    }

    if ( !o_proto || !((*o_proto).*field) || *((*o_proto).*field) != val )
      (*o).*field = val;
  }

};

}}

#endif // ACTORFEATUREEDITPANEL_H

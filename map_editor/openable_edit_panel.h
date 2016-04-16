#ifndef OPENABLEEDITPANEL_H
#define OPENABLEEDITPANEL_H

#include "actor_feature_edit_panel.h"
#include <atext_edit.h>
#include <actor_feature.h>

namespace amarlon { namespace map_editor {

class OpenableEditPanel : public ActorFeatureEditPanel
{
public:
  OpenableEditPanel(ActorsDatabase* db);

protected:
  void init();
  void saveActor();
  OpenableDescriptionPtr getOpenable() const;
  OpenableDescriptionPtr getOpenablePrototype() const;

  gui::ATextEditPtr _fLockId;
  gui::ATextEditPtr _fLocked;
  gui::ATextEditPtr _fScriptId;
  gui::ATextEditPtr _fClosed;
  gui::ATextEditPtr _fLockLevel;

  template<typename T>
  T getField( std::experimental::optional<T> OpenableDescription::*field )
  {
    OpenableDescriptionPtr o = getOpenable();
    OpenableDescriptionPtr o_proto = getOpenablePrototype();

    if (!o && !o_proto) return T();

    return o && *o.*field ? *(*o.*field)
                          : ( *o_proto.*field ? *(*o_proto.*field) : T() );

  }

  template<typename T>
  void saveField( std::experimental::optional<T> OpenableDescription::*field, T val )
  {
    OpenableDescriptionPtr o = getOpenable();
    OpenableDescriptionPtr o_proto = getOpenablePrototype();

    if ( !o )
    {
      o.reset( new OpenableDescription );
      _actor->features [ ActorFeature::OPENABLE ] = o;
    }

    if ( !o_proto || !((*o_proto).*field) || *((*o_proto).*field) != val )
      (*o).*field = val;
  }

};

}}

#endif // OPENABLEEDITPANEL_H

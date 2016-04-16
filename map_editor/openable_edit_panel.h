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

  gui::ATextEditPtr _fLockId;
  gui::ATextEditPtr _fLocked;
  gui::ATextEditPtr _fScriptId;
  gui::ATextEditPtr _fClosed;
  gui::ATextEditPtr _fLockLevel;
};

}}

#endif // OPENABLEEDITPANEL_H

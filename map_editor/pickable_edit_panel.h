#ifndef PICKABLEEDITPANEL_H
#define PICKABLEEDITPANEL_H

#include "actor_feature_edit_panel.h"
#include <atext_edit.h>
#include <actor_feature.h>

namespace amarlon { namespace map_editor {

class PickableEditPanel : public ActorFeatureEditPanel
{
public:
  PickableEditPanel(ActorsDatabase* db);

protected:
  void init();
  void saveActor();

  gui::ATextEditPtr _fAmount;
  gui::ATextEditPtr _fUses;
  gui::ATextEditPtr _fPrice;
  gui::ATextEditPtr _fWeight;
  gui::ATextEditPtr _fScript;
};

}}

#endif // PICKABLEEDITPANEL_H

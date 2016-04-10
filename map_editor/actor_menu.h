#ifndef ACTORMENU_H
#define ACTORMENU_H

#include <apanel.h>

namespace amarlon { namespace map_editor {

class ActorMenuPanel : public gui::APanel
{  
public:
  enum Action{
    ANoAction,
    ARemove
  };
  ActorMenuPanel(APanel* parent);
  void handleInput(TCOD_mouse_t mouse);
  void init();

  ActorMenuPanel::Action choosen() const;
  void setChoosen(const Action &choosen);

private:
  gui::APanel* _parent;
  Action _choosen;

};

}}

#endif // ACTORMENU_H

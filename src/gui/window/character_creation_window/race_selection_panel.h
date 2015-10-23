#ifndef RACE_SELECTION_PANEL_H
#define RACE_SELECTION_PANEL_H

#include <asub_panel.h>
#include <text_formater.h>

namespace amarlon {

class Race;
typedef std::shared_ptr<Race> RacePtr;

namespace gui {

class AMenu;
class AList;
class CharacterCreationWindow;
typedef std::shared_ptr<AList> AListPtr;
typedef std::shared_ptr<AMenu> AMenuPtr;

class RaceSelectionPanel : public ASubPanel
{
public:
  RaceSelectionPanel(CharacterCreationWindow* parent);

  virtual void selectNext();
  virtual void selectPrevious();

  virtual void manage();
  virtual void update();

  RacePtr getSelectedRace() const;

private:
  AMenuPtr _races;
  AListPtr _dsc;
  TextFormater _formater;
  CharacterCreationWindow* _parent;

  void showDescription();

};

}}

#endif // RACE_SELECTION_PANEL_H

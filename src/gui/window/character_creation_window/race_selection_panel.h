#ifndef RACE_SELECTION_PANEL_H
#define RACE_SELECTION_PANEL_H

#include <asub_panel.h>
#include <text_formater.h>

namespace amarlon { namespace gui {

class AMenu;
class AList;
typedef std::shared_ptr<AList> AListPtr;
typedef std::shared_ptr<AMenu> AMenuPtr;

class RaceSelectionPanel : public ASubPanel
{
public:
  RaceSelectionPanel();

  virtual void selectNext();
  virtual void selectPrevious();

  virtual void manage();
  virtual void update();

private:
  AMenuPtr _races;
  AListPtr _dsc;
  TextFormater _formater;

  void showDescription();

};

}}

#endif // RACE_SELECTION_PANEL_H

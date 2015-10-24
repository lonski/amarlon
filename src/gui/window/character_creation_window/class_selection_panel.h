#ifndef CLASS_SELECTION_PANEL_H
#define CLASS_SELECTION_PANEL_H

#include <asub_panel.h>
#include <text_formater.h>

namespace amarlon {

class CharacterClass;
typedef std::shared_ptr<CharacterClass> CharacterClassPtr;

namespace gui {

class AMenu;
class AList;
class CharacterCreationWindow;
typedef std::shared_ptr<AList> AListPtr;
typedef std::shared_ptr<AMenu> AMenuPtr;

class ClassSelectionPanel : public ASubPanel
{
public:
  ClassSelectionPanel(CharacterCreationWindow* parent);

  virtual void selectNext();
  virtual void selectPrevious();

  virtual void manage();
  virtual void update();
  virtual void handleKey(TCOD_key_t key);

private:
  AMenuPtr _classes;
  AListPtr _dsc;
  TextFormater _formater;
  CharacterCreationWindow* _parent;

  void showDescription();
  CharacterClassPtr getSelectedClass() const;
  void setClass();

};

}}

#endif // CLASS_SELECTION_PANEL_H

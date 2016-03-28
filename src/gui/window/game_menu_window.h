#ifndef GAME_MENU_WINDOW_H
#define GAME_MENU_WINDOW_H

#include <awindow.h>
#include <amenu.h>
#include <alist.h>

namespace amarlon { namespace gui {

class GameMenu : public AWindow
{
public:
  static  WindowId getId() { return AWindow::GAME_MENU; }

  GameMenu();
  virtual ~GameMenu();

  virtual AWindow& show();

private:
  gui::AMenuPtr _menu;
  gui::AListPtr _logo;

  std::map<std::string, bool (GameMenu::*)() > _functions;

  bool new_game();
  bool save_game();
  bool load_game();
  bool quit_game();

  void fillMenuSlots();

};

}}

#endif // GAME_MENU_WINDOW_H

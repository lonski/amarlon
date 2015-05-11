#ifndef MENU_WINDOW_H
#define MENU_WINDOW_H

#include <awindow.h>
#include <amenu.h>

namespace amarlon { namespace gui {

class MenuWindow : public AWindow
{
public:
  static  WindowId getId() { return AWindow::MENU; }

  MenuWindow();
  virtual AWindow& show();
  virtual AWindow& setDefaults();

  virtual void addMenuItem(AMenuItemPtr item);
  virtual AMenuItemPtr getSelectedItem();

private:
  AMenuPtr _menu;

  void init();

};

}}

#endif // MENU_WINDOW_H

#ifndef AHORIZONTAL_MENU_H
#define AHORIZONTAL_MENU_H

#include <amenu.h>

namespace amarlon { namespace gui {

class AHorizontalMenu : public AMenu
{
public:
  AHorizontalMenu();
  virtual ~AHorizontalMenu();

  void render(TCODConsole& console);

  virtual int getWidth() const;
  virtual int getHeight() const;

private:
  int calculateHeight() const;

};

}}

#endif // AHORIZONTAL_MENU_H

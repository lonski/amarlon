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

  /**
   * @brief Delegates to AMenu::fill
   */
  template<typename T, typename MenuItemType = ALabelMenuItem>
  void fill(std::vector<std::shared_ptr<T> > content,
            std::function<std::string(std::shared_ptr<T>)> value_fun,
            std::function<std::string(std::shared_ptr<T>)> category_fun = [](std::shared_ptr<T>){ return "";})
  {
    _menu->fill<T, MenuItemType>(content, value_fun, category_fun);
  }

private:
  AMenuPtr _menu;

  void init();

};

}}

#endif // MENU_WINDOW_H

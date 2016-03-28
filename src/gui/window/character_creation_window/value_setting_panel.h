#ifndef VALUE_SETTING_PANEL_H
#define VALUE_SETTING_PANEL_H

#include <asub_panel.h>
#include <ahorizontal_menu.h>
#include <alabel_menu_item.h>
#include <alabel.h>
#include <utils.h>

namespace amarlon { namespace gui {

class ValueSettingPanel : public ASubPanel
{
public:
  ValueSettingPanel(const std::string& name, int value, MinMax constrains, int& pointsPool);

  void activate();
  void deactivate();
  virtual void selectNext();
  virtual void selectPrevious();
  virtual void update();
  virtual void manage();

  int getValue() const;

private:
  AMenuPtr _menu;
  ALabelMenuItemPtr _plus;
  ALabelMenuItemPtr _minus;
  ALabelPtr _nameLabel;
  ALabelPtr _valueLabel;
  MinMax _constrains;
  int _currentValue;
  std::string _name;
  int& _pool;

  void setValue(int val);

};

typedef std::shared_ptr<ValueSettingPanel> ValueSettingPanelPtr;

}}

#endif // VALUE_SETTING_PANEL_H

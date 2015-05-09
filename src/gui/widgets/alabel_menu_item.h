#ifndef SELECTABLE_LABEL_H
#define SELECTABLE_LABEL_H

#include <memory>
#include <libtcod.hpp>
#include <amenu_item.h>

namespace amarlon { namespace gui {

class ALabel;
typedef std::shared_ptr<ALabel> ALabelPtr;

class ALabelMenuItem : public AMenuItem
{
public:
  ALabelMenuItem();

  virtual void render(TCODConsole& console);

  virtual void select();
  virtual void deselect();

  virtual TCODColor getColor() const;
  virtual void setColor(const TCODColor& color);

  virtual std::string getValue() const;
  virtual void setValue(const std::string& value);

  virtual int getWidth() const;
  virtual int getHeight() const;

  virtual void setWidth(int width);
  virtual void setHeight(int height);

private:
  ALabelPtr _label;

};

typedef std::shared_ptr<ALabelMenuItem> ALabelMenuItemPtr;

}}

#endif // SELECTABLE_LABEL_H

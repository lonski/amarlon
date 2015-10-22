#ifndef AMENU_ITEM_H
#define AMENU_ITEM_H

#include <memory>
#include <libtcod.hpp>
#include <awidget.h>

namespace amarlon { namespace gui {

class AMenuItem : public AWidget
{
public:
  AMenuItem() : _object(nullptr), _rawObject(nullptr) {}
  virtual ~AMenuItem() {}

  virtual void select() = 0;
  virtual void deselect() = 0;
  virtual bool isSelected() const = 0;

  virtual TCODColor getColor() const = 0;
  virtual void setColor(const TCODColor& color) = 0;

  virtual std::string getValue() const = 0;
  virtual void setValue(const std::string& value) = 0;

  /**
   * @brief Functions to manage the object bound to this item.
   *        MenuItem represents this object in menu.
   */
  template<typename T> void setObject(std::shared_ptr<T> t);
  template<typename T> std::shared_ptr<T> getObject();

private:
  std::shared_ptr<void> _object;
  void* _rawObject;

};

typedef std::shared_ptr<AMenuItem> AMenuItemPtr;

template<typename T> void AMenuItem::setObject(std::shared_ptr<T> t)
{
  _object = std::static_pointer_cast<void>(t);
}

template<typename T> std::shared_ptr<T> AMenuItem::getObject()
{
  return std::static_pointer_cast<T>(_object);
}

}}

#endif // AMENU_ITEM_H

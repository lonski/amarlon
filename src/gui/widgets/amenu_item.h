#ifndef AMENU_ITEM_H
#define AMENU_ITEM_H

#include <memory>
#include <libtcod.hpp>
#include <awidget.h>

namespace amarlon { namespace gui {

class AMenuItem : public AWidget
{
public:
  AMenuItem() : _object(nullptr) {}
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
  template<typename T> void setObject(T* t);
  template<typename T> T* getObject();

private:
  void* _object;

};

typedef std::shared_ptr<AMenuItem> AMenuItemPtr;

template<typename T> void AMenuItem::setObject(T* t)
{
  _object = static_cast<void*>(t);
}

template<typename T> T* AMenuItem::getObject()
{
  return static_cast<T*>(_object);
}

}}

#endif // AMENU_ITEM_H

#ifndef MESSENGER_H
#define MESSENGER_H

#include <string>
#include <memory>
#include <observer.h>

namespace amarlon {

namespace gui {
  class Gui;
}

class Messenger : public Observer
{
public:
  Messenger( std::weak_ptr<gui::Gui> gui );
  virtual ~Messenger();

  virtual void onNotify(Subject* subject, Event event);

private:
  std::weak_ptr<gui::Gui> _gui;

};

typedef std::shared_ptr<Messenger> MessengerPtr;

}

#endif // MESSENGER_H

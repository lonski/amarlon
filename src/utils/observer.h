#ifndef OBSERVER_H
#define OBSERVER_H

#include <event.h>

namespace amarlon {

class Subject;

class Observer
{
public:
  virtual ~Observer() {}
  virtual void onNotify(Subject* subject, Event event) = 0;
};

}

#endif // OBSERVER_H

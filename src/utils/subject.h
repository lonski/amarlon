#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
#include <event.h>

namespace amarlon {

class Observer;

class Subject
{
public:
  Subject();
  virtual ~Subject();
  virtual void addObserver(Observer* observer);
  virtual void removeObserver(Observer* observer);
  virtual void notify(Event event);

private:
  std::set<Observer*> _observers;

};

}

#endif // SUBJECT_H

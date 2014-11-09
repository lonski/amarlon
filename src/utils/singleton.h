#ifndef SINGLETON_H
#define SINGLETON_H

namespace amarlon
{

template<class T>
class Singleton
{
public:
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  static T& instance()
  {
    static T inst;
    return inst;
  }

protected:
  Singleton() = default;
  ~Singleton() = default;

};

}

#endif // SINGLETON_H

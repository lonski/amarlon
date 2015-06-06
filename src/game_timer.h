#ifndef GAME_TIMER_H
#define GAME_TIMER_H

#include <thread>
#include <engine.h>

namespace amarlon {

class GameTimer
{
public:
  GameTimer();
  ~GameTimer();

  void start();
  void resume();
  void speedUpTick();
  void pause();
  bool isRunning() const;

private:
  std::thread _timer;

  bool _stop;
  bool _speedUpTick;
  int _couter;

  void tick();

};

class TimeStop
{
public:
  TimeStop()
  {
    Engine::instance().timer().pause();
  }

  ~TimeStop()
  {
    Engine::instance().timer().resume();
  }
};

}

#endif // GAME_TIMER_H

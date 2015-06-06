#include "game_timer.h"

namespace amarlon {

GameTimer::GameTimer()
  : _stop(false)
  , _speedUpTick(false)
  , _couter(0)
{
}

GameTimer::~GameTimer()
{
  if ( _timer.joinable() )
  {
    _timer.join();
  }
}

void GameTimer::start()
{
  if ( !_timer.joinable() )
  {
    std::thread t{
      [&](){
            while (1)
            {
              std::this_thread::sleep_for( std::chrono::milliseconds(10) );

              if ( !_stop )
              {
                if ( ++_couter == 25 || _speedUpTick )
                {
                  tick();
                  _speedUpTick = false;
                  _couter = 0;
                }

                Engine::instance().render();
                TCODConsole::root->flush();
              }

            }
          }};
    _timer = std::move(t);
  }
}

void GameTimer::resume()
{
  _stop = false;  
  std::cout << "resume\n";
  std::cout.flush();
}

void GameTimer::pause()
{
  _stop = true;
  std::cout << "pause\n";
  std::cout.flush();
}

void GameTimer::speedUpTick()
{
  _speedUpTick = true;
  std::cout << "speed up\n";
  std::cout.flush();
}


bool GameTimer::isRunning() const
{
  return !_stop;
}

void GameTimer::tick()
{
  Engine::instance().update();
}

}

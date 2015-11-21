#include "input_dialog.h"
#include <engine.h>

namespace amarlon { namespace gui {

InputDialog::InputDialog()
  : _console(new TCODConsole(42, 5))
  , _maxSize(20)
{
  setDefaults();
}

AWindow &InputDialog::setDefaults()
{
  setTitle("Enter the name");
  _input = "";

  return *this;
}

std::string InputDialog::getText() const
{
  return _input;
}

void InputDialog::setText(const std::string &text)
{
  _input = text;
}

AWindow& InputDialog::show()
{
  TCOD_key_t key;
  key.vk = TCODK_TEXT;

  while(key.vk != TCODK_ENTER   && //accept
        key.vk != TCODK_KPENTER && //accept
        key.vk != TCODK_ESCAPE  && //cancel
        !TCODConsole::isWindowClosed())
  {
    render(*_console);
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);
    handlePressedKey(key);
  }

  if ( key.vk == TCODK_ESCAPE ) _input = "";

  return *this;
}

void InputDialog::render(TCODConsole&)
{
  renderFrame();
  renderInput();
  blitConsole();
}

int InputDialog::getMaxSize() const
{
  return _maxSize;
}

void InputDialog::setMaxSize(int maxSize)
{
  _maxSize = maxSize;
}

void InputDialog::setWidth(int width)
{
  APanel::setWidth(width + 2);
  _console.reset( new TCODConsole(width, _console->getHeight() ) );
}

void InputDialog::setHeight(int height)
{
  APanel::setHeight(height + 2);
  _console.reset( new TCODConsole(_console->getWidth(), height ) );
}

void InputDialog::renderFrame()
{
  _console->setDefaultForeground(TCODColor(200,180,50));
  _console->printFrame(0, 0, _console->getWidth(), _console->getHeight(), true, TCOD_BKGND_DEFAULT,
                      getTitle().empty() ? NULL : getTitle().c_str() );
}

void InputDialog::renderInput()
{
  int middle = _console->getWidth() / 2;
  int size = _input.size();
  int xpos = middle - size / 2;
  _console->print(xpos, 2, "%s", _input.c_str());
}

void InputDialog::blitConsole()
{
  int posX = Engine::consoleWidth  / 2 - _console->getWidth()  / 2;
  int posY = Engine::consoleHeight / 2 - _console->getHeight() / 2;

  TCODConsole::blit(_console.get(), 0, 0, _console->getWidth(), _console->getHeight(), TCODConsole::root, posX, posY);
  TCODConsole::flush();
}

void InputDialog::handlePressedKey(const TCOD_key_t &key)
{
  if (key.vk == TCODK_BACKSPACE)
  {
    if (!_input.empty()) _input.erase(_input.end()-1, _input.end());
  }
  else if ( _input.size() < _maxSize )
  {
    if ( key.c > 0 ) _input.push_back( key.c );
  }
  trim(_input);
}

}}


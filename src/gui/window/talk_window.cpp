#include "talk_window.h"
#include <amenu.h>
#include <engine.h>

namespace amarlon { namespace gui {

TalkWindow::TalkWindow()
  : FixedSizeTextWindow(Engine::consoleWidth, Engine::bottomPanelHeight)
  , _choices(new AMenu)
{
}

TalkWindow::~TalkWindow()
{
}

AWindow &TalkWindow::setDefaults()
{
  FixedSizeTextWindow::setDefaults();
  setPosition(AWidget::WINDOW_BOTTOM_LEFT);
  addWidget( _choices );
  setMargin(1);
  _choices->setX(_margin);

  return *this;
}

AWindow &TalkWindow::show()
{
  setText( _dialog.text );

  _choices->removeAllItems();
  for ( Choice c : _dialog.choices )
  {
    AMenuItemPtr item( new ALabelMenuItem(c.text) );
    item->setObject<Choice>( std::shared_ptr<Choice>(new Choice(c)) );
    _choices->addItem(item);
  }

  FixedSizeTextWindow::show();
  return *this;
}

TalkWindow& TalkWindow::setDialog(const Dialog &d)
{
  _dialog = d;
  return *this;
}

Choice TalkWindow::getChoice()
{
  Choice c;

  auto item = _choices->getSelectedItem();
  if ( item )
  {
    c = *item->getObject<Choice>();
  }

  return c;
}

void TalkWindow::displayText()
{
  FixedSizeTextWindow::displayText();
  _choices->setY( _list->getY() + _list->size() + 2 );
}

void TalkWindow::handleKey(TCOD_key_t& k)
{
  switch( k.vk )
  {
    case TCODK_UP:
    case TCODK_KP8:
      _choices->selectPrevious();
    break;
    case TCODK_DOWN:
    case TCODK_KP2:
      _choices->selectNext();
    break;
    default:;
  }
}

bool TalkWindow::exitCondition(const TCOD_key_t& key)
{
  return key.vk == TCODK_KPENTER ||
         key.vk == TCODK_ENTER;
}


}}

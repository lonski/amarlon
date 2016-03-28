#include "question_dialog.h"
#include <amenu.h>
#include <alabel_menu_item.h>

namespace amarlon { namespace gui {

QuestionDialog::QuestionDialog()
  : _menu(new AMenu)
{
  _menu->addItem( AMenuItemPtr(new ALabelMenuItem("No")) );
  _menu->addItem( AMenuItemPtr(new ALabelMenuItem("Yes")) );
}

QuestionDialog::Response QuestionDialog::getResponse()
{
  auto item = _menu->getSelectedItem();
  return item ? (item->getValue() == "Yes" ? YES : NO) : NO;
}

AWindow &QuestionDialog::setDefaults()
{
  ResizeableTextWindow::setDefaults();
  _menu->deselect();
  _menu->selectNext();

  return *this;
}

void QuestionDialog::handleKey(TCOD_key_t& key)
{
  switch(key.vk)
  {
    case TCODK_DOWN: _menu->selectNext(); break;
    case TCODK_UP: _menu->selectPrevious(); break;
    default:;
  }
}

void QuestionDialog::displayText()
{
  ResizeableTextWindow::displayText();
  setHeight(getHeight() + _menu->getHeight());
  _menu->setPosition( getWidth() - 1 - _menu->getWidth(), getHeight() - 1 - _menu->getHeight() );
  addWidget(_menu);
}

}}

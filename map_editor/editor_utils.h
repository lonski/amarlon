#ifndef EDITOR_UTILS_H
#define EDITOR_UTILS_H

#include <libtcod.hpp>
#include <vector>
#include <widgets/amenu_item.h>
#include <atext_edit.h>

namespace amarlon { namespace map_editor {

static inline void processInput(TCOD_mouse_t mouse, TCOD_key_t key, const std::vector<gui::AWidgetPtr>& widgets, int xoffset, int yoffset)
{
  for ( gui::AWidgetPtr w : widgets )
  {
    gui::AMenuItemPtr btn = std::dynamic_pointer_cast<gui::AMenuItem>(w);
    if ( btn )
    {
      if ( (w->getX()+xoffset <= mouse.cx) && (w->getX()+xoffset + w->getWidth() > mouse.cx) &&
           (w->getY()+yoffset <= mouse.cy) && (w->getY()+yoffset + w->getHeight() > mouse.cy ) )
      {
        btn->select();
        if ( mouse.lbutton_pressed )
        {
          btn->executeCallback();
        }
        if ( mouse.rbutton_pressed )
        {
          btn->executeCallback2();
        }
      }
      else
      {
        btn->deselect();
      }
    }
    //else
    {
      gui::ATextEditPtr edit = std::dynamic_pointer_cast<gui::ATextEdit>(w);
      if ( edit )
      {
        if ( edit->isActive() )
        {
          edit->handleKey(key);
        }
        if ( (w->getX()+xoffset <= mouse.cx) && (w->getX()+xoffset + w->getWidth() > mouse.cx) &&
             (w->getY()+yoffset <= mouse.cy) && (w->getY()+yoffset + w->getHeight() > mouse.cy ) && mouse.lbutton_pressed)
        {
          edit->activate();
        }
        else if ( mouse.lbutton_pressed )
        {
          edit->deactivate();
        }
      }
    }
  }
}

}}

#endif // EDITOR_UTILS_H

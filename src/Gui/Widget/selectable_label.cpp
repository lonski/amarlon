#include "selectable_label.h"

namespace amarlon { namespace gui {

SelectableLabel::SelectableLabel()
  : _selected(false)
{
}

void SelectableLabel::select()
{
  TCODColor temp = getBgcolor();

  setBgcolor( getColor() );
  setColor( temp );

  _selected = true;
}

void SelectableLabel::deselect()
{
  TCODColor temp = getColor();

  setColor( getBgcolor() );
  setBgcolor( temp );

  _selected = false;
}

bool SelectableLabel::selected() const
{
  return _selected;
}

}}

#ifndef SELECTABLE_LABEL_H
#define SELECTABLE_LABEL_H

#include <memory>
#include <Gui/Widget/label.h>

namespace amarlon { namespace gui {

class SelectableLabel : public Label
{
public:
  SelectableLabel();

  void select();
  void deselect();
  bool selected() const;

private:
  bool _selected;

};

typedef std::shared_ptr<SelectableLabel> SelectableLabelPtr;

}}

#endif // SELECTABLE_LABEL_H

#ifndef GUIOBJECT_H
#define GUIOBJECT_H

class TCODConsole;

namespace amarlon {

class GuiObject
{
public:
  GuiObject();
  virtual ~GuiObject() {}

  virtual void render(TCODConsole* console) = 0;
};

}

#endif // GUIOBJECT_H

#ifndef LOAD_SAVE_GAME_WINDOW_H
#define LOAD_SAVE_GAME_WINDOW_H

#include <awindow.h>
#include <amenu.h>
#include <alabel.h>

namespace amarlon { namespace gui {

class LoadSaveGameWindow : public AWindow
{
public:
  enum Mode
  {
    LOAD,
    SAVE
  };

  static  WindowId getId() { return AWindow::LOAD_SAVE_GAME; }

  LoadSaveGameWindow();
  virtual ~LoadSaveGameWindow();

  virtual AWindow& show();
  virtual std::string getSelectedFilename();
  virtual std::string getSelectedSlotName();
  virtual void setMode(Mode mode);
  virtual AWindow& setDefaults();

private:
  gui::AMenuPtr _menu;
  Mode _mode;
  int _slotCount;
  ALabelPtr _title;

  bool choose();
  void fillSaveSlots();
  std::string promptForName(const std::string &def);

};

}}

#endif // LOAD_SAVE_GAME_WINDOW_H

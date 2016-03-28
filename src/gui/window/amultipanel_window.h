#ifndef AMULTIPANEL_WINDOW_H
#define AMULTIPANEL_WINDOW_H

#include <memory>
#include <awindow.h>

namespace amarlon { namespace gui {

class ASubPanel;
typedef std::shared_ptr<ASubPanel> ASubPanelPtr;

class AMultiPanelWindow : public AWindow
{
public:
  AMultiPanelWindow();
  virtual ~AMultiPanelWindow();

  virtual AWindow& show();

protected:
  std::map<int, ASubPanelPtr> _panels;
  int _activePanel;

  virtual void managePanel(int panel) = 0;
  virtual bool exitWindow(TCOD_key_t key) = 0;
  virtual void loopUpdate() {}

private:
  void handleKey(TCOD_key_t key);
  void activateNextPanel();
  void activatePreviousPanel();

};

}}
#endif // AMULTIPANEL_WINDOW_H

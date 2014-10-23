#include "Gui.h"
#include <algorithm>
#include <iostream>

Gui::Gui()
  : _frameColor(TCODColor::darkerOrange)
{
  rCon = new TCODConsole(rightConWidth, rightConHeight);
  bCon = new TCODConsole(bottomConWidth, bottomConHeight);

  logCon = new TCODConsole(logConWidth, logConHeight);
  viewCon = new TCODConsole(viewConWidth, viewConHeight);
}

Gui::~Gui()
{
  delete rCon;
  delete bCon;

  delete logCon;
  delete viewCon;
}

void Gui::message(std::string msg, TCODColor color)
{
  if (_msgLog.size() == LogSize )
    _msgLog.pop_front();

  _msgLog.push_back( LogEntry(msg, color) );
}

void Gui::render()
{
  renderRightPanel();
  renderMessageLog();
  renderViewPanel();
}

void Gui::renderRightPanel()
{
  //frame
  rCon->setDefaultForeground(_frameColor);
  rCon->printFrame(0, 0, rightConWidth, rightConHeight, true, TCOD_BKGND_DEFAULT);

  TCODConsole::blit(rCon, 0, 0, rightConWidth, rightConHeight, TCODConsole::root, gloScreenWidth - rightConWidth, 0 );
}

void Gui::renderMessageLog()
{
  //log frame
  logCon->setDefaultForeground(_frameColor);
  logCon->printFrame(0, 0, logConWidth, logConHeight, true, TCOD_BKGND_DEFAULT);

  int row = 1;
  std::for_each(_msgLog.begin(), _msgLog.end(), [&](LogEntry& entry)
  {
    logCon->setDefaultForeground(entry.color);
    logCon->print(2, ++row, entry.msg.c_str());
  });

  TCODConsole::blit(logCon, 0, 0, logConWidth, logConHeight, TCODConsole::root, 0, gloScreenHeight - logConHeight );
}

void Gui::renderViewPanel(std::vector<LogEntry> *items)
{
  //log frame
  viewCon->setDefaultForeground(_frameColor);
  viewCon->printFrame(0, 0, viewConWidth, viewConHeight, true, TCOD_BKGND_DEFAULT);

  int row = 1;
  int msgLimit = viewConHeight - 2;

  if (items)
    std::for_each(items->begin(), items->end(), [&](LogEntry& entry)
    {
      if ( row < msgLimit )
      {
        viewCon->setDefaultForeground(entry.color);
        viewCon->print(2, ++row, entry.msg.c_str());
      }
      else if (row == msgLimit)
      {
        viewCon->setDefaultForeground(entry.color);
        viewCon->print(2, ++row, "...");
      }
    });

  TCODConsole::blit(viewCon, 0, 0, viewConWidth, viewConHeight, TCODConsole::root, logConWidth, gloScreenHeight - viewConHeight );
}

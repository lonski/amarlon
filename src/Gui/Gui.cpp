#include "Gui.h"
#include <algorithm>
#include <iostream>

Gui Gui::Root;

Gui::Gui()
  : _frameColor(TCODColor::darkerOrange)
{
  rCon = new TCODConsole(bottomConWidth, bottomConHeight);
  bCon = new TCODConsole(rightConWidth, rightConHeight);
}

Gui::~Gui()
{
  delete rCon;
  delete bCon;
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
  renderBottomPanel();

  TCODConsole::blit(rCon, 0, 0, bottomConWidth, bottomConHeight, TCODConsole::root, gloScreenWidth - bottomConWidth, 0 );
  TCODConsole::blit(bCon, 0, 0, rightConWidth, rightConHeight, TCODConsole::root, 0, gloScreenHeight - rightConHeight );
  TCODConsole::flush();
}

void Gui::renderRightPanel()
{
  //frame
  rCon->setDefaultForeground(_frameColor);
  rCon->printFrame(0, 0, bottomConWidth, bottomConHeight, true, TCOD_BKGND_DEFAULT);

}

void Gui::renderBottomPanel()
{
  //frame
  bCon->setDefaultForeground(_frameColor);
  bCon->printFrame(0, 0, rightConWidth, rightConHeight, true, TCOD_BKGND_DEFAULT);

  //message log
  renderMessageLog();
}

void Gui::renderMessageLog()
{
  int row = 1;
  std::for_each(_msgLog.begin(), _msgLog.end(), [&](LogEntry& entry)
  {
    bCon->setDefaultForeground(entry.color);
    bCon->print(2, ++row, entry.msg.c_str());
  });
}

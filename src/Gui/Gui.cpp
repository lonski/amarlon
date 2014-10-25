#include "Gui.h"
#include <algorithm>
#include <iostream>

namespace amarlon {

void renderBar(int x, int y, int width, const char *name, float value,
                    float maxValue, const TCODColor &barColor, const TCODColor &backColor, TCODConsole* con)
{
  // fill the background
  con->setDefaultBackground(backColor);
  con->rect(x,y,width,1,false,TCOD_BKGND_SET);

  int barWidth = (int)(value / maxValue * width);
  if ( barWidth > 0 )
  {
    // draw the bar
    con->setDefaultBackground(barColor);
    con->rect(x,y,barWidth,1,false,TCOD_BKGND_SET);
  }

  // print text on top of the bar
  con->setDefaultForeground(TCODColor::white);
  con->printEx(x+width/2, y, TCOD_BKGND_NONE,TCOD_CENTER,	"%s : %g/%g", name, value, maxValue);
}

Gui::Gui()
  : LogSize(17)
  , rightConWidth(20)
  , rightConHeight(gloScreenHeight)
  , bottomConWidth(gloScreenWidth - 20)
  , bottomConHeight(20)
  , logConWidth((gloScreenWidth - 20) / 2)
  , logConHeight(20)
  , viewConWidth((gloScreenWidth - 20) / 2)
  , viewConHeight(20)
  , _frameColor(TCODColor::darkerOrange)
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
  renderViewPanel(std::vector<LogEntry>());
}

void Gui::renderRightPanel()
{
  //frame
  rCon->setDefaultForeground(_frameColor);
  rCon->printFrame(0, 0, rightConWidth, rightConHeight, true, TCOD_BKGND_DEFAULT);

  renderBar(2,4,16,"HP",3,10,TCODColor::red, TCODColor::darkerRed,rCon);

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

void Gui::renderViewPanel(const std::vector<LogEntry>& items)
{
  //log frame
  viewCon->setDefaultForeground(_frameColor);
  viewCon->printFrame(0, 0, viewConWidth, viewConHeight, true, TCOD_BKGND_DEFAULT);

  int row = 1;
  int msgLimit = viewConHeight - 3;

  std::for_each(items.begin(), items.end(), [&](const LogEntry& entry)
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

}

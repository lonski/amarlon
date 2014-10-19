#ifndef AMOUNTWINDOW_H
#define AMOUNTWINDOW_H

#include <string>
#include <libtcod.hpp>

class AmountWindow
{
public:
  AmountWindow(int defAmount, std::string title = "Enter amount");
  int getAmount();

  void renderFrame();
  void renderAmount();
  void blitConsole();
private:
  std::string _title;

  const int _conWidth = 21;
  const int _conHeight = 5;
  TCODConsole _console;

  int _amount;
  bool _firstHit;

  void render();
  void handlePressedKey(const TCOD_key_t& key);

};

#endif // AMOUNTWINDOW_H

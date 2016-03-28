#ifndef DIRECTIONSELECTOR_H
#define DIRECTIONSELECTOR_H

#include <libtcod.hpp>
#include <string>

namespace amarlon {

class DirectionSelector
{
public:
  DirectionSelector(const std::string& selectionMessage = "");

  /**
   * @brief Updates the coordinates according to selected direction.
   * @return False if selection was aboirted, true otherwise
   */
  bool select(int& dx, int& dy);

private:
  std::string _selectionMessage;

};

}

#endif // DIRECTIONSELECTOR_H

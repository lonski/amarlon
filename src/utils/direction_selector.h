#ifndef DIRECTIONSELECTOR_H
#define DIRECTIONSELECTOR_H

#include <libtcod.hpp>

namespace amarlon {

class DirectionSelector
{
public:
  DirectionSelector();

  /**
   * @brief Updates the coordinates according to selected direction.
   * @return False if selection was aboirted, true otherwise
   */
  bool select(int& dx, int& dy);

};

}

#endif // DIRECTIONSELECTOR_H

#ifndef ITEMPICKER_H
#define ITEMPICKER_H

namespace amarlon {

class Actor;

class ItemPicker
{
public:
  ItemPicker(Actor *picker, Actor*& toPick);

  /**
   * @brief Invokes the picking. Handles stackable. If item is stackable
   *        and is spilted, then toPick actor addres is changed to a new instance of Actor class.
   *        That's why it is given by a reference to a pointer.
   * @return The amount of items picked. If not staskable, then max amount is equal to 1. If failed
   *         to pickup item, then return is 0.
   */
  int pick();

private:
  Actor* _picker;
  Actor*& _toPick;

};

}

#endif // ITEMPICKER_H

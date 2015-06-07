#ifndef DICES_H
#define DICES_H

namespace amarlon { namespace dices {

const int NATURAL_ONE = 1;
const int NATURAL_TWENTY = 20;

enum Die
{
  NoDie = 0,
  D4    = 4,
  D6    = 6,
  D8    = 8,
  D10   = 10,
  D12   = 12,
  D20   = 20,
  D100  = 100
};

int roll(Die dieType);
int roll(int from, int to);

}}

#endif // DICES_H

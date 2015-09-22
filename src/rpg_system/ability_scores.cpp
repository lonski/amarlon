#include "ability_scores.h"

namespace amarlon { namespace AbilityScore {

  int getModifier(int abilityScoreValue)
  {
    int mod = 0;

    if ( abilityScoreValue >= MIN_VALUE && abilityScoreValue <= MAX_VALUE )
    {
      mod = modifiersMap[ abilityScoreValue ];
    }

    return mod;
  }

}}


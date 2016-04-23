#ifndef TREASURE_TYPE_H
#define TREASURE_TYPE_H

namespace amarlon {

enum class TreasureType
{
  A,
  B
};

static std::map<const char*, TreasureType> Str2TreasureType {
  { "A", TreasureType::A },
  { "B", TreasureType::B }
};

}

#endif // TREASURE_TYPE_H
